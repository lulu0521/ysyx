// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Valu__Syms.h"


void Valu___024root__traceInitSub0(Valu___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Valu___024root__traceInitTop(Valu___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Valu___024root__traceInitSub0(vlSelf, tracep);
    }
}

void Valu___024root__traceInitSub0(Valu___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"a", false,-1);
        tracep->declBit(c+2,"b", false,-1);
        tracep->declBit(c+3,"f", false,-1);
        tracep->declBit(c+1,"alu a", false,-1);
        tracep->declBit(c+2,"alu b", false,-1);
        tracep->declBit(c+3,"alu f", false,-1);
    }
}

void Valu___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) VL_ATTR_COLD;
void Valu___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep);
void Valu___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/);

void Valu___024root__traceRegister(Valu___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        tracep->addFullCb(&Valu___024root__traceFullTop0, vlSelf);
        tracep->addChgCb(&Valu___024root__traceChgTop0, vlSelf);
        tracep->addCleanupCb(&Valu___024root__traceCleanup, vlSelf);
    }
}

void Valu___024root__traceFullSub0(Valu___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Valu___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) {
    Valu___024root* const __restrict vlSelf = static_cast<Valu___024root*>(voidSelf);
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Valu___024root__traceFullSub0((&vlSymsp->TOP), tracep);
    }
}

void Valu___024root__traceFullSub0(Valu___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlSelf->a));
        tracep->fullBit(oldp+2,(vlSelf->b));
        tracep->fullBit(oldp+3,(vlSelf->f));
    }
}
