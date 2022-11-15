#ifndef LOCK_MANAGER_H
#define LOCK_MANAGER_H

#include <set>
#include <map>
#include <utility>
#include <string>
#include <mutex>
#include <vector>
#include <condition_variable>

#include "transaction.h"

class LockMgr {

private:
    std::mutex mutex;

    std::map<VarType, Lock> locks;
    std::map<VarType, std::set<TxnID>> active;

    std::map<VarType, std::condition_variable> cvs;
    std::map<VarType, std::set<TxnID>> qs;

public:
    void acquireReadLock(TxnID txnID, VarType var_name);
    void acquireWriteLock(TxnID txnID, VarType var_name);
    void upgradeToWrite(TxnID txnID, VarType var_name);
    void releaseLock(TxnID txnID, VarType var_name);

    LockMgr(std::vector<VarType> state_vars);

};

#endif /* LOCK_MANAGER_H */
