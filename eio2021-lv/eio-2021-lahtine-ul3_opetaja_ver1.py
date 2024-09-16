kogus=int(input())
kohad={"X":0, "Y":1, "Z":2}
avatud={}
for nr in range(kogus): 
   rida=input().split()
   algus=[int(rida[0]), int(rida[1]), int(rida[2])]
   ots=algus[:]
   koht=kohad[rida[3][0]]
   if rida[3][1]=="+": ots[koht]+=1
   else: ots[koht]-=1
   algus=tuple(algus)
   ots=tuple(ots)
   if algus not in avatud: avatud[algus]=set()
   avatud[algus].add(ots)
algkoht=input().split()
algkoht=tuple(int(a) for a in algkoht)
seotud={}

for koht in avatud:
  seotud[koht]=set()
  for koht2 in avatud[koht]:

    if koht2 in avatud:
      if koht in avatud[koht2]:
        
        seotud[koht].add(koht2)
puhver=[algkoht]
valmis=[]

while puhver:
  uuritav=puhver.pop()
  for koht in seotud[uuritav]:
    if koht not in puhver and koht not in valmis:
      puhver.append(koht)
  valmis.append(uuritav)
sorteeritud= sorted(valmis , key=lambda k: [k[2], k[1], k[0]])
for i in sorteeritud:
  print(str(i[0])+" "+str(i[1])+ " "+str(i[2]))