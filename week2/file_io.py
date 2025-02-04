import time

def main():
    start_time = time.time()  # Start timing

    # Writing to a file
    with open('test_file.txt', 'w') as f:
        for _ in range(10000):  # Writing multiple lines to simulate a large file
            f.write("Hello, world!\n")

    # Reading from the file
    with open('test_file.txt', 'r') as f:
        content = f.read()

    end_time = time.time()  # End timing
    print(f"File I/O took {end_time - start_time:.6f} seconds.")

if __name__ == "__main__":
    main()
