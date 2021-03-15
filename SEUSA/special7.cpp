/*Kellen Haas
  Project Her 1.0
  Prob Code: PH101
  Special 7
  codechef.com
*/

#include <iostream>
#include <stdio.h>
#include <string>


using namespace std;



/* Find a way to check if a given location has a Horcrux or
   or not by examining its coordinates. If a coordinate has
   has the number 7 in it, it contains a Horcrux.

   Given:
   Several locations in the form of coordinates.

   Solve:
   Find out whether the location has a Horcrux or not.
*/


//Input:
    //Line 1 - # of test cases
    //Line 2 - single int N

//Output:
    //Print a single line answer, "True" if the location
    //has a Horcrux or "False" if it doesn't.


int main (void) {
    int numOfTestCases = 0;
    bool result = false;

    cin >> numOfTestCases;

    while (numOfTestCases--) {
        string N;
        cin >> N;

        for (unsigned int i = 0; i < N.size(); i++) {
            if (N[i] == '7') {
                result = true;
                break;
            }
            else {
                result = false;
            }
        }
        if (result) {cout << "True\n";}
        else {cout << "False\n";}
    }

    return 0;
}
