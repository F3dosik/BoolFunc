#include <iostream>
#include <string>
#include <list>

using namespace std;
// Представление в виде полинома Жигалкина
class Anf {
private:
    list<unsigned long long> anf;
public:
    Anf(const string& str){
        size_t strSize = str.size();
        unsigned long long tmp_anf = 0;
        for(size_t i = 0; i < strSize; i++){
            if(i % 64 == 0 && tmp_anf != 0){
                anf.push_front(tmp_anf);
                tmp_anf = 0;
            }
            if(str[strSize - 1 - i] == '1'){
                tmp_anf |= (1 << i);
            }
        }
        if(tmp_anf != 0){
            anf.push_front(tmp_anf);
        }   
    }

    void print_anf(){
        for(const auto& val : anf){
            cout << val << " ";
        }
        cout << endl;
    }

    int deg(){
        
    }

};



int main(){
    Anf f("11111111111111111111111111111111111111111111111111111111111111111");
    f.print_anf();
    return 0;
}