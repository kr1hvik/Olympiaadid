# sorteerib soovitud numbrite jada ja leiab selles "augud"

n = int(input())
soovid = [int(s) for s in input().split()]

soovid.sort()

vastus = []
for i in range(1, n):
	for number in range(soovid[i - 1] + 1, soovid[i]):
		vastus.append(number)

print(len(vastus))
print(*vastus)
