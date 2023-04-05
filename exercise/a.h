#include <iostream>
using namespace std;

class First
{
public:
    void FirstFunc() { cout << "FirstFunc" << endl; }
    virtual void MyFunc() { cout << "First's MyFunc" << endl; }
};

class Second: public First
{
public:
    void SecondFunc() { cout << "SecondFunc" << endl; }
    virtual void MyFunc() { cout << "Second's MyFunc" << endl; }
};

class Third: public Second
{
public:
    void ThirdFunc() { cout << "ThirdFunc" << endl; }
    virtual void MyFunc() { cout << "Third's MyFunc" << endl; }
};

int main(void)
{
    Third obj;
    obj.FirstFunc();
    obj.SecondFunc();
    obj.ThirdFunc();
    obj.MyFunc();

    Second & sref = obj;
    sref.FirstFunc();
    sref.SecondFunc();
    sref.MyFunc();

    First & fref = obj;
    fref.FirstFunc();
    fref.MyFunc();

    return 0;
}
/*
FirstFunc
SecondFunc
ThirdFunc
Third's MyFunc
FirstFunc
SecondFunc
Third's MyFunc
FirstFunc
Third's MyFunc
*/