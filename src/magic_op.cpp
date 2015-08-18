#include "magic_op.h"
#include <iostream>
#include <unordered_map>

static std::unordered_map<ADDRINT, Callback> cbMap;

VOID HandleMagicOp(ADDRINT op) {
    if (cbMap.count(op)) cbMap[op]();
}

VOID RegisterMagicOpCallback(ADDRINT op, const Callback& cb) {
    cbMap[op] = cb;
}

VOID DetectMagicOp(INS ins) {
    if (INS_IsXchg(ins) && INS_OperandReg(ins, 0) == REG_RCX && INS_OperandReg(ins, 1) == REG_RCX) {
        INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(HandleMagicOp), IARG_REG_VALUE, REG_ECX, IARG_END);
    }
}

