#include <iostream>

using namespace std;

int minDistance(int A[][2], int numRowA, int B[][2], int numRowB) {
    int result = 0;
    // Your Solution
    

    cout << result;
}

int main() {
    int A[8][2] = {{1,1}, {1,2}, {1,3}, {2,1}, {2,3}, {3,1}, {3,2}, {3,3}};
    int B[10][2] = {{6,5}, {6,6}, {6,7}, {7,5}, {7,7}, {8,6}, {8,7}, {8,8}, {8,9}, {9,9}};

    minDistance(A, 8, B, 10);
    return 0;
}