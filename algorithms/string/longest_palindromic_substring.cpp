#include <bits/stdc++.h>
using namespace std;

string makeSubstring(string str, int start, int end)
{
    string ret;
    for (int i = start; i <= end; i++)
    {
        ret.push_back(str[i]);
    }
    return ret;
}

/********************** Start of O(N^3) *****************************/
// string longestPalindrome(string s)
// {
//     int length = s.size();
//     int maxLen = 1;
//     int startOfPalind = 0;

//     for (int i = 0; i < length; i++)
//     {
//         for (int j = i; j < length; j++)
//         {
//             bool isPalindDetected = true;
//             for (int k = 0; k < (j - i + 1) / 2; k++)
//             {
//                 if (s[i + k] != s[j - k])
//                 {
//                     isPalindDetected = false;
//                 }
//             }

//             if (isPalindDetected && (maxLen < (j - i + 1)))
//             {
//                 startOfPalind = i;
//                 maxLen = j - i + 1;
//             }
//         }
//     }

//     return makeSubstring(s, startOfPalind, startOfPalind + maxLen - 1);
// }
/********************** End of O(N^3) *****************************/

/********************** Start of O(N^2) *****************************/
string longestPalindrome(string s)
{
    int length = s.size();
    int start = 0;
    int maxLen = 1;
    int low, high;
    // iteration to each character
    // from each one, move to lower and higher position to detect longest palindrome
    for (int i = 0; i < length; i++)
    {
        // even palindrome
        low = i - 1;
        high = i;

        while (low >= 0 && high < length && s[low] == s[high])
        {
            if (maxLen < (high - low + 1))
            {
                start = low;
                maxLen = (high - low + 1);
            }
            low--;
            high++;
        }

        // odd palindrome
        low = i - 1;
        high = i + 1;
        while (low >= 0 && high < length && s[low] == s[high])
        {
            if (maxLen < (high - low + 1))
            {
                start = low;
                maxLen = (high - low + 1);
            }
            low--;
            high++;
        }
    }

    return makeSubstring(s, start, start + maxLen - 1);
}
/********************** End of O(N^2) *****************************/

/* */
int main()
{
    cout << longestPalindrome("forgeeksskeegfor");
    return EXIT_SUCCESS;
}