#include <iostream>
#include <vector>
#include <optional>
#include <array>
#include <algorithm>
#include <numeric>
#include <tuple>

using namespace std;

typedef long long ll;

//  0
// 1 2
//  3
// 4 5
//  6

const int masks [] =
  {
   1 << 0 | 1 << 1 | 1 << 2 | 1 << 4 | 1 << 5 | 1 << 6,
   1 << 2 | 1 << 5,
   1 << 0 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 6,
   1 << 0 | 1 << 2 | 1 << 3 | 1 << 5 | 1 << 6,
   1 << 1 | 1 << 2 | 1 << 3 | 1 << 5,
   1 << 0 | 1 << 1 | 1 << 3 | 1 << 5 | 1 << 6,
   1 << 0 | 1 << 1 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6,
   1 << 0 | 1 << 2 | 1 << 5,
   (1 << 7) - 1,
   (1 << 7) - 1 - (1 << 4)
  };

const int fact [8] = {1, 1, 2, 6, 24, 120, 720, 5040};

bool valid [1 << 7];
array<int, 7> unrank [5040];
vector<int> good_perms [1 << 7];

int applyp (const array<int, 7> &perm, int mask) {
  int nmask = 0;
  for (int i = 0; i < 7; i++)
    if (mask & 1 << i)
      nmask |= 1 << perm[i];

  return nmask;
}

void calc_unrank () {
  array<int, 7> perm;
  iota(perm.begin(), perm.end(), 0);

  int idx = 0;
  do {
    unrank[idx] = perm;
    idx++;
  } while (next_permutation(perm.begin(), perm.end()));
}

void calc_good_perms (int x) {
  array<int, 7> perm;
  iota(perm.begin(), perm.end(), 0);

  int idx = 0;
  do {
    int y = applyp(perm, x);
    if (valid[y])
      good_perms[x].push_back(idx);
    idx++;
  } while (next_permutation(perm.begin(), perm.end()));
}

template<size_t N>
class ResetArray {
  array<bool, N> _arr;
  array<int, N> _age;
  int _cur_age = 1;
  bool _cur_def = 0;

public:
  void set_all (int def) {
    _cur_age++;
    _cur_def = def;
  }

  bool &at (int pos) {
    if (_age[pos] != _cur_age) {
      _age[pos] = _cur_age;
      _arr[pos] = _cur_def;
    }

    return _arr[pos];
  }
};

const int LEFT = 1 << 0;
const int RIGHT = 1 << 1; 
const int ZEROS = 1 << 2;

struct Encoding {
  array<int, 7> perm;
  bool rev;
  bool flip;

  int decode_bit (int mask) const {
    if (flip)
      mask ^= 0x7f;
    
    int nmask = applyp(perm, mask);

    for (int i = 0; i < 10; i++)
      if (nmask == masks[i])
        return i;

    if (nmask == 0)
      return -1;

    return -2; // fail
  }
  
  pair<ll, int> decode (int n, ll bits) const {
    vector<int> chars;
    for (int i = 0; i < n; i++) {
      int ch = decode_bit((bits >> (7 * i)) & 0x7f);
      if (ch == -2) {
        return make_pair(0LL, 0);
      }

      chars.push_back(ch);
    }

    if (rev)
      reverse(chars.begin(), chars.end());

    // 0th is the most significant digit
    ll val = 0;
    for (int i = 0; i < n; i++) {
      if (chars[i] == -1)
        continue;

      val *= 10;
      val += chars[i];
    }

    // check alignment
    int align = 0; // bitmask
    int epref = 0, esuff = 0, etot = 0;
    for (int i = 0; i < n; i++) {
      if (chars[i] == -1)
        epref++;
      else
        break;
    }

    for (int i = n - 1; i >= 0; i--) {
      if (chars[i] == -1)
        esuff++;
      else
        break;
    }

    for (int i = 0; i < n; i++)
      if (chars[i] == -1)
        etot++;

    // LEFT: number, then -1's
    if (esuff == etot && etot != n) {
      if (chars[0] != 0)
        align |= LEFT;
      if (chars[0] == 0 && (n == 1 || chars[1] == -1))
        align |= LEFT;
    }

    // RIGHT: -1's, then number
    if (epref == etot && etot != n) {
      if (chars[epref] != 0)
        align |= RIGHT;
      if (chars[epref] == 0 && n == epref + 1)
        align |= RIGHT;
    }

    if (etot == 0)
      align |= ZEROS;

    return make_pair(val, align);
  }
};

ll get_next () {
  cout << "NEXT" << endl;

  ll ret;
  cin >> ret;
  return ret;
}

ResetArray<5040> valid_for_digit [8];

void solve (int n, ll first) {
  vector<Encoding> encs;

  vector<int> enc_digits (n);
  pair<int, int> min_good = make_pair(100'000, -1);
  for (int i = 0; i < n; i++) {
    enc_digits[i] = (first >> (7 * i)) & 0x7f;

    if (good_perms[enc_digits[i]].size() == 5040) {
      valid_for_digit[i].set_all(1);
    } else {
      valid_for_digit[i].set_all(0);
      for (int p : good_perms[enc_digits[i]])
        valid_for_digit[i].at(p) = 1;
    }

    min_good = min(min_good, make_pair((int) good_perms[enc_digits[i]].size(), i));
  }
  
  for (int p : good_perms[enc_digits[min_good.second]]) {
    bool ok = true;
    for (int i = 0; i < n; i++) {
      if (!valid_for_digit[i].at(p)) {
        ok = false;
        break;
      }
    }

    if (!ok)
      continue;

    for (int rev = 0; rev < 2; rev++)
      for (int flip = 0; flip < 2; flip++)
        encs.push_back(Encoding{.perm = unrank[p], .rev = (bool) rev, .flip = (bool) flip});
  }
  
  vector<pair<Encoding, pair<int, int>>> alive;
  for (const auto &enc : encs) {
    auto pr = enc.decode(n, first);
    if (pr.second == 0)
      continue;

    alive.emplace_back(enc, pr);
  }

  while (true) {
    if (alive.empty()) {
      cout << 999 << endl;
      return;
    }

    int val = alive[0].second.first;
    bool all_same = true;
    for (const auto &trip : alive) {
      if (trip.second.first != val) {
        all_same = false;
        break;
      }
    }

    if (all_same) {
      cout << val << endl;
      return;
    }
    
    ll cur = get_next();
    
    vector<pair<Encoding, pair<int, int>>> nalive;
    for (const auto &trip : alive) {
      const auto &enc = trip.first;
      pair<int, int> oldpr = trip.second;
 
      auto pr = enc.decode(n, cur);
      if (!(pr.second & oldpr.second))
        continue;

      if (pr.first != oldpr.first + 1)
        continue;

      nalive.emplace_back(enc, make_pair(pr.first, pr.second & oldpr.second));
    }
    
    alive = nalive;
  }
}

int main () {
  for (int i = 0; i < 10; i++) {
    valid[masks[i]] = 1;
    valid[~masks[i] & 0x7f] = 1;
  }

  calc_unrank();
  for (int i = 0; i < 1 << 7; i++) {
    calc_good_perms(i);
  }
  
  int n;
  cin >> n;

  while (true) {
    ll x;
    cin >> x;

    if (x == -1)
      break;

    solve(n, x);
  }
}
