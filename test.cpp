#include <iostream>

class A
{
    public:

    int x;
    A (int k)
    {
        x = k;
    }
    const A operator & (const A& a) const; 
};
    const A A::operator & (const A& a) const
    {
        A a_(x);
        a_.x = a_.x & a.x;
        return a_;
    }

int main()
{
    A a(10);
    A b(15);
    a & b;
    std::cout << (a & b).x << std::endl;
    return 0;
}
