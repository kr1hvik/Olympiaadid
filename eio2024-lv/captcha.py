import sys

correct_order = []
while True: 
    string = sys.stdin.readline().strip()
    try:
        brother_moves_count=int(string)
        break
    except:
        correct_order.append(string)

brother_moves=[]
for i in range(brother_moves_count):
    string = sys.stdin.readline().strip()

    if string in brother_moves:
        #if a string exists even times it will be removed as it would have been removed already 
        brother_moves.remove(string)
    else:
        brother_moves.append(string)

current_order = brother_moves[:]
current_moves=[]

# because the data ammounts are small time is not a constrain, memory can be

def click(string, list):
    if string in list:
        list.remove(string)
        return list
    else:
        list.append(string)
        return list


for i in range(len(correct_order)):
    string=correct_order[i]

    if len(current_order)==i:
        current_moves.append(correct_order[i])
        current_order = click(correct_order[i], current_order)
        continue
    if current_order[i] == correct_order[i]:
        
        continue
    else:
        while True:
            if len(current_order)==i:
                current_moves.append(correct_order[i])
                current_order = click(correct_order[i], current_order)
                break

            current_moves.append(current_order[i])
            current_order = click(current_order[i], current_order)
            if current_order[i] == correct_order[i]:
                break
print(len(current_moves))
for move in current_moves:
    print(move)