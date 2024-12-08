import sys

def over():
    sys.stdout.write("EI")
    sys.exit()

n = int(sys.stdin.readline().strip())

p = [int(_) for _ in sys.stdin.readline().strip().split()]

Kin = sys.stdin.readline().strip()

tempString=""
k=[]
sortedK=[]
maxCount={}
for s in Kin:
    if s==" ":
        appendable=int(tempString)
        if appendable in maxCount:
            maxCount[appendable]+=1
        else:
            maxCount[appendable]=1
        k.append(appendable)
        sortedK.append(appendable)
        tempString=""
    else:
        tempString+=s
appendable=int(tempString)
if appendable in maxCount:
    maxCount[appendable]+=1
else:
    maxCount[appendable]=1
k.append(appendable)
sortedK.append(appendable)
tempString=""

sortedK.sort(key=int)

gramsTable = {}
for i in range(n):
    table= p[0]
    cake = sortedK[i]
    gramsPerPerson = cake / table
    gramsTable[gramsPerPerson]={
        cake:1
        }
    




try:
    keys=list(gramsTable.keys())
    for i in range(1, n):

        if len(keys)<2:
            break

        table= p[i]

        #create iterable and removable objects
        unCheckedKeys=keys[:]

        iK=0

        gramsTableSize=len(keys)
        
        for iGrams in range(gramsTableSize):
            availableWeight = keys[iGrams]

            while True:
                weight = sortedK[iK]
                calcualedWeight = weight/table        
                if calcualedWeight > availableWeight:
                    break
                if calcualedWeight == availableWeight:

                    if weight in gramsTable[availableWeight]:
                        if gramsTable[availableWeight][weight]<maxCount[weight]:
                            unCheckedKeys.remove(availableWeight)
                            gramsTable[availableWeight][weight]+=1
                            break
                    else:
                        unCheckedKeys.remove(availableWeight)
                        gramsTable[availableWeight][weight]=1
                        break
                iK+=1
                if iK>n-1:
                    break

        #remove impossibilities
        for uncheCkedKey in unCheckedKeys:
            keys.remove(uncheCkedKey)
except:
    pass


if len(keys)==0:
    over()
weight = keys[0]

usedCakes=[]
string = ""


for cakeI in range(n):
    for tableI in range(n):
        ist=True
        if k[cakeI]/p[tableI]==weight and tableI not in usedCakes:
            string+=f"{tableI+1} "
            usedCakes.append(tableI)
            ist=False
            break
    if ist:
        over()
sys.stdout.write("JAH\n" + string)