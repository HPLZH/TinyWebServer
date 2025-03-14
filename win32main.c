#include "global.h"

WSADATA wsaData;

int win32_main() 
{
	int iResult;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	struct addrinfo* result = NULL, * ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, port, &hints, &result);
	if (iResult != 0) 
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) 
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) 
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(result);



	while (1)
	{
		if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) 
		{
			printf("Listen failed with error: %ld\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		SOCKET ClientSocket = INVALID_SOCKET;
		SOCKADDR ClientAddr;
		memset(&ClientAddr, 0, sizeof(ClientAddr));
		int ClientAddrLength = 16;

		// Accept a client socket
		ClientSocket = accept(ListenSocket, &ClientAddr, &ClientAddrLength);
		if (ClientSocket == INVALID_SOCKET) 
		{
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		PTARGS argp = malloc(sizeof(TARGS));
		if (argp) 
		{
			argp->socket = ClientSocket;
			argp->sockaddr = ClientAddr;
			argp->addrlen = ClientAddrLength;

			HANDLE thread = CreateThread(NULL, 0, win32_thread, argp, 0, NULL);
			{
				if (thread) CloseHandle(thread);
			}
		}
	}
}
