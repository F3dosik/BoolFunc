#include <iostream>
#include <string>
#include <list>

using namespace std;

class BoolList {
private:
    list<unsigned long long> bl;
    size_t blSize;
    int strSize;
    string str;
public:
    // Конструктор с инициализацией по строке
    BoolList(const string& str){
        strSize = str.size();
        this->str = str;
        unsigned long long tmp_ull = 0;
        for(size_t i = 0; i < strSize; i++){
            if(i % 64 == 0 && tmp_ull != 0){
                bl.push_front(tmp_ull);
                tmp_ull = 0;
            }
            if(str[strSize - 1 - i] == '1'){
                tmp_ull |= (1ULL << i);
            }
        }
        if(tmp_ull != 0){
            bl.push_front(tmp_ull);
        }
        blSize = bl.size();
    }
    //Конструктор с инициализацией по листу
    BoolList(const list<unsigned long long>& input) : bl(input) {}

    // Перегрузка оператора [] для обращения по индексу
    bool operator[](size_t index) const {
        if(index >= strSize){
            throw out_of_range("Индекс за пределами диапазона");
        }
        size_t i = index / 64;
        short s = index % 64;
        auto it = bl.begin();
        if(i > ((blSize - 1) / 2)){
            auto it = bl.rbegin();
            advance(it, i);
        }
        else{
            advance(it, blSize - 1 - i);
        }    
        return ((1 << s) & (*it));
    }

    // Вес вектора
    unsigned long long w() const {
        unsigned long long res = 0;
        for(auto it = bl.rbegin(); it != bl.rend(); it++){
            unsigned long long x = *it;
            x = x - ((x >> 1) & 0x5555555555555555);
            x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
            x = (x + (x >> 4)) & 0x0F0F0F0F;
            x = x + (x >> 8);
            x = x + (x >> 16);
            x = x + (x >> 32);
            res +=  x & 0xFF;
        }
        return res;
    }
    void print_bin() const {
        for(auto it = bl.begin(); it != bl.end(); ++it){
            cout << *it << " ";
        }
        cout << endl;
    }

};
// Представление в виде полинома Жигалкина
class Anf {
private:
    BoolList anf; 
public:
    Anf(const string& str) : anf(str){}
    // Обращение к вектору
    const BoolList& get_anf() const {
        return anf;
    }
};

// Представление в виде вектора значений
class Tt {
private:
    BoolList tt;
public:
    Tt(const string& str) : tt(str){}
    // Обращение к вектору
    const BoolList& get_tt() const {
        return tt;
    }
};



int main(){
    BoolList a("11111111111111111111111111111111111111111111111111111111111111111");
    cout << a.w() << endl;
    return 0;
}