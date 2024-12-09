# naiivne lahendus: võrdleb esimese rea iga sõna kõigi järgmiste ridade kõigi sõnadega
# natuke optimeeritud realisatsioon: edastab tekste funktsioonile viitena ja hoiab vahetulemustena tekside asemel nende pikkuseid
# mõnes testis töötab 3-4 korda kiiremini, aga punkte juurde siiski ei saa

def prefix(a, b):
	i = 0
	while i < len(a) and i < len(b) and a[i] == b[i]:
		i += 1
	return i

m, n = (int(x) for x in input().split())
words = [input().split() for _ in range(n)]

best = ''
for k in range(m):
	file_pref = len(words[0][k])
	for i in range(1, n):
		line_pref = 0
		for j in range(m):
			word_pref = prefix(words[0][k], words[i][j])
			if line_pref < word_pref:
				line_pref = word_pref
		if file_pref > line_pref:
			file_pref = line_pref
	if len(best) < file_pref or len(best) == file_pref and best > words[0][k][0 : file_pref]:
		best = words[0][k][0 : file_pref]
print(best)
