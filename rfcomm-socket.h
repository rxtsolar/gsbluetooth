#ifndef GS_RFCOMM_SOCKET_H
#define GS_RFCOMM_SOCKET_H

#include <string>
#include <cstdio>
#include <cstdlib>

#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

namespace gs {

using namespace std;

class RfcommSocket {
public:
	RfcommSocket(void)
	{
		addr.rc_family = AF_BLUETOOTH;
		addr.rc_channel = (uint8_t)1;
		sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
		if (sock < 0) {
			perror("socket");
			exit(-1);
		}
	}

	RfcommSocket(int fd)
	{
		sock = fd;
		addr.rc_family = AF_BLUETOOTH;
		addr.rc_channel = (uint8_t)1;
		sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
		if (sock < 0) {
			perror("socket");
			exit(-1);
		}
	}

	void setSocket(int fd)
	{
		sock = fd;
	}

	int getSocket(void) const
	{
		return sock;
	}

	void setBD(const string& bd)
	{
		str2ba(bd.c_str(), &addr.rc_bdaddr);
	}

	int setRecvTimeout(int seconds)
	{
		timeval timeout;
		timeout.tv_sec = seconds;
		timeout.tv_usec = 0;
		return setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,
				(char*)&timeout, sizeof(timeout));
	}

	int setSendTimeout(int seconds)
	{
		timeval timeout;
		timeout.tv_sec = seconds;
		timeout.tv_usec = 0;
		return setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO,
				(char*)&timeout, sizeof(timeout));
	}

	int sendSocket(const char* data, int len) const
	{
		return send(sock, data, len, 0);
	}

	int sendSocket(const string& data) const
	{
		return sendSocket(data.c_str(), data.size());
	}

	int recvSocket(char* data, int len) const
	{
		return recv(sock, data, len, 0);
	}

	int recvSocket(string& data) const
	{
		char buffer[2048];
		memset(buffer, 0, 2048);
		int ret = recvSocket(buffer, 2048);
		data = string(buffer);
		return ret;
	}

	int closeSocket(void)
	{
		return close(sock);
	}

	int operator == (const RfcommSocket& s) const
	{
		return sock == s.getSocket();
	}

protected:
	int sock;
	sockaddr_rc addr;
};

class ServerRfcommSocket : public RfcommSocket {
public:
	ServerRfcommSocket(void)
	{
		memset(&addr.rc_bdaddr, 0, sizeof(addr.rc_bdaddr));
		acceptLen = sizeof(acceptAddr);

		if (bind(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
			perror("bind");
			exit(-1);
		}

		if (listen(sock, 1) < 0) {
			perror("listen");
			exit(-1);
		}
	}

	~ServerRfcommSocket(void)
	{
		closeSocket();
	}

	void acceptSocket(void)
	{
		int s = accept(sock, (sockaddr*)&acceptAddr, &acceptLen);
		if (s < 0) {
			perror("accept");
			exit(-1);
		}
		connectSock.setSocket(s);
	}

	void closeSocket(void)
	{
		connectSock.closeSocket();
	}

	void setRecvTimeout(int seconds)
	{
		if (connectSock.setRecvTimeout(seconds) < 0) {
			perror("setsockopt");
			exit(-1);
		}
	}

	void setSendTimeout(int seconds)
	{
		if (connectSock.setSendTimeout(seconds) < 0) {
			perror("setsockopt");
			exit(-1);
		}
	}

	void sendMessage(const string& message)
	{
		connectSock.sendSocket(message);
	}

	bool getMessage(string& message)
	{
		if (connectSock.recvSocket(message) < 0)
			return false;
		return true;
	}

	bool isConnected(void)
	{
		if (connectSock.sendSocket("test") < 0)
			return false;
		return true;
	}

protected:
	RfcommSocket connectSock;
	sockaddr_rc acceptAddr;
	socklen_t acceptLen;
};

class ClientRfcommSocket : public RfcommSocket {
public:
	ClientRfcommSocket(const string& bd)
	{
		setBD(bd);
	}

	void connectSocket(void)
	{
		if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
			perror("connect");
			exit(-1);
		}
	}

	void sendMessage(const string& message)
	{
		sendSocket(message);
	}

	string getMessage(void)
	{
		string message;
		recvSocket(message);
		return message;
	}
};

}

#endif
