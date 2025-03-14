#include "global.h"

int linux_main()
{
	int iResult;

	ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): socket create fail\n");
		return 1;
	}

	struct socketaddr_in
	{
		unsigned short int sin_family;
		__uint16_t sin_port;
		struct in_addr sin_addr;
		unsigned char sin_zero[8];
	} serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(atoi(port)); // specify port

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, (const struct sockaddr *)(&serveraddr), sizeof(serveraddr));
	if (iResult != 0)
	{
		printf("bind failed with error: %s\n", strerror(errno));
		closesocket(ListenSocket);
		return 1;
	}

	while (1)
	{
		if (listen(ListenSocket, SOMAXCONN) != 0)
		{
			printf("Listen failed with error\n");
			closesocket(ListenSocket);
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
			printf("accept failed: %s\n", strerror(errno));
			closesocket(ListenSocket);
			return 1;
		}

		PTARGS argp = malloc(sizeof(TARGS));
		if(argp)
		{
			argp->socket = ClientSocket;
			argp->sockaddr = ClientAddr;
			argp->addrlen = ClientAddrLength;

			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
			pthread_t pthr;
			int thread = pthread_create(&pthr, &attr, linux_thread, argp);
		}
	}
	return 0;
}
