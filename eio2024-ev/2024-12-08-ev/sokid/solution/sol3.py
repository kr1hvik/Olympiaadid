n = int(input())

yksikud = set()
for i in range(n):
    varv = input().strip()
    if varv in yksikud:
        yksikud.remove(varv)
    else:
        yksikud.add(varv)

if n % 2 > 0:
    print(-1)
else: 
    print(len(yksikud) // 2)
