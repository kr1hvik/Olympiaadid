# -*- coding: utf8 -*-

# 2017-11-18 programmeerimisvõistlus
# Ülesanne: LAUAMÄNG
# Autor: Ahto Truu
# Testitud: Python 2.7 / CygWin; Python 3.6 / CygWin

# otsib sügavuti läbimisega veel külastamata ruute, kuhu pääseb ruudust i
# kasutab globaalseid muutujaid:
# n - ruutude arv laual
# a[] - ruutudes olevad arvud, 1..n asemel indeksid 0..n-1
# r[] - 1 neis ruutudes, mis on juba külastatud, indeksid jälle 0..n-1
def dfs(i):
	if r[i] == 0: # kui ruut pole juba külastatud
		r[i] = 1 # märgime külastatuks
		if a[i] == 0: # kui ruudus on 0
			# siis võib sellest vastavalt täringuviskele 1..6 sammu edasi saada
			for j in range(6):
				# range annab 0..5, j+1 on siis 1..6
				dfs((i + j + 1) % n)
		else:
			# muidu astume alati kindla arvu edasi/tagasi
			# i + a[i] võib olla negatiivne
			# + n tagab, et jääki leiame mittenegatiivsest arvust
			dfs((i + a[i] + n) % n)

with open('mangsis.txt', 'r') as sis:
	n = int(sis.readline().strip())
	a = [int(a) for a in sis.readline().strip().split()]

# algseisus on kõik ruudud külastamata
r = [0] * n
# alustame 1. ruudult, mille indeks programmis on 0
dfs(0)

with open('mangval.txt', 'w') as val:
	val.write(' '.join(map(str, r)))
