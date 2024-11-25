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
                tmp_ull |= (1 << i);
            }
        }
        if(tmp_ull != 0){
            bl.push_front(tmp_ull);
        }
        blSize = bl.size();
    }
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
    const BoolList& get_anf() const {
        return anf;
    }
};



int main(){
    Anf a("100000");
    a.get_anf().print_bin();
    return 0;
}