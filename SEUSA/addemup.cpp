#include <iostream>
#include <unordered_set>
#include <algorithm>

using namespace std;


int main(){
  int numCards, desiredSum, curr;
  cin >> numCards >> desiredSum;

  unordered_set<int> map;

  for(int i=0;i<numCards;i++){
    cin >> curr;
    string altNum = to_string(curr);
    reverse(altNum.begin(), altNum.end());
    int alt = -1;
    bool flip = true;
    for (int i = 0; i < altNum.length(); i++) {
        if (altNum[i] == '2' || altNum[i] == '5' || altNum[i] == '1' || altNum[i] == '8' || altNum[i] == '9' || altNum[i] == '6') {
            if (altNum[i] == '6') altNum[i] = '9';
            else if (altNum[i] == '9') altNum[i] = '6';
        }
        else flip = false;
        alt = stoi(altNum);
    }
    if (map.count(desiredSum-curr) > 0 || (flip && map.count(desiredSum-alt) > 0)) {
      cout << "YES" << endl;
      return 0;
      }
    map.insert(curr);
    map.insert(alt);
  }
  cout << "NO" << endl;
  return 0;
}
