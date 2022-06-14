#include <iostream>
#include <string>
 
using namespace std;
 
const char ch[8] = { '0', '1', '2', '3', '4', '5', '6', '7' };
 
int calc10(string s)
{
    int base = 1,
        res = 0;
    while (s.size())
    {
        res += base * ((int)s[s.size() - 1] - '0');
        s.resize(s.size() - 1);
        base <<= 1;
    }
    return res;
}
 
string calc8(int n)
{
    string s;
    while (n)
    {
        s.insert(s.begin(), ch[n % 8]);
        n /= 8;
    }
    return s;
}
 
int main(){
    setlocale(LC_ALL, "Russian");
    cout << "Введите двоичное число:\n";
    string number;
    cin >> number;
    for (int i = 0; i<number.length(); i++)
    {
        if ((number[i] != '0') && (number[i] != '1'))
        {
            cout<<"Двоичное число состоит только из нулей и единиц!\n";
            return 0;
        }
    }
    cout << "Восьмеричное число:\n";
    int n = calc10(number);
    cout << (calc8(n)) << endl;
    return 0;
}
