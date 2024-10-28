vasakule = [
	10, 12,  5,  1, 21,  8,
	 4, 18, 11,  7, 15,  2,
	22,  0, 17, 13,  9, 20,
	16,  6, 23, 19,  3, 14]
paremale = [
	 5, 10, 12,  8,  1, 21,
	11,  4, 18,  2,  7, 15,
	17, 22,  0, 20, 13,  9,
	23, 16,  6, 14, 19,  3]

def liigu(olek, sammud):
	for samm in sammud:
		if samm == 'V':
			olek = vasakule[olek]
		if samm == 'P':
			olek = paremale[olek]
	return olek

teed = [
	"",
	"V", "P",
	"VV", "VP", "PV", "PP",
	"VVV", "VVP", "VPV", "VPP",
	"PVV", "PVP", "PPV", "PPP"]

_ = int(input())
tee = input().strip()
olek = liigu(0, tee)

for tee in teed:
	if liigu(olek, tee) in [0, 1, 2]:
		print(len(tee))
		print(tee)
		break
