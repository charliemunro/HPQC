import sys

def main():
    output = 0

    # Checks if there are the right number of arguments
    try:
        # Converts the first two arguments to integers
        in_arg = int(sys.argv[1])
        multiple = int(sys.argv[2])
    except:
        # Raises an error
        raise Exception("Incorrect arguments.\nUsage: python repeat_adder.py <num> <multiple>")

    # Iterates over all numbers up to the input
    for i in range(in_arg):
        # Adds the index to the output
        output = output + multiple

    # Prints the output
    print("{}\n".format(output))

if __name__ == "__main__":
    main()
