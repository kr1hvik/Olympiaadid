
import sys
n_s, m_s, x1_s, y1_s, x2_s, y2_s= sys.stdin.readline().strip().split()
O_m=int(m_s)
O_n= int(n_s)
O_x1=int(x1_s)
O_y1=int(y1_s)
O_x2=int(x2_s)
O_y2=int(y2_s)

#all vasak
def attempt(x1, y1, x2, y2, n, m):
    output=""
    if x1==0 and y2==0:
        if x1<m and y2<n:
            output = (str(m*n-y1*x2/2))
        if x1>m:
            output = str(m*(n-x1))
        if y2>n:
            output = str(n*(m-y2))

    #all parem
    if x1==n and y2==0:
        if n-x1<m and y2<n:
            output = (str(m*n-y1*(n-x2)/2))
        if n-x1>m:
            output = str(m*x1)
        if y2>n:
            output = str(n*(m-y2))


    #up vasak
    if x1==0 and y2==m:
        if x1<m and m-y2<n: 
            output = (str(m*n-(m-y1)*x2/2))
        if x1>m:
            output = str(m*(n-x1))
        if m-y2>n:
            output = str(n*y2)

    #up parem
    if x1==n and y2==m:
        if n-x1<m and m-y2<n:
            output = (str(m*n-(m-y1)*(n-x2)/2))
        if n-x1>m:
            output = str(m*x1)
        if m-y2>n:
            output = str(n*y2)

    #vertical
    if y1==0 and y2==m and x1 == x2:
        output = (str(max(
            abs(n*m - x1*m),
            x1*m
        )))
    if y1==0 and y2==m and x1 != x2:
        output= str(min(x1,x2)*m + m*m/2)    
    #horisontal
    
    if x1==0 and x2==n and y1==y2:
        output = (str(max(
            abs(n*m - y1*n),
            y1*n
        )))
    if x1==0 and x2==n and y1!=y2:
        output=str(min(y1, y2)*n + n*n/2)


    if output!="":
        if "." not in output:
            sys.stdout.write(output.split(".")[0])
        else:
            sys.stdout.write(output)
        #sys.stdout.write("\n\n")
        return 1
    else:
        return 0


ret1 = attempt(O_x1, O_y1, O_x2, O_y2, O_n, O_m)

if ret1==0:
    ret2 = attempt(O_x2, O_y2, O_x1, O_y1, O_n, O_m)

