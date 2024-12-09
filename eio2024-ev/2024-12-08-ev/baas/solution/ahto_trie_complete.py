# asümptootiliselt optimaalne lahendus trie põhjal
# kuna ehitab trie kogu sisendi kohta, siis ületab mõnes suuremas testis mälulimiiti

m, n = (int(x) for x in input().split())

root = [n, {}]

def add_word(row, word):
	curr = root
	for c in word:
		if c not in curr[1]:
			curr[1][c] = [0, {}]
		curr = curr[1][c]
		if curr[0] == row - 1:
			curr[0] = row

def print_trie(curr = root, char = '', level = 0):
	print(' ' * level, char, curr[0])
	for c in curr[1]:
		print_trie(curr[1][c], c, level + 1)

for row in range(n):
	words = input().split()
	for word in words:
		add_word(1 + row, word)
		#print_trie()

def find_best(curr = root, word = ''):
	global best
	if curr[0] < n:
		return
	if len(best) < len(word):
		best = word
	for c in sorted(curr[1]):
		find_best(curr[1][c], word + c)

best = ''
find_best()
print(best)
