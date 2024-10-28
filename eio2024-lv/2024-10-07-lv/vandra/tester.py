import subprocess
import os

def validate_solution():
    score={
        "correct":0,
        "incorrect":0,
        "timeout":0
    }
    input_dir = "input"
    output_dir = "output"
    solution_file = "vandra2.py"
    time_limit = 3  # Time limit in seconds
    
    # Ensure the input and output directories exist
    if not os.path.exists(input_dir) or not os.path.exists(output_dir):
        print("Input or output directory is missing.")
        return

    # Check each input file and validate it against the expected output
    for input_filename in sorted(os.listdir(input_dir)):
        if input_filename.startswith("input") and input_filename.endswith(".txt"):
            test_case_number = input_filename.replace("input", "").replace(".txt", "")
            input_path = os.path.join(input_dir, input_filename)
            expected_output_path = os.path.join(output_dir, f"output{test_case_number}.txt")
            
            # Read expected output
            if not os.path.exists(expected_output_path):
                print(f"Expected output file {expected_output_path} is missing.")
                continue
            
            with open(expected_output_path, "r") as f:
                expected_output = f.read().strip()
            
            # Run vandra2.py with the input file content and a timeout
            with open(input_path, "r") as f:
                input_data = f.read()
            
            try:
                result = subprocess.run(
                    ["python3", solution_file],
                    input=input_data,
                    text=True,
                    capture_output=True,
                    timeout=time_limit  # Set timeout to 3 seconds
                )
                
                # Get actual output from the solution
                actual_output = result.stdout.strip()
                
                # Check if the actual output matches the expected output
                if actual_output == expected_output:
                    print(f"Test case {test_case_number}: PASS")
                    score["correct"]+=1
                else:
                    print(f"Test case {test_case_number}: FAIL")
                    print(f"Expected Output:\n{expected_output}")
                    print(f"Actual Output:\n{actual_output}")
                    score["incorrect"]+=1

            except subprocess.TimeoutExpired:
                print(f"Test case {test_case_number}: TIMEOUT (exceeded {time_limit} seconds)")
                score["timeout"]+=1
    print(score)

if __name__ == "__main__":
    validate_solution()
