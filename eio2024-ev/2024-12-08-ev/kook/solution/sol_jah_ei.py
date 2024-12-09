n = int(input())
p = sorted(list(map(int, input().split())))
m = sorted(list(map(int, input().split())))

voimalik = True
for i in range(1,n):
    if (m[i]*p[i-1] != m[i-1]*p[i]):
        voimalik = False
    
if (voimalik):
    print('JAH')
else:
    print('EI')
