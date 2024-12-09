n = int(input())
p = list(map(int, input().split()))
m = list(map(int, input().split()))

p_sorted = sorted(p)
m_sorted = sorted(m)

voimalik = True

for i in range(1,n):
    if (m_sorted[i] * p_sorted[i-1] != m_sorted[i-1] * p_sorted[i]):
        voimalik = False
        break

if (voimalik):
    print('JAH')

    a = [-1]*n
    p_voetud = [False]*n
    m_voetud = [False]*n

    for i in range(n):
        p_vota = -1
        m_vota = -1

        for j in range(n):
            if (p[j] == p_sorted[i]):
                p_vota = j
                break
        
        for j in range(n):
            if (m[j] == m_sorted[i]):
                m_vota = j
                break
        
        a[m_vota] = p_vota+1

        p[p_vota] = -1
        m[m_vota] = -1
    
    print(*a)
else:
    print('EI')