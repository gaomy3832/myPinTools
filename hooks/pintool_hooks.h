#ifndef PINTOOL_HOOKS_H_
#define PINTOOL_HOOKS_H_

#include <stdint.h>
#include <stdio.h>
#include "../include/magic_op_code.h"

// Avoid optimizing compilers moving code around this barrier
#define COMPILER_BARRIER() { __asm__ __volatile__("" ::: "memory");}

#ifdef __x86_64__
#define HOOKS_STR  "HOOKS"
static inline void pintool_magic_op(uint64_t op) {
    COMPILER_BARRIER();
    __asm__ __volatile__("xchg %%rcx, %%rcx;" : : "c"(op));
    COMPILER_BARRIER();
}
#else
#define HOOKS_STR  "NOP-HOOKS"
static inline void pintool_magic_op(uint64_t op) {
    //NOP
}
#endif

static inline void pintool_roi_begin() {
    //printf("[" HOOKS_STR "] ROI begin\n");
    pintool_magic_op(PINTOOL_MAGIC_OP_ROI_BEGIN);
}

static inline void pintool_roi_end() {
    pintool_magic_op(PINTOOL_MAGIC_OP_ROI_END);
    //printf("[" HOOKS_STR  "] ROI end\n");
}

#endif // PINTOOL_HOOKS_H_
