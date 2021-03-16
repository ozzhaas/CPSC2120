/*Kellen Haas
  Project Her 1.0
  Prob Code: PH102
  Digitone
  codechef.com
*/

#include <iostream>
#include <stdio.h>
#include <string>


using namespace std;

int sumDigits (int sum) {
    string strSum = to_string(sum);

    int numOfDigits = strSum.length();
    int finalSum = 0;

    int j = 0;
    int temp = 0;
    while (j < numOfDigits) {
        temp = strSum[j] - '0';
        finalSum += temp;
        j++;
    }
    if (finalSum > 9) {
        finalSum = sumDigits(finalSum);
    }
    return finalSum;
}






int main (void) {
    int numOfTestCases = 0;
    string nums;
    string evenNums, oddNums, strA, strB;
    int sumOdd = 0, sumEven = 0, fullSum = 0;
    int a = 0, b = 0;

    cin >> numOfTestCases;

    while (numOfTestCases > 0) {
        cin >> nums;
        cin >> strA;
        cin >> strB;
        a = stoi(strA);
        b = stoi(strB);

        sumEven = 0;
        sumOdd = 0;

        for (unsigned int i = 0; i < nums.size(); i++) {
            if (i == 0) {
                sumOdd += (nums[i] - '0') * a;
            }
            else if (i == 1) {
                sumEven += (nums[i] - '0') * b;
            }
            else if ((i % 2) == 0) {
                //aka the index is odd
                sumOdd += (nums[i] - '0') * a;

            }
            else {
                //aka the index is even
                sumEven += (nums[i] - '0') * b;
            }
        }
        fullSum = sumOdd + sumEven;
        int total = sumDigits(fullSum);
        cout << total << endl;
        numOfTestCases--;
    }



    return 0;
}
