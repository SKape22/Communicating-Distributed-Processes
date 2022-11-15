#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <signal.h>

#include "transaction.h"
#include "lock_manager.h"

using namespace std;

map<VarType,VarValue> state_vars;
LockMgr *lkm;

int num_txn;
vector<Transaction*> transactions;


void signal_cb(int signum)
{
    cout << "Caught keyboard interrupt!\n";
    cout << "Currently unfinished transactions: \n";
    for (Transaction *txn : transactions) {
        if (txn->outcome == Outcome::Running)
            cout << txn->id << '\n';
    }

    exit(signum);
}

bool is_number(const string &s)
{
    return !s.empty() && find_if(s.begin(),
        s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

Operation* input_op()
{
    Operation *op = new Operation;

    string op_type; cin >> op_type;
    if (op_type == "READ") {
        op->op_type = OpType::Read;
        cin >> op->var_name;
    } else if (op_type == "WRITE") {
        op->op_type = OpType::Write;
        cin >> op->var_name;
    } else if (op_type == "ASSIGN") {
        op->op_type = OpType::Assign;
        cin >> op->var_name;
        cin >> op->op1 >> op->op >> op->op2;
        if (op->op != "+" && op->op != "-") {
            cout << "Invalid operand: " << op->op << '\n';
            exit(2);
        }
    } else if (op_type == "COMMIT") {
        op->op_type = OpType::Commit;
    } else if (op_type == "ABORT") {
        op->op_type = OpType::Abort;
    } else {
        cout << "Invalid Operation: " << op_type << '\n';
        exit(1);
    }

    return op;
}

void execute_transaction(Transaction *txn)
{
    map<VarType,VarValue> backup = txn->local_vars;
    txn->local_vars.clear();

    for (int i = 0; i < txn->num_ops; i++) {
        Operation *currOp = txn->operations[i];

        switch(currOp->op_type) {

            case OpType::Read :
                cout << "READ " << txn->id << ' ' << currOp->var_name << '\n';

                if (txn->locks[currOp->var_name] < Lock::Read)
                    lkm->acquireReadLock(txn->id, currOp->var_name);

                txn->local_vars[currOp->var_name] = state_vars[currOp->var_name];
                txn->locks[currOp->var_name] = Lock::Read;

                break;

            case OpType::Write :
                cout << "WRITE " << txn->id << ' ' << currOp->var_name << '\n';

                if (txn->locks[currOp->var_name] < Lock::Read)
                    lkm->acquireWriteLock(txn->id, currOp->var_name);
                else if (txn->locks[currOp->var_name] < Lock::Write)
                {
                    lkm->upgradeToWrite(txn->id, currOp->var_name);
                }

                state_vars[currOp->var_name] = txn->local_vars[currOp->var_name];
                txn->locks[currOp->var_name] = Lock::Write;

                break;

            case OpType::Assign :
                cout << "ASSIGN " << txn->id << ' ' << currOp->var_name << " = " << currOp->op1 << ' ' << currOp->op << ' ' << currOp->op2 << '\n';

                VarValue val1;
                if (is_number(currOp->op1))
                    val1 = stoi(currOp->op1);
                else
                    val1 = txn->local_vars[currOp->op1];

                VarValue val2;
                if (is_number(currOp->op2))
                    val2 = stoi(currOp->op2);
                else
                    val2 = txn->local_vars[currOp->op2];

                if (currOp->op == "+") {
                    txn->local_vars[currOp->var_name] = val1 + val2;
                } else if (currOp->op == "-") {
                    txn->local_vars[currOp->var_name] = val1 - val2;
                }

                break;

            case OpType::Commit :
                cout << "COMMIT " << txn->id<< '\n';

                for (auto &p : txn->locks) {
                    if (p.second > Lock::Unlocked)
                        lkm->releaseLock(txn->id, p.first);
                }

                txn->outcome = Outcome::Commit;
                return;

            case OpType::Abort :
                cout << "ABORT " << txn->id << '\n';

                for (auto &p : txn->locks) {
                    if (p.second == Lock::Write)
                        state_vars[p.first] = backup[p.first];
                    if (p.second > Lock::Unlocked)
                        lkm->releaseLock(txn->id, p.first);
                }

                txn->outcome = Outcome::Abort;
                return;
        }
    }

}

int main()
{
    signal(SIGINT, signal_cb);

    int num_var; cin >> num_var;
    vector<VarType> state_vars_list;
    for (int i = 0; i < num_var; i++) {
        VarType var_name; VarValue var_value; cin >> var_name >> var_value;
        state_vars[var_name] = var_value;
        state_vars_list.push_back(var_name);
    }

    cin >> num_txn;
    for (int i = 0; i < num_txn; i++) {
        TxnID txnID; cin >> txnID;
        Transaction *txn = new Transaction(txnID, state_vars);

        cin >> txn->num_ops;
        for (int i = 0; i < txn->num_ops; i++) {
            Operation *op = input_op();
            txn->operations.push_back(op);
        }

        transactions.push_back(txn);
    }

    lkm = new LockMgr(state_vars_list);

    vector<thread> threads;
    for (int i = 0; i < num_txn; i++) {
        threads.push_back(thread(execute_transaction, transactions[i]));
    }

    for (int i = 0; i < num_txn; i++) {
        threads[i].join();
    }

    cout << "Completed Successfully\n";
    cout << "Printing state variables: \n";
    for (auto &p : state_vars) {
        cout << p.first << " = " << p.second << '\n';
    }

    return 0;
}
