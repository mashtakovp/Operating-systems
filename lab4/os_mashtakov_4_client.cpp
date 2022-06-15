#include <iostream>
#include <Windows.h>

#define PIPE_NAME "\\\\.\\pipe\\Pipe"

using namespace std;

int main(int argc, char** argv)
{
    int seconds = 0;
    int name = atoi(argv[1]);
    DWORD dwRead;
    DWORD dWrite;
    cout << "Starting client" << argv[1] << "\n";
    HANDLE pipe = CreateFile(TEXT("\\\\.\\pipe\\Pipe"),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
    WriteFile(pipe, &name, sizeof(int), &dWrite, NULL);
    ReadFile(pipe, &seconds, sizeof(int), & dwRead, NULL);
    cout << seconds << endl;
    Sleep(seconds * 1000);
    cout << "Ending client" << argv[1] << "\n";
    CloseHandle(pipe);
}