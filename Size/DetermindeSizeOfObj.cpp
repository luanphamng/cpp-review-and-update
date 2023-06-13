#include <iostream>

using namespace std;

class TestA
{

};

class TestB: public TestA
{

};

class TestC: virtual public TestA
{

};

class TestD
{
    public:
        int i;
};

class TestE: public TestD
{
    public:
        int j;
};

class TestF: virtual public TestD
{
    public:
        int j;
};

class TestG
{
    public:
        void function()
        {

        }
};

class TestH: public TestG
{
    public:
        void function()
        {

        }
};

class TestI: virtual public TestG
{
    public:
        void function()
        {

        }
};

class TestJ
{
    public:
        virtual void function() {}
        virtual void function2() {}
        virtual void function3() {}
        virtual void function4() {}
        virtual void function5() {}
        virtual void function6() {}
        virtual void function7() {}
        virtual void function8() {}
};

class TestK: public TestJ
{
    public:
        void function() override
        {

        }
};

class TestL: virtual public TestJ
{
    public:
        void function() override
        {

        }
};

int main()
{
    cout << "int:\t\t" << sizeof(int) << "\n";
    cout << "TestA:\t\t" << sizeof(TestA) << "\t(empty class)\n";
    cout << "TestB:\t\t" << sizeof(TestB) << "\t(inheriting empty class)\n";
    cout << "TestC:\t\t" << sizeof(TestC) << "\t(virtual inheriting empty class)\n";
    cout << "TestD:\t\t" << sizeof(TestD) << "\t(int class)\n";
    cout << "TestE:\t\t" << sizeof(TestE) << "\t(inheriting int + int class)\n";
    cout << "TestF:\t\t" << sizeof(TestF) << "\t(virtual inheriting int + int class)\n";
    cout << "TestG:\t\t" << sizeof(TestG) << "\t(function class)\n";
    cout << "TestH:\t\t" << sizeof(TestH) << "\t(inheriting function class)\n";
    cout << "TestI:\t\t" << sizeof(TestI) << "\t(virtual inheriting function class)\n";
    cout << "TestJ:\t\t" << sizeof(TestJ) << "\t(virtual function class)\n";
    cout << "TestK:\t\t" << sizeof(TestK) << "\t(inheriting overriding function class)\n";
    cout << "TestL:\t\t" << sizeof(TestL) << "\t(virtual inheriting overriding function class)\n";

    cout << "\n";
    system("pause");

    return EXIT_SUCCESS;
}