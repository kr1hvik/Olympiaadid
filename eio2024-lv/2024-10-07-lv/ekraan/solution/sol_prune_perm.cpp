#include <iostream>
#include <vector>
#include <optional>
#include <array>
#include <algorithm>
#include <numeric>

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

bool cont [7][1 << 7];

void build_perm (vector<int> &cur, array<bool, 7> &used,
                 const vector<int> &orig_masks, vector<int> &cur_masks,
                 vector<array<int, 7>> &valid) {
  if (cur.size() == 7) {
    array<int, 7> perm;
    for (int i = 0; i < 7; i++)
      perm[cur[i]] = i;
    
    valid.push_back(perm);
    return;
  }

  int k = cur.size();
  for (int i = 0; i < 7; i++) {
    if (used[i])
      continue;

    bool ok = true;
    for (int j = 0; j < (int) orig_masks.size(); j++) {
      if (orig_masks[j] & 1 << i)
        cur_masks[j] |= 1 << k;

      if (!cont[k][cur_masks[j]])
        ok = false;
    }

    if (ok) {
      cur.push_back(i);
      used[i] = 1;
      build_perm(cur, used, orig_masks, cur_masks, valid);
      used[i] = 0;
      cur.pop_back();
    }

    for (int j = 0; j < (int) orig_masks.size(); j++) {
      cur_masks[j] &= ~(1 << k);
    }
  }
}

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
    
    int nmask = 0;
    for (int i = 0; i < 7; i++)
      if (mask & 1 << i)
        nmask |= 1 << perm[i];

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

void solve (int n, ll first) {
  vector<Encoding> encs;

  {
    vector<int> orig_masks;
    for (int i = 0; i < n; i++) {
      orig_masks.push_back((first >> (7 * i)) & 0x7f);
    }

    vector<int> cur;
    array<bool, 7> used = {0, 0, 0, 0, 0, 0, 0};
    vector<int> cur_masks (n, 0);
    vector<array<int, 7>> valid;

    build_perm(cur, used, orig_masks, cur_masks, valid);

    for (const auto &perm : valid)
      for (int rev = 0; rev < 2; rev++)
        for (int flip = 0; flip < 2; flip++)
          encs.push_back(Encoding{.perm = perm, .rev = (bool) rev, .flip = (bool) flip});
  }

  vector<pair<Encoding, pair<int, int>>> alive;
  for (const auto &enc : encs) {
    auto pr = enc.decode(n, first);
    if (pr.second == 0)
      continue;

    alive.emplace_back(enc, pr);
  }

  int mod = 1;
  for (int i = 0; i < n; i++)
    mod *= 10;
  
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

      if (pr.first != (oldpr.first + 1) % mod)
        continue;

      nalive.emplace_back(enc, make_pair(pr.first, pr.second & oldpr.second));
    }
    
    alive = nalive;
  }
}

int main () {
  for (int i = 0; i < 10; i++) {
    cont[6][masks[i]] = 1;
    cont[6][~masks[i] & 0x7f] = 1;
  }

  for (int k = 6; k > 0; k--) {
    for (int i = 0; i < 1 << (k + 1); i++) {
      cont[k - 1][i & ((1 << k) - 1)] |= cont[k][i];
    }
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
