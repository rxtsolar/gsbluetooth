#ifndef GS_RFCOMM_SERVER_H
#define GS_RFCOMM_SERVER_H

#include "rfcomm-socket.h"

#include <iostream>

namespace gs {

using namespace std;

class RfcommServer {
public:
	void accept(void)
	{
		serverSock.acceptSocket();
	}

	void loop(void)
	{
		while (1) {
			cout << serverSock.getMessage() << endl;
		}
	}

private:
	ServerRfcommSocket serverSock;
};

}

#endif
