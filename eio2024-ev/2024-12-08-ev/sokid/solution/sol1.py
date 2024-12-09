n = int(input())

sokid = {} 
for i in range(n):
    varv = input().strip()
    if varv in sokid:
        sokid[varv] += 1
    else:
        sokid[varv] = 1

yksi = 0
for arv in sokid.values():
    if arv % 2 > 0:
        yksi += 1

if yksi % 2 > 0:
    print(-1)
else: 
    print(yksi // 2)
