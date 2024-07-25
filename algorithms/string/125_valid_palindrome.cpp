#include <bits/stdc++.h>

using namespace std;


    bool isValidCharacter(char input) {
        return ((input >= 'A') && (input <= 'Z') || (input >= 'a') && (input <= 'z')) || ((input >= '0') && (input <= '9'));
    }

    bool isPalindrome(string s) {
        int low = 0;
        int high = s.length() - 1;
        bool isPalind = true;

        while (low < high) {

            while (!isValidCharacter(s[low])) {
                if (low >= s.length() - 1) break;
                low++;
            }

            while (!isValidCharacter(s[high])){
                if (high <= 0) break;
                high--;
            }

            if ((low < high) && tolower(s[low]) != tolower(s[high])) {
                isPalind = false;
                break;
            }

            low++; high--;
        }
        return isPalind;
    }


int main() {
    cout << (isPalindrome("0P") ? "true" : "false");
    return EXIT_SUCCESS;
}