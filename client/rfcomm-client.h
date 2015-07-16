#ifndef GS_RFCOMM_CLIENT_H
#define GS_RFCOMM_CLIENT_H

#include "../rfcomm-socket.h"

#include <iostream>

namespace gs {

using namespace std;

class RfcommClient {
public:
	RfcommClient(const string& bd) : clientSock(bd)
	{
	}

	void connect(void)
	{
		clientSock.connectSocket();
	}

	void loop(void)
	{
		string message;
		while (1) {
			cin >> message;
			clientSock.sendMessage(message);
		}
	}

private:
	ClientRfcommSocket clientSock;
};

}

#endif
