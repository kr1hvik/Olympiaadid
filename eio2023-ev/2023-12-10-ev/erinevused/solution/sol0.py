# naiivne O(N^2) keerukusega lahendus; jääb suuremates testides ajahätta

# erinevuse arvutamine täpselt ülesande püstituse järgi 
# alternatiivina võiks max(a[i],a[j])-min(a[i],a[j])
# asemel kirjutada ka abs(a[i]-a[j])

n = int(input())
a = input().split()
for i in range(n):
	a[i] = int(a[i])

s = 0
for i in range(n):
	for j in range(i):
		s += max(a[i], a[j]) - min(a[i], a[j])

print(s)
