#include <iostream>
#include <vector>
#include <set>
#include <string>

using std::vector, std::cin, std::cout, std::string, std::set, std::pair;

using State = pair<string, vector<int>>;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;

  string s;
  
  set<State> curr_states, next_states;
  for(int ti = 0; ti < t; ++ ti) {
    int n;
    cin >> n;
    cin >> s;

    int ls = s.size();
    int l = ls / n;
    
    curr_states.clear();
    curr_states.insert({"", vector<int>(n - 1)});
    for(auto ch : s) {
      next_states.clear();
      for(auto &curr : curr_states) {
	auto &[cs, v] = curr;

	if(cs.size() < l) {
	  next_states.insert({cs + ch, v});
	}

	int last = cs.size();
	for(int i = 0; i < v.size(); ++ i) {
	  int x = v[i];
	  if(x < last && ch == cs[x]) {
	    auto v2 = v;
	    ++ v2[i];
	    next_states.insert({cs, v2});
	  }
	  last = x;
	}
      }
      swap(next_states, curr_states);
    }

    cout << curr_states.size() << '\n';
    bool prev = false;
    for(auto &[cs, _] : curr_states) {
      if(prev) {
	cout << ' ';
      }
      prev = true;
      cout << cs;
    }
    cout << '\n';
  }
}
