/*Kellen Haas
  Prob Code: PH101
  Special 7
  codechef.com
*/



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
    string N;

    cin >> numOfTestCases;

    for (int i = 0; i < numOfTestCases; i++) {
        cin >> N;

        if (N[i] == '7') {
            cout << "True\n";
        }
        else {
            cout << "False\n";
        }
    }

    return 0;
}
