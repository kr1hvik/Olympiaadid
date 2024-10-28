#!/usr/bin/python2.7
# -*- coding: utf8 -*-

# 2017 eelvoor
# MURD
# Lahendus: Sandra Schumann
# Testitud: Python 2.7 (3.5 jaoks muuta täisarvulist jagamist)

# Kasutame Pythoni sisseehitatud funktsionaalsust
from fractions import Fraction
from math import log10

with open("murdsis.txt", 'r') as fin:
    # Loeme sisendi
    t = fin.read().split('\n')
    # Teisendame sisendi murruks (Pythonis on see väga lihtne) ja lahutame
    ans = Fraction(t[0]) - Fraction(t[1])
    
    fout = open("murdval.txt", 'w')
    sign = ""
    # Kontrollime, kas vastus on negatiivne
    if ans.numerator < 0:
        sign = "-" # Jätame märgi meelde (kui see eksisteerib)
        ans = -ans # Edasi tegeleme ainult positiivse murruga
    # Täisarvulise jagamisega leiame täisosa
    int_part = ans.numerator/ans.denominator
    ans -= int_part # Edasi tegeleme ainult lihtmurruga
    fout.write(sign+str(int_part)+'\n')
    if ans != 0: # Kontrollime, kas vaja üldse formaaditud kuju kirjutada
        fout.write(str(ans)+'\n') # Formaatimata kuju on lihtne
        if int_part == 0:
            int_len = 0
        else:
            int_len = int(log10(int_part))+1 # Arvutame täisosa pikkuse logaritmimise abil
            # Täisosa pikkus, kui täisosa on suurem kui 0, on log10 täisosast ümardatud allapoole pluss 1
            # Ühekohaliste arvude puhul on log10 arvust ümardatuna allapoole 0,
            # kahekohaliste puhul 1, kolmekohaliste puhul 2 jne
        denom_len = int(log10(ans.denominator))+1 # Samuti nimetaja pikkuse
        num_len = int(log10(ans.numerator))+1 # Ja lugeja pikkuse
        # Kirjutame sobiva arvu tühikuid, lugeja ja vajadusel järgmisele reale märgi
        fout.write(' '*(len(sign)+int_len+denom_len-num_len)+str(ans.numerator)+'\n'+sign)
        if int_part != 0:
            fout.write(str(int_part)) # Kirjutame vajadusel välja täisosa
        # Kirjutame murrujoone ja sobiva arvu tühikutega nimetaja
        fout.write('-'*denom_len+'\n'+' '*(len(sign)+int_len)+str(ans.denominator)+'\n')
    fout.close()
