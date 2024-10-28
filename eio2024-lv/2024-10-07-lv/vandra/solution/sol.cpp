#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct laud {
    ll x1, x2, y1, y2;
};

// võrdleb laudu vasaku serva järgi
bool vasaku_jargi(laud e, laud v){
    return e.x1 < v.x1;
}

// võrdleb laudu parema serva järgi
bool parema_jargi(laud e, laud v){
    return e.x2 < v.x2;
}

vector<laud> lauadv; // lauad sorteeritud vasaku serva järgi
vector<laud> lauadp; // lauad sorteeritud parema serva järgi

vector<ll> kordumatud; // unikaalsed y-koordinaadi väärtused

vector<ll> t, lz; // lõikude puu ja laisa levitamise puhver

// uuendame lõikude puu tipu k, mille all on lehed i..j
void upd(ll k, ll i, ll j) {
    t[k] += lz[k]; // lisame väärtuse laisa levitamise puhvrist tipule
    if (i < j) {
        // kui k pole leht, siis levitame puhvri sisu alluvatele
        lz[2 * k] += lz[k];
        lz[2 * k + 1] += lz[k];
    }
    lz[k] = 0; // tühjendame kasutatud puhvri
}

// lisame v lõikude puu lehtedele, mis vastavad väärtustele a..b
// praegu oleme järjega tipus k, mille all on lehed i..j
void add(ll k, ll i, ll j, ll a, ll b, ll v) {
    upd(k, i, j); // rakendame muutused laisa levitamise puhvrist
    ll alampiir = i < kordumatud.size() ? kordumatud[i - 1] : 1e10;
    ll ulempiir = j < kordumatud.size() ? kordumatud[j] : 1e10;
    if (alampiir >= b || ulempiir <= a) {
        // kui a..b on tervenisti väljaspool alampuud
        // siis pole siin midagi teha
        return;
    }
    if (alampiir >= a && ulempiir <= b) {
        // kui a..b katab terve alampuu
        // siis paneme muutuse puhvrisse ootele
        lz[k] += v;
        upd(k, i, j);
        return;
    }
    // vastasel juhul töötleme kummagi alampuu eraldi
    add(2 * k, i, (i + j) / 2, a, b, v);
    add(2 * k + 1, (i + j) / 2 + 1, j, a, b, v);
    t[k] = max(t[2 * k], t[2 * k + 1]);
}

int main(){
    ll n;
    cin>>n;
    lauadv.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> lauadv[i].x1 >> lauadv[i].y1 >> lauadv[i].x2 >> lauadv[i].y2;
        kordumatud.push_back(lauadv[i].y1);
        kordumatud.push_back(lauadv[i].y2);
    }

    lauadp = lauadv;
    sort(lauadv.begin(), lauadv.end(), vasaku_jargi);
    sort(lauadp.begin(), lauadp.end(), parema_jargi);

    sort(kordumatud.begin(), kordumatud.end());
    auto end = unique(kordumatud.begin(), kordumatud.end());
    kordumatud.erase(end, kordumatud.end());

    ll c = 1;
    while (c < kordumatud.size()) c *= 2;
    t.resize(2 * c + 1);
    lz.resize(2 * c + 1);

    bool kattuvad = false;
    // käime skaneeriva joonega läbi kõigi laudade vasakud servad
    for (int i = 0, p = 0; i < n; i++){
        // eemaldame need lauad, mis lõppevad enne
        while (p < i && lauadp[p].x2 <= lauadv[i].x1) {
            add(1, 1, c, lauadp[p].y1, lauadp[p].y2, -1);
            p++;
        }
        // lisame laua, mis algab joone peal
        add(1, 1, c, lauadv[i].y1, lauadv[i].y2, 1);
        if (t[1] > 1){
            kattuvad = true;
            break;
        }
    }

    if (kattuvad) {
        cout << "JAH\n";
    } else {
        cout << "EI\n";
    }
}
