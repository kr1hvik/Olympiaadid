import sys
boards_count = int(sys.stdin.readline().strip())
boards = []


for i in range (boards_count):

    board = sys.stdin.readline().strip().split(" ")
    boards.append(board)
boards.sort() #can be sorted bc sorting would take less time than combing thru all of the boards multiple times (probably)

for i in range(boards_count):
    pass
    distance = i
    current_board = boards[i]
    while True:
        distance+=1
        if distance>boards_count-1:#count starts with 1 distance with 0
            break
        boards_for_eval = boards[distance]
        if current_board[2]<=boards_for_eval[0]:
            break #if boards are already too far apart (on the x axes)
        if current_board[1]< boards_for_eval[3] and current_board[3]<boards_for_eval[3]:
            print("JAH")
            sys.exit()
        
        
print("EI")