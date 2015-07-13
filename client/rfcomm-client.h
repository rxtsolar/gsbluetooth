#ifndef GS_RFCOMM_CLIENT_H
#define GS_RFCOMM_CLIENT_H

#include "rfcomm-socket.h"

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
		clientSock.sendMessage("hello");
	}

private:
	ClientRfcommSocket clientSock;
};

}

#endif
