import sys

n = int(sys.stdin.readline().strip())

if n%2==1:
    sys.stdout.write("-1")
    sys.exit()

sokid = {}

for i in range(n):
    sokk = sys.stdin.readline().strip()

    if sokk in sokid:
        sokid[sokk]+=1
    else: 
        sokid[sokk]=1


count = 0
for colour in sokid:
    if sokid[colour]%2==1:
        count+=1
sys.stdout.write(str(int(count/2)))