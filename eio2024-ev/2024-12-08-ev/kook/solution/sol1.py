n = int(input())
p = list(map(int, input().split()))
m = list(map(int, input().split()))

if (m[0] * p[0] == m[1] * p[1]):
    print('JAH\n2 1')
elif (m[0] * p[1] == m[1] * p[0]):
    print('JAH\n1 2')
else:
    print('EI')