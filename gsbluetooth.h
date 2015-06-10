#ifndef GSBLUETOOTH_H

#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

namespace gs {

class Scan {
public:
	Scan(void);
	~Scan(void);

	void inquiry(void);
	void list(void);

private:
	std::vector<std::string> addresses;
	std::vector<std::string> names;

	inquiry_info* info;
	int max_rsp;
	int num_rsp;
	int dev_id;
	int sock;
	int len;
	int flags;
};

}

#endif
