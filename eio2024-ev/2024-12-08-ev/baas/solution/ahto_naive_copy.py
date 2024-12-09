# naiivne lahendus: võrdleb esimese rea iga sõna kõigi järgmiste ridade kõigi sõnadega
# naiivne realisatsioon: hoiab kõiki vahetulemusi tekstidena ja kopeerib neid edasi-tagasi

def prefix(a, b):
	i = 0
	while i < len(a) and i < len(b) and a[i] == b[i]:
		i += 1
	return a[0 : i]

m, n = (int(x) for x in input().split())
words = [input().split() for _ in range(n)]

best = ''
for k in range(m):
	file_pref = words[0][k]
	for i in range(1, n):
		line_pref = ''
		for j in range(m):
			word_pref = prefix(words[0][k], words[i][j])
			if len(line_pref) < len(word_pref):
				line_pref = word_pref
		if len(file_pref) > len(line_pref):
			file_pref = line_pref
	if len(best) < len(file_pref) or len(best) == len(file_pref) and best > file_pref:
		best = file_pref
print(best)
