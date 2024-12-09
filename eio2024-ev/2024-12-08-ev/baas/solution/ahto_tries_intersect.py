# asümptootiliselt optimaalne lahendus trie põhjal
# ehitab trie iga rea kohta eraldi ja siis võtab neist ühisosa
# hoiab korraga mälus ainult senist ühisosa ja jooksva rea trie'd

def add_word(root, word):
	curr = root
	for c in word:
		if c not in curr:
			curr[c] = {}
		curr = curr[c]

def intersect(a, b):
	res = {}
	for c in a:
		if c in b:
			res[c] = intersect(a[c], b[c])
	return res

def find_best(curr, word = ''):
	global best
	if len(best) < len(word):
		best = word
	for c in sorted(curr):
		find_best(curr[c], word + c)

m, n = (int(x) for x in input().split())

for row in range(n):
	line_trie = {}
	words = input().split()
	for word in words:
		add_word(line_trie, word)
	if row == 0:
		file_trie = line_trie
	else:
		file_trie = intersect(file_trie, line_trie)

best = ''
find_best(file_trie)
print(best)
