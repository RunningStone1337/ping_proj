#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

// �������� ���������: ������������ ������ ��� ASCII ���������
#ifdef UNICODE
	#define cout std::wcout
#else
	#define cout std::cout
#endif

void InitSock(WSADATA&);

// ������� ������� ���������
int main(int argc, TCHAR* argv[]) {
	WSADATA wsaData;
	
	InitSock(wsaData);
	WSACleanup();
	system("pause");
	return 0;
}

// 
void InitSock(WSADATA& wsaData) {
	int errorStateCode;
	const int sockVersion = 2;
	errorStateCode = WSAStartup(MAKEWORD(sockVersion, sockVersion), &wsaData);
	// �������� �� ������
	if (errorStateCode != 0) {
		cout << TEXT("������ ������������� WinSock #");
		cout << errorStateCode << TEXT(":\n");
		switch (errorStateCode) {
		case WSASYSNOTREADY:
			cout << TEXT("������� ������� ���������� �� ������ � �������� ��������������.\n");
			break;
		case WSAVERNOTSUPPORTED:
			cout << TEXT("����������� ������ ������� �� �������������� ������ ����������� ������� Windows.\n");
			break;
		case WSAEINPROGRESS:
			cout << TEXT("����������� �������� ���������� �������.\n");
			break;
		case WSAEPROCLIM:
			cout << TEXT("���������� ����������� �� ���������� �����, �������������� ����������� ������� Windows.\n");
			break;
		case WSAEFAULT:
			cout << TEXT("������� ������� ������������ ���������.\n");
			break;
		default:
			cout << TEXT("������� ���������� ������� ������������ ��������.\n");
			break;
		}
		exit(1);
	}
	else if (LOBYTE(wsaData.wVersion) != sockVersion ||
	  HIBYTE(wsaData.wVersion) != sockVersion) {
		cout << TEXT("�� ������� ��������� ������ Winsock.dll.\n");
		WSACleanup();
		exit(2);
	}
	else cout << TEXT("�� � �������.\n");
}
