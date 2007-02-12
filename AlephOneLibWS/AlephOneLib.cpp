#include <WScom.h>
#include <WSDexternal.h>

static char *object_symbols[] = {
NULL
};

class  _dll_init {
  public:
  _dll_init(){
#ifndef WS_EMBED
     WSDexternal::setTempData(object_symbols);
     WSDexternal::setProjectName("AlephOneLib");
#endif
  }
};
static _dll_init _execute_initialize;

