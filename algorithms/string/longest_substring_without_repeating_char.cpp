// TAG: Sliding windown - Hash Table - String

#include <bits/stdc++.h>

using namespace std;

/**************************** O(N^3) *****************
bool areDistinct(string str, int start, int end)
{
    vector<bool> visited(256); // init = false
    for (int i = start; i <= end; i++)
    {
        if (visited[str[i]])
            return false;
        visited[str[i]] = true;
    }
    return true;
}

int lengthOfLongestSubstring(string str)
{
    int length = str.size();
    int result = 0;

    for (int i = 0; i < length; i++)
    {
        for (int j = i; j < length; j++)
        {
            if (areDistinct(str, i, j))
            {
                result = max(result, j - i + 1);
            }
        }
    }
    return result;
}
******************************************************/

/**************************** O(N^2) *****************/
// int lengthOfLongestSubstring(string str)
// {
//     int length = str.size();
//     int result = 0;

//     for (int i = 0; i < length; i++)
//     {
//         // Sliding window
//         vector<bool> visited(256); // All false
//         for (int j = i; j < length; j++)
//         {
//             if (visited[str[j]] == true)
//             {
//                 break;
//             }
//             else
//             {
//                 result = max(result, j - i + 1);
//                 visited[str[j]] = true;
//             }
//         }
//         visited[str[i]] = false;
//     }
//     return result;
// }
/************************** End O(N^2) ****************/

/**************************** O(NlogN) *****************/
// int lengthOfLongestSubstring(string str)
// {
//     int length = str.size();
//     int result = 0;
//     int newStart = 0;

//     for (int i = 0; i < length; i++)
//     {
//         vector<bool> visited(256); // All false
//         while (visited[str[i]] == false) {
//             visited[str[i]] = true;
//             i++;
//         }

//         visited[str[i]] = true;
//         // I now as visited character. So length = i - 1 - newstart
//         result = max(result, i - 1 - newStart);
//         newStart = i;

//     }
//     return result;
// }
/************************** End O(NLogN) ****************/

/**************************   O(N)  ****************/

// Neu gap ki tu da check truoc do thi se slide windown sang diem newStart moi
// Moi lan di qua 1 ki tu se tinh result va update max result
// Moi lan di qua 1 ki tu se update lastIndex cua ki tu do.

int lengthOfLongestSubstring(string str)
{
    int length = str.size();
    int result = 0;

    vector<int> lastIndex(256, -1);
    int newStart = 0;

    for (int j = 0; j < length; j++) {
        // Update newStart (starting index of current window)
        // as maximum of current value of i and last index + 1
        newStart = max(newStart, lastIndex[str[j]] + 1);

        // Update result if get a lagger window
        result = max(result, j - newStart + 1);


        // Find the last index of str[j]
        lastIndex[str[j]] = j;
    }
    return result;
}
/************************** End O(N) ****************/
int main()
{
    string test = "geeksforgeeks";
    int len = lengthOfLongestSubstring(test);
    cout << "The length of the longest non-repeating "
            "character substring is "
         << len;
    return EXIT_SUCCESS;
}