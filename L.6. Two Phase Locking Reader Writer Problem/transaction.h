#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <map>
#include <vector>
#include <string>

typedef int TxnID;
typedef std::string VarType;
typedef int VarValue;

enum class OpType {
    Read = 1,
    Write,
    Assign,
    Commit,
    Abort
};

enum class Outcome {
    Running,
    Commit = 4,
    Abort
};

enum class Lock {
    Unlocked,
    Read,
    Write
};

class Operation {
public:
    OpType op_type;
    VarType var_name;
    std::string op1;
    std::string op;
    std::string op2;
};


class Transaction {

public:
    TxnID id;
    int num_ops;
    std::vector<Operation*> operations;
    std::map<VarType, Lock> locks;
    std::map<VarType, VarValue> local_vars;
    Outcome outcome;

    Transaction(TxnID txnID, std::map<VarType, VarValue> &state_vars);
};

#endif /* TRANSACTION_H */
