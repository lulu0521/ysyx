// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSW_C__SYMS_H_
#define VERILATED_VSW_C__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODEL CLASS

#include "VSW_C.h"

// INCLUDE MODULE CLASSES
#include "VSW_C___024root.h"

// SYMS CLASS (contains all model state)
class VSW_C__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VSW_C* const __Vm_modelp;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VSW_C___024root                TOP;

    // CONSTRUCTORS
    VSW_C__Syms(VerilatedContext* contextp, const char* namep, VSW_C* modelp);
    ~VSW_C__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
