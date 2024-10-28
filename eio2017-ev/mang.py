import sys

n = int(sys.stdin.readline().strip())-1#counting starts from 0 not 1(in the text)
board = [int(x) for x in sys.stdin.readline().strip().split(" ")]
def moveCalculator(current, add):
    sum=current+add
    if sum==n:
        return sum
    modul = sum%(n+1)
    return modul

def checkSquare(curent, add):
    checkable_square = moveCalculator(curent,add)
    checkable_value = board[checkable_square]
    if checkable_value != "+":
        if checkable_square not in needToCheck:
            needToCheck.append(checkable_square)



needToCheck=[0]
while True:
    if len(needToCheck)==0:
        break

    current_square=needToCheck.pop(0)
    current_value = board[current_square]
    board[current_square] = "+"

    #dice throws
    if current_value==0:
        for i in range(6):
            checkSquare(current_square, i+1)
    else:
        checkSquare(current_square, current_value)
    pass #for debugging

for result in board:
    if result=="+":
        sys.stdout.write("1 ")
    else:
        sys.stdout.write("0 ")
