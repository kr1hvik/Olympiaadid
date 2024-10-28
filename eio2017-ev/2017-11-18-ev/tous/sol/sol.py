#!/usr/bin/python2.7
# -*- coding: utf8 -*-

# 2017 eelvoor
# TOUS
# Lahendus: Sandra Schumann
# Testitud: Python 2.7, 3.5

# Hakkame jarjest punkte vaatama
# Jatame meelde seni nahtud maksimaalse tousu
# ja ka hetkel vaadeldava punkti tousu
maxtous = 0 # Maksimaalne tous
curtous = 0 # Hetkel kaimas olev tous

# Avame faili ja loeme sisendi
with open("toussis.txt", 'r') as fin:
    # Loeme sisendi ja splitime reavahetuste kohalt (fin.read().split('\n'))
    # Eemaldame tyhjad read (if line)
    # Eemaldame esimese arvu (N) ([1:])
    # Viime iga arvu taisarvu kujule
    t = [ int(line) for line in fin.read().split('\n')[1:] if line ]
    
    # Peame meeles eelmisena nahtud punkti
    # Esimese punkti jaoks valime eelmisena nahtud punktiks punkti enda,
    # sest see annab tousu 0
    prevpoint = t[0]
    for point in t:
        if point > prevpoint: # Tegemist on tousuga
            curtous += point - prevpoint # Suurendame hetkel vaadeldavat tousu
        else: # Tous sai otsa (voi ei alanudki)
            # Kui praegune tous on maksimaalsest nahtust suurem, siis uuendame maksimaalset
            if curtous > maxtous:
                maxtous = curtous
            # Praegune tous on nyyd 0
            curtous = 0
        # Uuendame eelmist punkti jargmise jaoks
        prevpoint = point

# Kirjutame vastuse
# Maksimaalne tous on kas maxtous voi curtous, kui sisend loppes maksimaalse tousuga
# Valime neist kahest maksimaalse
with open("tousval.txt", 'w') as fout:
    fout.write(str(max(maxtous, curtous)))
