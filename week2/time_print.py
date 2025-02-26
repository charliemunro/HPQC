import time

def main():
    start_time = time.time()  # Record start time

    with open("output_python.txt", "w") as file:
        for i in range(1000000):
            file.write(f"Line {i}\n")

    end_time = time.time()  # Record end time
    print(f"Python File Write Time: {end_time - start_time:.6f} seconds")

if __name__ == "__main__":
    main()
