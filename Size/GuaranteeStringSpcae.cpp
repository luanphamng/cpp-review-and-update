#include <iostream>
#include <fstream>
#include <string>

void f(std::istream &in)
{
    char buffer[32];
    try
    {
        in.read(buffer, sizeof(buffer));
    }
    catch (std::ios_base::failure &e)
    {
        // Handle error
    }

    std::string str(buffer);
    std::cout << str << std::endl;
}

void f2(std::istream &in)
{
    char buffer[32];
    try
    {
        in.read(buffer, sizeof(buffer));
    }
    catch (std::ios_base::failure &e)
    {
        // Handle error
    }
    std::string str(buffer, in.gcount());
    std::cout << str << std::endl;
}

int main()
{
    std::filebuf fb;
    char buffer[32];
    std::cout << "Size of buffer is: " << sizeof(buffer) << std::endl;
    if (fb.open("test.txt", std::ios::in))
    {
        std::istream is(&fb);
        while (is)
        {
            f(is);
            // f2(is);
        }
        fb.close();
    }
    return EXIT_SUCCESS;
}