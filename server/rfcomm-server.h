#ifndef GS_RFCOMM_SERVER_H
#define GS_RFCOMM_SERVER_H

#include "../rfcomm-socket.h"

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
		cout << "connected" << endl;
		while (1) {
			string message;
			while (!serverSock.getMessage(message)) {
				if (!serverSock.isConnected()) {
					cout << "disconnected" << endl;
					serverSock.closeSocket();
					return;
				}
			}
			cout << "got message: " << message << endl;
		}
	}

private:
	ServerRfcommSocket serverSock;
};

}

#endif
