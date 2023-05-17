#include <iostream>

using namespace std;

template <typename T>
class EVT {
    public:
        EVT(std::string&& name, T&& value) : name(name), value(value) {}
        ~EVT() {}
        inline EVT& operator= (const T& value);
        inline operator T()const;
    private:
        T value;
        const std::string name;
};


template<>
inline EVT<bool>::operator bool() const
{
    return static_cast<bool>(value);
}

template<>
inline EVT<bool>& EVT<bool>::operator= (const bool& value)
{
    this->value = value;
    return *this;
}

class EVT_Charge {
    EVT_Charge() : isTest("abv", true) {

    }
}

int main() {
    EVT<bool> isTest("abv", true);

    isTest = true;
    cout << "Test exit success: " << isTest << endl;
    isTest = false;
    cout << "Test exit success 2: " << isTest << endl;
    return EXIT_SUCCESS;
}