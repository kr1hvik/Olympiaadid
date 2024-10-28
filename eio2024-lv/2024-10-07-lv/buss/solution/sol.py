# loeme sisendist praeguse kellaaja ning teisendame selle minutiteks
H, M = [int(x) for x in input().split()]
C = H * 60 + M

peatus = -1 # muutuja hetkel suurima ajavaruga peatuse meeles pidamiseks
ajavaru = -10001 # muutuja maksimaalse ajavaru jaoks

N = int(input())
for i in range(1, N + 1):
	H, M, J = [int(x) for x in input().split()]
	B = 60 * H + M # teisendame bussi saabumisaja minutiteks
	varu = (B - C) - J # arvutame, mitu minutit varem jõuab Juku
	if varu > ajavaru: # kui leidsime parema ajavaruga peatuse, siis uuendame praeguseid parimad
		ajavaru = varu
		peatus = i

# väljund
if ajavaru >= 0:
	print("JAH")
else:
	print("EI")
print(peatus)
