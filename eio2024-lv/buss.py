import sys

current_time_input = sys.stdin.readline().strip().split()
start_time = int(current_time_input[0])*60 + int(current_time_input[1]) #converts to minutes so it is easier to calculate

stops = int(sys.stdin.readline().strip())
best_time=[999999999999999999999999999999999, 0, False]

for i in range (stops):
    time_to_next_stop_input = sys.stdin.readline().strip().split()
    stop_time = int(time_to_next_stop_input[0])*60 + int(time_to_next_stop_input[1])
    current_time = int(time_to_next_stop_input[2]) + start_time
    
    if best_time[0] > current_time-stop_time:
        best_time[0] = current_time-stop_time
        best_time[1] = i+1
        if current_time<= stop_time:
            best_time[2] = True
    """print(time_to_next_stop_input)
    print(stop_time)
    print(current_time)
    print(best_time)"""
        
if best_time[2]:
    print("JAH")
    print(best_time[1])
else:
    print("EI")
    print(abs(best_time[1]))