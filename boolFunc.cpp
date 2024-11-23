#include <iostream>
#include <string>
#include <algorithm> 
#include <chrono>

using namespace std;

class BoolFunc {
private:
    unsigned long long anf;
    string anfStr;
public:
    // Конструктор класса для инициализации по числу
    BoolFunc(unsigned long long input) : anf(input) {
        anfStr = conv_to_str();
    }

    // Констурктор класса для инициализации по строке
    BoolFunc(const string& input = ""){
        if (input.empty()){
            cout << "Введите ANF через последовательность '0' и '1': ";
            cin >> anfStr; 
        }
        else {
            anfStr = input;
        }
        anf = 0;
        size_t anfStrSize = anfStr.size();
        for(size_t i = 0; i < anfStrSize; i++){
            if(anfStr[anfStrSize - 1 - i] == '1'){
                anf |= (1 << i);
            }
        }
    }
    // Перевод из числа в строку
    string conv_to_str(){
        unsigned long long a = anf;
        string str;
        while (a != 0){
            if (a & 1){
                str.push_back('1');
            }
            else{
                str.push_back('0');
            }
            a = a >> 1;
        }
        reverse(str.begin(), str.end());
        return str;   
    }
    
    // Вывод в виде строки
    void printAnfStr(){
        for(char s : anfStr){
            cout << s;
        }
        cout << endl;
    }

    // Вывод в виде числа
    void printAnf(){
        cout << anf << endl;
    }

    // Вес
    unsigned long long w(){
        unsigned long long x = anf;
        x = x - ((x >> 1) & 0x5555555555555555);
        x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
        x = (x + (x >> 4)) & 0x0F0F0F0F;
        x = x + (x >> 8);
        x = x + (x >> 16);
        return x & 0x3F;
    }

    // Умножение функций
    unsigned long long mul(const BoolFunc& other){
        int i = 0;
        int j = 0;
        unsigned long long res = 0;
        while (anf >> i != 0){
            if((anf >> i) & 1){
                while (other.anf >> j != 0){
                    if((other.anf >> j) & 1){
                        res ^= (1 << (i | j));
                    }
                    j++;
                }
                j = 0;
            }
            i++;
        }
        return res;
    }


};
int main(){
    BoolFunc f("101011");
    cout << "f num: ";
    f.printAnf();
    cout << "f str: ";
    f.printAnfStr();
    BoolFunc g("10010");
    cout << "g num: ";
    g.printAnf();
    cout << "g str: ";
    g.printAnfStr();
    BoolFunc h(f.mul(g));
    cout << "h num: ";
    h.printAnf();
    cout << "h str: ";
    h.printAnfStr();
    cout << "Вес h: " <<  h.w() << endl;


    return 0;
}
