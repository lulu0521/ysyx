#include <common.h>
#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <debug.h>

static Context* do_event(Event e, Context* c) {
  switch (e.event) {
    case EVENT_YIELD:printf("yield\n");break;
    default: panic("Unhandled event ID = %d", e.event);
  }
  return c;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");

  cte_init(do_event);
}
