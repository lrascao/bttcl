/*


*/

/*
   Structures
*/

typedef struct {
	char name[249];
	char peer[249];
} BT_SCAN_OUT;

typedef struct {
	int n;
	BT_SCAN_OUT *list;
} BT_SCAN_LIST_OUT;

/*
   Command prototypes
*/

BT_SCAN_LIST_OUT *bt_scan(short get_name);
