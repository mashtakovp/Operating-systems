#include <iostream>
#include <Windows.h>

#define PIPE_NAME "\\\\.\\pipe\\Pipe"

using namespace std;

int main()
{
    HANDLE pipe = CreateFile(TEXT(PIPE_NAME), //подключение к именованному каналу
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (pipe == INVALID_HANDLE_VALUE) { //если не удалось подключиться
        cout << "Error: can not connect to the pipe.\n";
        system("pause");
        return - 1;
    }

    //размеры матрицы
    int sizeX = 2;
    int sizeY = 2;
    int v;

    WriteFile(pipe, &sizeX, sizeof(int), NULL, NULL);//записываем в канал размеры матрицы
    WriteFile(pipe, &sizeY, sizeof(int), NULL, NULL);
    //int** matrix = new int* [sizeX];
    cout << "Enter " << sizeX << 'x' << sizeY << " matrix:\n";
    for (int i = 0; i < sizeX; i++) {
      //  matrix[i] = new int[sizeY];
        for (int j = 0; j < sizeY; j++) {
            cin >> v;
            WriteFile(pipe, &v, sizeof(int), NULL, NULL);//запись в канал элементов матрицы (поэлементно)
        }
    }
    
    if (!ReadFile(pipe, &sizeX, sizeof(int), NULL, NULL)) { //если чтение из канала не удалось
        return -1;
    }

    if (!ReadFile(pipe, &sizeY, sizeof(int), NULL, NULL)) { //если чтение из канала не удалось
        return -1;
    }

    cout << "result sizes: ";
    cout << sizeX << ' ' << sizeY << endl;
    cout << "\nresult:\n";

    //вывод результата сложения в консоль
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (ReadFile(pipe, &v, sizeof(int), NULL, NULL)) {
                cout << v << ' ';
            }
            else { //если возникла ошибка при чтении
                cout << "err\n";
                return -1;
            }
        }
        cout << endl;
    }

    system("pause");
}