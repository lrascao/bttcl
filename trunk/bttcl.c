#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>

#include "bttcl.h"

int Bttcl_Init(Tcl_Interp *interp) {

   if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
      
      return TCL_ERROR;
   }

   /* Create the various commands */   
   Tcl_CreateCommand(interp, TCL_COMMAND_NAME_SCAN, tcl_btscan, NULL, NULL);
   
   return Tcl_PkgProvide(interp, "bttcl", "0.1");
}
