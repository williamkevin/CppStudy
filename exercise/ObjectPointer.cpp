#include <iostream>
using namespace std;

class Person
{
    public:
        void Sleep() { cout << "Sleep" << endl; }
};

class Student : public Person
{
    public:
        void Study() { cout << "Study" << endl; }
};

class PartTimeJob : public Student
{
    public:
        void Work() { cout << "Work" << endl; }
};

int main(void)
{
    Person * ptr1 = new Student();
    Person * ptr2 = new PartTimeJob();
    Student * ptr3 = new PartTimeJob();

    ptr1 -> Sleep();
    ptr2 -> Sleep();
    ptr3 -> Study();

    delete ptr1;
    delete ptr2;
    delete ptr3;

    return 0;
}