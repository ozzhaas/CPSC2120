/* Order by frequency
   1. read in input
   2. store all comma separated ints in a hash table
   3. sort the vector based on the frequency count of each number
      (highest frequency -> lowest frequency)
   4.
*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;



struct intFreq {
    int freq = 0;
    int value = 0;
}

int compareFreq(intFreq &a, intFreq &b) {
    return (a.freq > b.freq);
}




int main(void)
{
    vector<intFreq> myInts;
    intFreq testInts;
    while (cin >> in) {
        testInts.value = stoi(in);
        testInts.freq = 0;

        for (unsigned int i = 0; i < myInts.size(); i++) {
            if (testInts.value == myInts[i].value) {
                myInts[i].freq++;
            }
        }
        sort(myInts.begin(), myInts.end(), compareFreq);
    }

    for (unsigned int i = 0; i < myInts.size(); i++) {
        cout << myInts[i].value;
    }


  return 0;
}
