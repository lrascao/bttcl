/*



*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include "bt.h"


BT_SCAN_LIST_OUT *bt_scan(short get_name) {
	int dev_id, i;
	inquiry_info *info = NULL;
	uint8_t lap[3] = { 0x33, 0x8b, 0x9e };
	int num_rsp, length, flags, dd;
	struct hci_dev_info di;
	BT_SCAN_LIST_OUT *out;
	BT_SCAN_OUT *elem;
	
	length  = 2;	/* ~10 seconds */
	num_rsp = 0;
	flags   = 0;

	dev_id = hci_get_route(NULL);
	if (dev_id < 0) {
		perror("Device is not available");
		return NULL;
	}

	if (hci_devinfo(dev_id, &di) < 0) {
		perror("Can't get device info");
		return NULL;
	}

	num_rsp = hci_inquiry(dev_id, length, num_rsp, lap, &info, flags);
	if (num_rsp < 0) {
		perror("Inquiry failed");
		return NULL;
	}

	dd = hci_open_dev(dev_id);
	if (dd < 0) {
		perror("HCI device open failed");
		free(info);
		return NULL;
	}

	out = (BT_SCAN_LIST_OUT *) malloc(sizeof(BT_SCAN_LIST_OUT));
	out->n = num_rsp;
	out->list = (BT_SCAN_OUT *) malloc(sizeof(BT_SCAN_OUT) * out->n);
	
	for (i = 0; i < num_rsp; i++) {
		
		memset(out->list[i].name, 0, sizeof(out->list[i].name));
			
		ba2str(&(info+i)->bdaddr, out->list[i].peer);

		if (get_name) {
			if (hci_read_remote_name_with_clock_offset(dd,
				&(info+i)->bdaddr,
				(info+i)->pscan_rep_mode,
				(info+i)->clock_offset | 0x8000,
				sizeof(out->list[i].name), out->list[i].name, 100000) < 0) {
			
				strcpy(out->list[i].name, "n/a");
			}
		} else {
			out->list[i].name[0] = '\0';
		}
	
	}
	
	return out;
}
