#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
  int t;
  cin >> t;

  string s;
  string a, b;
  vector<int> choice;
  set<string> good;
  for(int ti = 0; ti < t; ++ ti) {
    int n;
    cin >> n;
    cin >> s;
    
    int l = s.length() / n;
    choice.resize(l);
    for(int i = 0; i < l; ++ i) {
      choice[i] = i;
    }

    good.clear();
    
    while(true) {
      a.clear();
      b.clear();

      // Construct
      int ai = 0;
      for(int i = 0; i < s.length(); ++ i) {
	char ch = s[i];
	if(ai < l && choice[ai] == i) {
	  a += ch;
	  ++ ai;
	} else {
	  b += ch;
	}
      }
      
      // Check
      if(a == b) {
        good.insert(a);
      }
      
      // Next choice
      int ci = l - 1;
      for(; ci >= 0; -- ci) {
	++ choice[ci];
	if(choice[ci] <= ci + l) {
	  break;
	}
      }
      if(ci < 0) {
	break;
      }
      ++ ci;
      for(; ci < l; ++ ci) {
	choice[ci] = choice[ci - 1] + 1;
      }
    }

    cout << good.size() << "\n";
    for(auto &s : good) {
      cout << s << " ";
    }
    cout << "\n";
  }
}
