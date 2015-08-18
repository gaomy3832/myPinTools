#include <iostream>
#include <fstream>
#include "pin.H"
#include "magic_op.h"

// Total instruction count in ROI.
static UINT64 icnt = 0;
// Total ROI count.
static UINT32 rcnt = 0;

// Output file handler.
ofstream outFileHdl;

/*
 * Trace instrumentation.
 *
 * BBL function bblFunc counts number of instructions if within ROI, or does
 * nothing elsewhere.
 */
VOID PIN_FAST_ANALYSIS_CALL noCount(UINT32 c) {}
VOID PIN_FAST_ANALYSIS_CALL doCount(UINT32 c) { icnt += c; }

VOID (*bblFunc)(UINT32 c) = noCount;

VOID Trace(TRACE trace, VOID* v) {
    for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl)) {
        BBL_InsertCall(bbl, IPOINT_ANYWHERE,
                AFUNPTR(bblFunc),
                IARG_UINT32, BBL_NumIns(bbl),
                IARG_END);
    }

    // To detect magic op.
    for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl)) {
        for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins = INS_Next(ins)) {
            DetectMagicOp(ins);
        }
    }
}

/*
 * Image instrumentation.
 *
 * beforeROI and afterROI switch bblFunc, and also count number of ROIs.
 */
void beforeROI() {
    bblFunc = doCount;
    rcnt++;
}

void afterROI() {
    bblFunc = noCount;
}

/*
 * Application exit.
 */
VOID Fini(INT32 code, VOID *v)
{
    // Write to a file since cout and cerr maybe closed by the application.
    if (outFileHdl.is_open()) {
        outFileHdl.setf(ios::showbase); // show numerical base prefixes
        outFileHdl << "===============================================" << endl;
        outFileHdl << "RegionInsCount analysis results:" << endl;
        outFileHdl << "Region count: " << rcnt << endl;
        outFileHdl << "Instruction count: " << icnt << endl;
        outFileHdl << "Average instruction per region: " << (float)icnt / rcnt << endl;
        outFileHdl << "===============================================" << endl;
        outFileHdl.close();
    }
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
        "o", "", "specify output file name");

INT32 Usage() {
    cerr << "This tool counts the number of dynamic instructions executed within the annotated regions." << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return 1;
}


int main(int argc, char * argv[]) {
    // Initialize symbol table code, needed for RTN instrumentation.
    PIN_InitSymbols();
    // Initialize Pin.
    if (PIN_Init(argc, argv)) return Usage();
    // Output file.
    if (!KnobOutputFile.Value().empty()) {
        outFileHdl.open(KnobOutputFile.Value().c_str());
    }

    RegisterROIBeginCallback(beforeROI);
    RegisterROIEndCallback(afterROI);

    TRACE_AddInstrumentFunction(Trace, 0);

    PIN_AddFiniFunction(Fini, 0);

    // Start the program, never returns
    PIN_StartProgram();

    return 0;
}
