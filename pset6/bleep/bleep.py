from cs50 import get_string
from sys import argv


def main():

    if len(argv) != 2:
        sys.exit("Usage: python bleep.py dictionary")
    
    # Creates a blank set   
    dict = set()

    # Opens the file in read mode
    file = open(argv[1], "r")
    
    # Iterates over the lines in the file, stripping and storing them in dict
    for line in file:
        dict.add(line.strip("\n"))
    file.close()

    # Getting a string, and splitting it into an individual list
    str = get_string("What message would you like to censor?\n").split()

    # Iterate through the lenght of the message
    for i in range(len(str)):
        # if list.lowercase matches dict, print * message
        if str[i].lower() in dict:
            # Multplies the '*'' by the lenght of the word 
            print('*' * len(str[i]), end=" ")
        else:
            print(str[i], end=" ")
        
    print()
    

if __name__ == "__main__":
    main()
