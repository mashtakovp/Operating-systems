#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <deque>
#include <mutex>
#include <string>
#include <time.h>

#define PIPE_NAME "\\\\.\\pipe\\Pipe"

using namespace std;

ofstream fout;

class matrix {
private:
    int sizeX;
    int sizeY;
    int* matrixArray;
    HANDLE clientPipe;

public:
    matrix(int sizeX, int sizeY) {
        this->sizeX = sizeX;
        this->sizeY = sizeY;

        matrixArray = new int[sizeX * sizeY];
    }

    int set(const int& iX, const int& iY, int value) {
        if (iX >= sizeX || iY >= sizeY)
            return -1;
        matrixArray[iY + sizeY * iX] = value;
        return 0;
    }

    int get(const int& iX, const int& iY) {
        return matrixArray[iY + sizeY * iX];
    }

    bool operator==(const matrix& m) {
        if (sizeX == m.sizeX && sizeY == m.sizeY) {
            return 1;
        }
        return 0;
    }

    matrix operator+(matrix& m) {
        matrix result(sizeX, sizeY);
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                result.set(i, j, this->get(i, j) + m.get(i, j));
            }
        }
        return result;
    }

    void send(void* param) {
        HANDLE pipe = (HANDLE)param;
        DWORD dwWrite = 0;
        WriteFile(pipe, &sizeX, sizeof(int), &dwWrite, NULL);
        WriteFile(pipe, &sizeX, sizeof(int), &dwWrite, NULL);
        for (int i = 0; i < sizeX * sizeY; i++) {
            int v = *(matrixArray + i);
            WriteFile(pipe, &v, sizeof(int), &dwWrite, NULL);
        }
    }

    void setClientPipe(void* param) {
        this->clientPipe = (HANDLE)param;
    }

    void* getClientPipe() {
        return (void*)clientPipe;
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

deque<matrix> queue;
mutex queueMutex;

int main()
{
    ifstream ifs("current_log.txt");
    ofstream ofs("previous_log.txt");
    string s;
    getline(ifs, s, '\0');
    ofs << s;
    ifs.close();
    ofs.close();
    fout.open("current_log.txt");
    thread adderThread(&adder);
    adderThread.detach();

    while (1) {
        HANDLE pipe = CreateNamedPipe(
            TEXT(PIPE_NAME), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, PIPE_UNLIMITED_INSTANCES, 1, 1, 0, NULL);
        if (ConnectNamedPipe(pipe, NULL)) {
            time_t rawtime;
            struct tm* timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            fout << "[" << asctime(timeinfo) << "] " << "Client connected.\n";
            thread clientThread(&clientProcessingThread, (void*)pipe);
            clientThread.detach();
        }
    }
}

void adder() {
    while (1) {
        queueMutex.lock();
        if (queue.size() >= 2) {
            time_t rawtime;
            struct tm* timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            fout << "[" << asctime(timeinfo) << "] " << "Got two matrices.\n";
            matrix m1 = queue[0];
            queue.pop_front();
            matrix m2 = queue[0];
            queue.pop_front();
            queueMutex.unlock();
            matrix sum = m1 + m2;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            fout << "[" << asctime(timeinfo) << "] " << "sum:\n";
            for (int i = 0; i < sum.getSizeX(); i++) {
                for (int j = 0; j < sum.getSizeY(); j++) {
                    fout << sum.get(i, j) << ' ';
                }
                fout << endl;
            }
            HANDLE pipe1 = (HANDLE)m1.getClientPipe();
            HANDLE pipe2 = (HANDLE)m2.getClientPipe();
            sum.send((void*)pipe1);
            //FlushFileBuffers(pipe1);
            //DisconnectNamedPipe(pipe1);
            sum.send((void*)pipe2);
            //FlushFileBuffers(pipe2);
            //DisconnectNamedPipe(pipe2);
        }
        else {
            queueMutex.unlock();
        }
    }
}

int clientProcessingThread(void* param) {
    int sizeX;
    int sizeY;
    int v;


    DWORD dwWrite = 0;
    DWORD dwRead = 0;

    HANDLE pipe = (HANDLE)param;

    if (!ReadFile(pipe, &sizeX, sizeof(int), &dwRead, NULL) || dwRead == 0) {
        fout << "Error: Client disconnected!";
        return -1;
    }

    if (!ReadFile(pipe, &sizeY, sizeof(int), &dwRead, NULL) || dwRead == 0) {
        fout << "Error: Client disconnected!";
        return -1;
    }

    matrix m(sizeX, sizeY);

    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (!ReadFile(pipe, &v, sizeof(int), &dwRead, NULL) || dwRead == 0) {
                fout << "Error: Client disconnected!";
                return -1;
            }
            m.set(i, j, v);
        }
    }
    m.setClientPipe((void*)pipe);
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fout << "[" << asctime(timeinfo) << "] " << "Got a matrix form client\n";
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            fout << m.get(i, j) << ' ';
        }
        fout << endl;
    }
    queueMutex.lock();
    queue.push_back(m);
    queueMutex.unlock();
    //FlushFileBuffers(pipe);
    //DisconnectNamedPipe(pipe);
}