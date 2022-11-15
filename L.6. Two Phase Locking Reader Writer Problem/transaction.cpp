#include "transaction.h"

Transaction::Transaction(TxnID txnID, std::map<VarType, VarValue> &state_vars) : id(txnID)
{
    operations = std::vector<Operation*>();
    outcome = Outcome::Running;

    for (auto &p : state_vars) {
        locks[p.first] = Lock::Unlocked;
        local_vars[p.first] = p.second;
    }
}
