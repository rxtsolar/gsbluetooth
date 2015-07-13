#include "rfcomm-server.h"

using namespace gs;

int main(void)
{
	RfcommServer server;
	while (1) {
		server.accept();
		server.loop();
	}
	return 0;
}
