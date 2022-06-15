#include <iostream>
#include <Windows.h>
#include <string>
#include <thread>
#define PIPE_NAME "\\\\.\\pipe\\Pipe"
#define CLIENT_EXECUTABLE_PATH "C:\\client.exe"

using namespace std;

int clientThreadProc(int* times, void* param) {

	BOOL fSuccess;
	int connectedID;

	DWORD dwWrite = 0;
	DWORD dwRead = 0;

	HANDLE pipe = (HANDLE)param;
	fSuccess = ReadFile(pipe, &connectedID, sizeof(int), &dwRead, NULL);
	if (!fSuccess || dwRead == 0) {
		return -1;
	}
	//cout << "connected Client" << connectedID;
	fSuccess = WriteFile(pipe, &times[connectedID], sizeof(int), &dwWrite, NULL);
	if (!fSuccess || dwWrite==0) {
		return -1;
	}
	FlushFileBuffers(pipe);
	DisconnectNamedPipe(pipe);
	return 0;
}

int connectionThreadProc(void* param, int* times) {
	HANDLE pipe = (HANDLE)param;
	BOOL fConnected = 0;
	while (1) {
		fConnected = ConnectNamedPipe(pipe, NULL);
		if (fConnected) {
			thread clientThread(&clientThreadProc, times, (void*)pipe);
			clientThread.detach();
		}
	}
}

void main()
{
	int number_of_clients = 0;
	cin >> number_of_clients;
	int* times = new int[number_of_clients];
	for (int i = 0; i < number_of_clients; i++) {
		cin >> times[i];
	}

	// PROCESS CREATION PREPARATIONS
	char* hotkeyexe = (char*) CLIENT_EXECUTABLE_PATH;
	char* exedirectory = (char*)"c:\\";
	string cmd("client ");
	PROCESS_INFORMATION pi;
	STARTUPINFOA si;
	ZeroMemory(&si, sizeof(si));

	// PIPE
	HANDLE pipe;
	pipe = CreateNamedPipe(
	TEXT(PIPE_NAME), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, PIPE_UNLIMITED_INSTANCES, 1, 1, 0, NULL);
	
	
	int seconds = 1;
	int clientID = 0;
	
	thread connectionThread(&connectionThreadProc, (void*)pipe, times);
	connectionThread.detach();

	while (clientID<number_of_clients) {
		// генерируем аргументы коммандной строки
		cmd = string("cmd ");
		cmd += to_string(clientID++);
		// запускаем клиент
		if (!CreateProcessA((LPCSTR)hotkeyexe,
			(LPSTR)cmd.c_str(),
			0,
			0,
			0,
			0,
			0, 
			(LPCSTR)exedirectory, &si, &pi))

			cout << ("error");
		//Sleep(1000);
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
