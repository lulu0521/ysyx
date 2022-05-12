// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VSW_C.h for the primary calling header

#ifndef VERILATED_VSW_C___024ROOT_H_
#define VERILATED_VSW_C___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class VSW_C__Syms;

//----------

VL_MODULE(VSW_C___024root) {
  public:

    // PORTS
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_OUT16(led,15,0);

    // LOCAL SIGNALS
    IData/*31:0*/ SW_C__DOT__count;

    // LOCAL VARIABLES
    CData/*0:0*/ __Vclklast__TOP__clk;

    // INTERNAL VARIABLES
    VSW_C__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(VSW_C___024root);  ///< Copying not allowed
  public:
    VSW_C___024root(const char* name);
    ~VSW_C___024root();

    // INTERNAL METHODS
    void __Vconfigure(VSW_C__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
