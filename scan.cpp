#include "gsbluetooth.h"

using namespace std;

namespace gs {

Scan::Scan(void)
{
	dev_id = hci_get_route(0);
	assert(dev_id >= 0);
	sock = hci_open_dev(dev_id);
	assert(sock >= 0);

	len = 8;
	max_rsp = 255;
	flags = IREQ_CACHE_FLUSH;
	info = new inquiry_info[max_rsp];
}

Scan::~Scan(void)
{
	delete[] info;
	close(sock);
}

void Scan::inquiry(void)
{
	int ret;
	char addr[19] = { 0 };
	char name[248] = { 0 };

	num_rsp = hci_inquiry(dev_id, len, max_rsp, 0, &info, flags);
	assert(num_rsp >= 0);

	for (int i = 0; i < num_rsp; i++) {
		ba2str(&info[i].bdaddr, addr);
		addresses.push_back(string(addr));
		memset(name, 0, sizeof(name));
		ret = hci_read_remote_name(sock, &info[i].bdaddr,
				sizeof(name), name, 0);
		if (ret < 0)
			names.push_back(string("[unknown]"));
		else
			names.push_back(string(name));
	}
}

void Scan::list(void)
{
	for (int i = 0; i < num_rsp; i++) {
		cout << addresses[i] << ' ' << names[i] << endl;
	}
}

}
