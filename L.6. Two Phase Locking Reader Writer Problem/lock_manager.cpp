#include "lock_manager.h"
#include <iostream>

void LockMgr::acquireReadLock(TxnID txnID, VarType var_name)
{
    std::unique_lock<std::mutex> lk(mutex);

    while (locks[var_name] == Lock::Write) {
        std::cout << "Entering waiting: READ " << txnID << ' ' << var_name << '\n';
        qs[var_name].insert(txnID);
        cvs[var_name].wait(lk, [&]{ return (locks[var_name] <= Lock::Read); });
        qs[var_name].erase(txnID);
    }

    locks[var_name] = Lock::Read;
    active[var_name].insert(txnID);

    lk.unlock();
}

void LockMgr::acquireWriteLock(TxnID txnID, VarType var_name)
{
    std::unique_lock<std::mutex> lk(mutex);

    while (locks[var_name] != Lock::Unlocked) {
        std::cout << "Entering waiting: Write " << txnID << ' ' << var_name << '\n';
        qs[var_name].insert(txnID);
        cvs[var_name].wait(lk, [&]{ return (locks[var_name] == Lock::Unlocked); });
        qs[var_name].erase(txnID);
    }

    locks[var_name] = Lock::Write;
    active[var_name].insert(txnID);

    lk.unlock();
}

void LockMgr::upgradeToWrite(TxnID txnID, VarType var_name)
{
    std::unique_lock<std::mutex> lk(mutex);

    while (active[var_name].size() > 1) {
        std::cout << "Entering waiting: UPGRADE " << txnID << ' ' << var_name << '\n';
        for (auto var : active[var_name]) {
            std::cout << var << '\n';
        }
        qs[var_name].insert(txnID);
        cvs[var_name].wait(lk, [&]{ return (active[var_name].size() == 1); });
        qs[var_name].erase(txnID);
    }

    locks[var_name] = Lock::Write;

    lk.unlock();
}

void LockMgr::releaseLock(TxnID txnID, VarType var_name)
{
    std::unique_lock<std::mutex> lk(mutex);

    if (locks[var_name] == Lock::Write)
    {
        active[var_name].erase(txnID);
        locks[var_name] = Lock::Unlocked;

        if (qs[var_name].size() > 0)
            cvs[var_name].notify_all();
    }
    else if (locks[var_name] == Lock::Read)
    {
        active[var_name].erase(txnID);

        if (active[var_name].size() <= 1)
        {
            locks[var_name] = Lock::Unlocked;
            cvs[var_name].notify_all();
        }
    }

    lk.unlock();
}

LockMgr::LockMgr(std::vector<VarType> state_vars)
{
    for (VarType var_name : state_vars) {
        locks[var_name] = Lock::Unlocked;
    }
}




