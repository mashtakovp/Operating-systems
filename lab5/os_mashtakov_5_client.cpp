#include <iostream>
#include <Windows.h>

#define PIPE_NAME "\\\\.\\pipe\\Pipe"

using namespace std;

int main()
{
    HANDLE pipe = CreateFile(TEXT(PIPE_NAME), //����������� � ������������ ������
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (pipe == INVALID_HANDLE_VALUE) { //���� �� ������� ������������
        cout << "Error: can not connect to the pipe.\n";
        system("pause");
        return - 1;
    }

    //������� �������
    int sizeX = 2;
    int sizeY = 2;
    int v;

    WriteFile(pipe, &sizeX, sizeof(int), NULL, NULL);//���������� � ����� ������� �������
    WriteFile(pipe, &sizeY, sizeof(int), NULL, NULL);
    //int** matrix = new int* [sizeX];
    cout << "Enter " << sizeX << 'x' << sizeY << " matrix:\n";
    for (int i = 0; i < sizeX; i++) {
      //  matrix[i] = new int[sizeY];
        for (int j = 0; j < sizeY; j++) {
            cin >> v;
            WriteFile(pipe, &v, sizeof(int), NULL, NULL);//������ � ����� ��������� ������� (�����������)
        }
    }
    
    if (!ReadFile(pipe, &sizeX, sizeof(int), NULL, NULL)) { //���� ������ �� ������ �� �������
        return -1;
    }

    if (!ReadFile(pipe, &sizeY, sizeof(int), NULL, NULL)) { //���� ������ �� ������ �� �������
        return -1;
    }

    cout << "result sizes: ";
    cout << sizeX << ' ' << sizeY << endl;
    cout << "\nresult:\n";

    //����� ���������� �������� � �������
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (ReadFile(pipe, &v, sizeof(int), NULL, NULL)) {
                cout << v << ' ';
            }
            else { //���� �������� ������ ��� ������
                cout << "err\n";
                return -1;
            }
        }
        cout << endl;
    }

    system("pause");
}