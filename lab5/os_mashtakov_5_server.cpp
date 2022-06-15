#include <iostream>
#include <Windows.h>
#include <thread>
#include <deque>
#include <mutex>

#define PIPE_NAME "\\\\.\\pipe\\Pipe"

using namespace std;

//класс матрицы для упрощения работы
class matrix {
private:
    int sizeX;
    int sizeY;
    int* matrixArray;
    HANDLE clientPipe;

public:
    matrix(int sizeX, int sizeY) {//конструктор
        this->sizeX = sizeX;
        this->sizeY = sizeY;

        matrixArray = new int[sizeX*sizeY];
    }

    int set(const int& iX, const int& iY, int value) {//установка элемента по индексам
        if (iX >= sizeX || iY >= sizeY)
            return -1;
        matrixArray[iY+sizeY*iX] = value;
        return 0;
    }

    int get(const int& iX, const int& iY) {//получение элемента по индексам
        return matrixArray[iY + sizeY * iX];
    }

    bool operator==(const matrix& m) {//оператор сравнения на строгое равенство
        if (sizeX == m.sizeX && sizeY == m.sizeY) {
            return 1;
        }
        return 0;
    }

    matrix operator+(matrix& m) {//оператор сложения
        matrix result(sizeX, sizeY);
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                result.set(i, j, this->get(i, j) + m.get(i, j));
            }
        }
        return result;
    }

    void send(void* param) {
        HANDLE pipe = (HANDLE)param;//наш канал
        DWORD dwWrite = 0;
        WriteFile(pipe, &sizeX, sizeof(int), &dwWrite, NULL);//запись в канал размеров
        WriteFile(pipe, &sizeX, sizeof(int), &dwWrite, NULL);
        for (int i = 0; i < sizeX*sizeY; i++) {
            int v = *(matrixArray + i);
             WriteFile(pipe, &v, sizeof(int), &dwWrite, NULL);//запись в канал элементов матрицы
        }
    }

    void setClientPipe(void* param) {
        this->clientPipe = (HANDLE) param;
    }

    void* getClientPipe() {
        return (void*) clientPipe;
    }

    int getSizeX() {
        return sizeX;
    }

    int getSizeY() {
        return sizeY;
    }
};


// поток обработки клиента. получает матрицу от него, записывает ее в очередь
int clientProcessingThread(void* param);

// поток суммирования матриц. если в очереди не меньше двух матриц, удаляет первые две оттуда, 
// суммирует и отправляет результат клиентам, приславшим эти две матрицы
void adder();

deque<matrix> queue;//дек матриц
mutex queueMutex;

int main()
{
    thread adderThread(&adder);//поток суммирования
    adderThread.detach();

    while (1) {
        HANDLE pipe = CreateNamedPipe(
            TEXT(PIPE_NAME), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, PIPE_UNLIMITED_INSTANCES, 1, 1, 0, NULL);//создание именованного канала
        if (ConnectNamedPipe(pipe, NULL)) {//если подключение прошло успешно
            cout << "Client connected.\n";
            thread clientThread(&clientProcessingThread, (void*)pipe);//создание потока-клиента
            clientThread.detach();
        }
    }
}




void adder() {
    while (1) {
        queueMutex.lock();//захват мьютекса
        if (queue.size() >= 2) {
            cout << "Got two matrices.\n";
            matrix m1 = queue[0];//первая матрица
            queue.pop_front();//удаление ее из очереди
            matrix m2 = queue[0];//вторая матрицы
            queue.pop_front();//удаление ее из очереди
            queueMutex.unlock();//освобождение мьютекса
            matrix sum = m1 + m2;//сложение матриц
            cout << "sum:\n";
            for (int i = 0; i < sum.getSizeX(); i++) {
                for (int j = 0; j < sum.getSizeY(); j++) {
                    cout << sum.get(i, j) << ' '; //запись элементов полученной матриц
                }
                cout << endl;
            }
            HANDLE pipe1 = (HANDLE) m1.getClientPipe();
            HANDLE pipe2 = (HANDLE) m2.getClientPipe();
            sum.send((void*)pipe1);//запись результирующей матрицы в канал (первому клиенту)
            //FlushFileBuffers(pipe1);
            //DisconnectNamedPipe(pipe1);
            sum.send((void*)pipe2);//запись результирующей матрицы в канал (второму клиенту)
            //FlushFileBuffers(pipe2);
            //DisconnectNamedPipe(pipe2);
        }
        else {
            queueMutex.unlock();//освобождение мьютекса
        }
    }
}

int clientProcessingThread(void* param) {
    int sizeX;
    int sizeY;
    int v;


    DWORD dwWrite = 0;
    DWORD dwRead = 0;

    HANDLE pipe = (HANDLE)param;//наш канал

    if (!ReadFile(pipe, &sizeX, sizeof(int), &dwRead, NULL) || dwRead == 0) {//ошибка чтения из канала
        cout << "Error: Client disconnected!";
        return -1;
    }

    if (!ReadFile(pipe, &sizeY, sizeof(int), &dwRead, NULL) || dwRead == 0) {//ошибка чтения из канала
        cout << "Error: Client disconnected!";
        return -1;
    }

    matrix m(sizeX, sizeY);
    //чтение элементов матрицы из канала
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (!ReadFile(pipe, &v, sizeof(int), &dwRead, NULL) || dwRead == 0) {//ошибка чтения из канала
                cout << "Error: Client disconnected!";
                return -1;
            }
            m.set(i, j, v);
        }
    }
    m.setClientPipe((void*)pipe);
    cout << "Got a matrix form client\n";
    for (int i = 0; i < sizeX; i++) {//вывод матрицы в консоль
        for (int j = 0; j < sizeY; j++) {
            cout << m.get(i, j)<<' ';
        }
        cout<<endl;
    }
    queueMutex.lock();//захват мьютекса
    queue.push_back(m);//помещение матрицы в очередь
    queueMutex.unlock();//освобождение мьютекса
    //FlushFileBuffers(pipe);
    //DisconnectNamedPipe(pipe);
}