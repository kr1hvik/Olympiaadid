import sys

d = int(sys.stdin.readline().strip())
n = int(sys.stdin.readline().strip())
money = int(sys.stdin.readline().strip())*100

if 5*n >= money:
    sys.stdout.write(str(money/n))
    #   print()
    #print(222)
else:
    
    if 5*n + 4*d <= money:
        sys.stdout.write(str(9))
        #print()
        #print(3333)
    else:
        forDay = money-n*5
        sys.stdout.write(str(5+forDay/d))
        #print()
        #print(4444)