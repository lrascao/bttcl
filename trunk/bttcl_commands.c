/*


*/

#include <tcl.h>
#include "bttcl.h"
#include "bt.h"

/*

*/
int tcl_btscan(ClientData clientData,
	Tcl_Interp *interp,
	int argc,
	char *argv[]) {
	char buffer_out[50000], buffer[1024];	
	BT_SCAN_LIST_OUT *out;  
	int i, len;
	short get_name = 0;

	/* See if the -name option has been passed*/
	if ((argc > 1) && (strcmp(argv[1], "-name") == 0)) {
	   get_name = 1;
	}
	
	out = bt_scan(get_name);
	for (i = 0; i < out->n; i++) {  
		sprintf(buffer, "{%s %s}", out->list[i].peer, out->list[i].name);
		
		strcat(buffer_out, buffer);
		
		if (out->n > 0) {
			strcat(buffer_out, " ");
		}
	}
	
	/* Set the TCL result */
	Tcl_SetResult(interp, buffer_out, NULL);
	
	return TCL_OK;
}
