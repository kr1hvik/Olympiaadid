import sys
n = int(sys.stdin.readline().strip())

map=[]
hasExited = False

def checkKattuvus(x1,x2,y1,y2):
    for board in map:
        if (x1<board[0] and board[0]<x2) or (x1<board[1] and board[1]<x2):
            #print((x1<=board[0] and board[0]<=x2))
            #print((x1<=board[1] and board[1]<=x2))
            #print("x")
            if (y1<board[2] and board[2]<y2) or (y1<board[3] and board[3]<y2):
                #print((y1<=board[2] and board[2]<=y2))
                #print((y1<=board[3] and board[3]<=y2))
                #print("y")
                #print("JAH")
                hasExited = True
                sys.exit()

for i in range(n):
    #print(i)
    plaat = sys.stdin.readline().strip().split()
    x1 = int(plaat[0])
    x2 = int(plaat[2])
    y1 = int(plaat[1])
    y2 = int(plaat[3])
    checkKattuvus(x1,x2,y1,y2)
    map.append([x1,x2,y1,y2])

if (hasExited != True):
    print("EI")