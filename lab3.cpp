#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#define DEFAULT_BUFFSIZE 128;
using namespace std;
vector<int> getDividers(int n);
vector<int> getRoots(vector<int> polymnome);
vector<int> polynomeDivision(vector<int> polynome, int root);
bool headOnly(vector<int> polynome);
int main(int argc, char** argv){
    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    if(argc>1){
        if(!strcmp(argv[1],"--help")){
            cout<<"Usage: lab_3\n"
                  "\t--help\tPrint this text and exit\n"
                  "After start enter number of polynome coefficients, including zeros and all coefficients\n";
        }else {
            cout << "lab3: Unexpected argument\nUse lab3 --help for more information\n";
        }
        return 0;
    }
    pid_t pid =  fork();
    
    if(pid==0){
        vector<int> polynome;
        int n;
        int p;
        
        read(pipe1[0], &n, sizeof(int));
        for(int i=0; i<n; i++){
            read(pipe1[0], &p, sizeof(int));
            polynome.push_back(p);
        }
        vector<int> roots = getRoots(polynome);
        n = roots.size();
        write(pipe2[1], &n, sizeof(int));
        for(int i=0; i<n; i++){
            write(pipe2[1], &roots[i], sizeof(int));
        }
    }
    else{
        int n;
        int p;
        cin >> n;
        write(pipe1[1], &n, sizeof(int));
        for(int i=0; i<n; i++){
            cin >> p;
            write(pipe1[1], &p, sizeof(int));
        }
        read(pipe2[0], &n, sizeof(int));
        for(int i=0; i<n; i++){
            read(pipe2[0], &p, sizeof(int));
            cout << p << ' ';
        }
        cout << endl;
    }
    return 0;
}

vector<int> getDividers(int n){
    if(n<0) n *=-1;
    vector<int> dividers;
    int d=1;
    dividers.push_back(d);
    dividers.push_back(d*-1);
    while(d<n){
        d++;
        if(!(n%d)) {
            dividers.push_back(d);
            dividers.push_back(d*-1);
        }
    }
    return dividers;
}

// поиск целых корней многочлена методом Горнера
vector<int> getRoots(vector<int> polynome){
    vector<int> dividers = getDividers(polynome[polynome.size()-1]); // находим все делители свободного члена
    vector<int> newPolynome;
    vector<int> roots;
    int i=0;
    do{
        newPolynome = polynomeDivision(polynome, dividers[i]); // выполняем деление многочлена на многочлен (x-r) по схеме Горнера
        if(newPolynome[newPolynome.size()-1]==0){ // если последний коэффициент нулевой, данный делитель - корень 
            polynome = newPolynome; // далее работаем с частным
            roots.push_back(dividers[i]); // cохраням корень
        }
        else i++; // если не является корнем многочлена, переходим к следующему
    }while(!headOnly(polynome) && i!=dividers.size()); // выполняем пока не проверили все делители или не нашли все корни
    return roots;
}

vector<int> polynomeDivision(vector<int> polynome, int root){
    vector<int> newPolynome;
    newPolynome.push_back(polynome[0]);
    for(int i=1; i<polynome.size(); i++){
        newPolynome.push_back(newPolynome[i-1]*root+polynome[i]);
    }
    return newPolynome;
}

bool headOnly(vector<int> polynome){
    for(int i=1; i<polynome.size(); i++){
        if(polynome[i]!=0) return 0;
    }        
    return 1;
}
    
