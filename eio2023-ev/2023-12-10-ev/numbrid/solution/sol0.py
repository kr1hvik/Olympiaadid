# vaatab läbi kõik arvud soovitud numbrite miinimumist maksimumini;
# kontrollib igaühe kohta, kas see on soovitute hulgas

# hoiab soovide nimekirja loendina, kus elemendi olemasolu kontroll
# vajab loendi läbivaatamist, milleks kulub kuni N sammu;
# kõigi võimalike väärtuste kontrolliks kulub seega (max-min)*N sammu,
# mis jääb suuremate andmemahtude korral liiga aeglaseks

n = int(input())
soovid = list(map(int, input().split()))

vastus = []
for number in range(min(soovid), max(soovid)):
	if number not in soovid:
		vastus.append(number)

print(len(vastus))
print(*vastus)
