import sys
boards_count = int(sys.stdin.readline().strip())
boards = []


for i in range (boards_count):
    # ! sorting broke because they were sorted as strings not int
    board = [int(axes) for axes in sys.stdin.readline().strip().split(" ")]
    boards.append(board)

#sorting bc sorting would take less time than combing thru all of the boards multiple times (probably)
boards.sort()

for i in range(boards_count):
    pass
    distance = i
    current_board = boards[i]
    while True:
        distance+=1
        if distance>boards_count-1:#count starts with 1 distance with 0
            break

        boards_for_eval = boards[distance]

        #x axes check
        if current_board[2]<=boards_for_eval[0]:
            break #if boards are already too far apart (on the x axes)

        # y axes check 
        # *! checking logic was flawed, did not check for all occasions 
        if (current_board[1] <  boards_for_eval[3] <=  current_board[3] or # 2.boards bottom is between
            current_board[1] <= boards_for_eval[1] <  current_board[3] or # 2.boards top    is between
            (current_board[1] >= boards_for_eval[1] and current_board[3] <= boards_for_eval[3])
            ):
            print("JAH")
            sys.exit()
        
        
print("EI")