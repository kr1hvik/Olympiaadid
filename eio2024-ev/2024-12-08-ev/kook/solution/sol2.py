n = int(input())
p = list(map(int, input().split()))
m = list(map(int, input().split()))

voimalik = True
for i in range(1,n):
    if (m[i]*p[i-1] != m[i-1]*p[i]):
        voimalik = False
    
if (voimalik):
    print('JAH')
    print(*range(1,n+1))

else:
    print('EI')