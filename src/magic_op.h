#ifndef MAGIC_OP_H_
#define MAGIC_OP_H_

#include <functional>
#include "pin.H"
#include "magic_op_code.h"

typedef std::function<void(void)> Callback;

VOID RegisterMagicOpCallback(ADDRINT op, const Callback& cb);

VOID DetectMagicOp(INS ins);

static inline VOID RegisterROIBeginCallback(const Callback& cb) {
    RegisterMagicOpCallback(PINTOOL_MAGIC_OP_ROI_BEGIN, cb);
}

static inline VOID RegisterROIEndCallback(const Callback& cb) {
    RegisterMagicOpCallback(PINTOOL_MAGIC_OP_ROI_END, cb);
}

#endif // MAGIC_OP_H_
