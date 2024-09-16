import sys

# Reading all the data in and then computing would be easier but generating the stations beforehand can be quicker

## TODO the code doesent work because it assumed that if the door is open on one side it is also open on the other side

doors = []
inputString =  sys.stdin.read().strip()
lines = inputString.split("\n")
amount_doors = int(lines[0])

def format(x,y,z):
    x = int(x)
    y = int(y)
    z = int(z)
    return x, y, z

def calculateSecond(x,y,z, door):
    x = int(x)
    y = int(y)
    z = int(z)

    if door =="X-":
        return x-1, y, z
    if door =="X+":
        return x+1, y, z
    
    if door =="Y-":
        return x, y-1, z
    if door =="Y+":
        return x, y+1, z
    
    if door =="Z-":
        return x, y, z-1
    if door =="Z+":
        return x, y, z+1

def addToStations(module1, module2):
    # if stations already exist it appends to the existing one
    for i  in range(len(stations)):
        if module1 in stations[i]:
            if module2 in stations[i]: #prevent dupliactes
                break
            stations[i].add(module2)
            break
        if module2 in stations[i]:
            if module1 in stations[i]: #prevent dublicates
                break
            stations[i].add(module1)
            break
    #if no maches are present a new sation is created
    stations.append({module1,module2})

def mergeStations():
    for station1 in stations:
        for station2 in stations:
            for module in station2:
                if module in station1:
                    return 0

def orderModules(module1, module2):
    print (module1[0])
    if module1[0]!=module2[0]:
        if module1[0] < module2[0]:
            return [module1, module2]
        else:
            return [module2, module1]
    if module1[1]!=module2[1]:
        if module1[1] < module2[1]:
            return [module1, module2]
        else:
            return [module2, module1]
    else:
        if module1[2] < module2[2]:
            return [module1, module2]
        else:
            return [module2, module1]

single_passages = []
compleate_passages = []

stations = []


for i in range(amount_doors):

    door = lines[i+1].strip().split()
    #            x          y        z       door x y z direction 
    doors.append([door[0], door[1], door[2], door[3]])

    #finds the cordinates of stations
    module1 = format(door[0], door[1], door[2])
    module2 = calculateSecond(door[0], door[1], door[2], door[3])

    door = orderModules(module1, module2)

    if door in single_passages:
        
        addToStations(module1, module2)
        compleate_passages.append(door)
    else:
        single_passages.append(door)


leak = lines[-1].strip().split()
leakformated = format(*leak)
print(stations)

for station in stations:
    if leakformated in station:
        for module in station:
            print(f"{module[0]} {module[1]} {module[2]}") # TODO the output isnt sorted
input()