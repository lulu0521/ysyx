// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VSW_C.h"
#include "VSW_C__Syms.h"

//============================================================
// Constructors

VSW_C::VSW_C(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new VSW_C__Syms(_vcontextp__, _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , f{vlSymsp->TOP.f}
    , rootp{&(vlSymsp->TOP)}
{
}

VSW_C::VSW_C(const char* _vcname__)
    : VSW_C(nullptr, _vcname__)
{
}

//============================================================
// Destructor

VSW_C::~VSW_C() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void VSW_C___024root___eval_initial(VSW_C___024root* vlSelf);
void VSW_C___024root___eval_settle(VSW_C___024root* vlSelf);
void VSW_C___024root___eval(VSW_C___024root* vlSelf);
QData VSW_C___024root___change_request(VSW_C___024root* vlSelf);
#ifdef VL_DEBUG
void VSW_C___024root___eval_debug_assertions(VSW_C___024root* vlSelf);
#endif  // VL_DEBUG
void VSW_C___024root___final(VSW_C___024root* vlSelf);

static void _eval_initial_loop(VSW_C__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    VSW_C___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        VSW_C___024root___eval_settle(&(vlSymsp->TOP));
        VSW_C___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = VSW_C___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/majianlu/ysyx-workbench/npc/vsrc/SW_C.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = VSW_C___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

void VSW_C::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VSW_C::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VSW_C___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        VSW_C___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = VSW_C___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/majianlu/ysyx-workbench/npc/vsrc/SW_C.v", 1, "",
                "Verilated model didn't converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = VSW_C___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

//============================================================
// Invoke final blocks

void VSW_C::final() {
    VSW_C___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Utilities

VerilatedContext* VSW_C::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* VSW_C::name() const {
    return vlSymsp->name();
}
