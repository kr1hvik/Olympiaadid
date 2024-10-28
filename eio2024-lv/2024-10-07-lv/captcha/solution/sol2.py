pildid = []
for _ in range(5):
    pildid.append(input())

klikid = []
n = int(input())
for _ in range(n):
    pilt = input()
    if pilt in klikid:
        klikid.remove(pilt)
    else:
        klikid.append(pilt)

logi = []
for i in range(len(pildid)):
    while len(klikid) > i and klikid[i] != pildid[i]:
        logi.append(klikid[i])
        klikid.pop(i)
    if len(klikid) <= i:
        logi.append(pildid[i])

print(len(logi))
for pilt in logi:
    print(pilt)
