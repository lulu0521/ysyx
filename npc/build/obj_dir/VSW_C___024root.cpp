// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSW_C.h for the primary calling header

#include "VSW_C___024root.h"
#include "VSW_C__Syms.h"

//==========

VL_INLINE_OPT void VSW_C___024root___combo__TOP__1(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___combo__TOP__1\n"); );
    // Body
    vlSelf->f = ((IData)(vlSelf->a) ^ (IData)(vlSelf->b));
}

void VSW_C___024root___eval(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___eval\n"); );
    // Body
    VSW_C___024root___combo__TOP__1(vlSelf);
}

QData VSW_C___024root___change_request_1(VSW_C___024root* vlSelf);

VL_INLINE_OPT QData VSW_C___024root___change_request(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___change_request\n"); );
    // Body
    return (VSW_C___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData VSW_C___024root___change_request_1(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void VSW_C___024root___eval_debug_assertions(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->a & 0xfeU))) {
        Verilated::overWidthError("a");}
    if (VL_UNLIKELY((vlSelf->b & 0xfeU))) {
        Verilated::overWidthError("b");}
}
#endif  // VL_DEBUG
