// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSW_C.h for the primary calling header

#include "VSW_C___024root.h"
#include "VSW_C__Syms.h"

//==========


void VSW_C___024root___ctor_var_reset(VSW_C___024root* vlSelf);

VSW_C___024root::VSW_C___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    VSW_C___024root___ctor_var_reset(this);
}

void VSW_C___024root::__Vconfigure(VSW_C__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

VSW_C___024root::~VSW_C___024root() {
}

void VSW_C___024root___eval_initial(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___eval_initial\n"); );
}

void VSW_C___024root___combo__TOP__1(VSW_C___024root* vlSelf);

void VSW_C___024root___eval_settle(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___eval_settle\n"); );
    // Body
    VSW_C___024root___combo__TOP__1(vlSelf);
}

void VSW_C___024root___final(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___final\n"); );
}

void VSW_C___024root___ctor_var_reset(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->a = 0;
    vlSelf->b = 0;
    vlSelf->f = 0;
}
