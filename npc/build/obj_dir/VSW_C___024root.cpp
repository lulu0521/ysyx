// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSW_C.h for the primary calling header

#include "VSW_C___024root.h"
#include "VSW_C__Syms.h"

//==========

VL_INLINE_OPT void VSW_C___024root___sequent__TOP__1(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___sequent__TOP__1\n"); );
    // Variables
    SData/*15:0*/ __Vdly__led;
    IData/*31:0*/ __Vdly__SW_C__DOT__count;
    // Body
    __Vdly__SW_C__DOT__count = vlSelf->SW_C__DOT__count;
    __Vdly__led = vlSelf->led;
    if (vlSelf->rst) {
        __Vdly__led = 1U;
        __Vdly__SW_C__DOT__count = 0U;
    } else {
        if ((0U == vlSelf->SW_C__DOT__count)) {
            __Vdly__led = ((0xfffeU & ((IData)(vlSelf->led) 
                                       << 1U)) | (1U 
                                                  & ((IData)(vlSelf->led) 
                                                     >> 0xfU)));
        }
        __Vdly__SW_C__DOT__count = ((0x4c4b40U <= vlSelf->SW_C__DOT__count)
                                     ? 0U : ((IData)(1U) 
                                             + vlSelf->SW_C__DOT__count));
    }
    vlSelf->led = __Vdly__led;
    vlSelf->SW_C__DOT__count = __Vdly__SW_C__DOT__count;
}

void VSW_C___024root___eval(VSW_C___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSW_C__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSW_C___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        VSW_C___024root___sequent__TOP__1(vlSelf);
    }
    // Final
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
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
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
