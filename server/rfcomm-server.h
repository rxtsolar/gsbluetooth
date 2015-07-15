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
		serverSock.setRecvTimeout(1);
		while (1) {
			string message;
			while (!serverSock.getMessage(message)) {
				cout << "waiting" << endl;
			}
			cout << "got message: " << message << endl;
		}
	}

private:
	ServerRfcommSocket serverSock;
};

}

#endif
