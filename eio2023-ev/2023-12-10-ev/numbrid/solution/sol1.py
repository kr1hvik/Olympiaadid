# vaatab läbi kõik arvud soovitud numbrite miinimumist maksimumini;
# kontrollib igaühe kohta, kas see on soovitute hulgas

# hoiab soovide nimekirja hulgana, kus elemendi olemasolu kontroll
# on efektiivne ja seetõttu töötab kiiesti ka suuremates testides

n = int(input())
soovid = set(map(int, input().split()))

vastus = []
for number in range(min(soovid), max(soovid)):
	if number not in soovid:
		vastus.append(number)

print(len(vastus))
print(*vastus)
