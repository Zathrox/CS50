import sys
from cs50 import get_string


def main():
    
    # Checks for the correct arguements
    if len(sys.argv) != 2:
        sys.exit("Usage: python caesar.py positivevalue")
    
    # Stores the key
    key = int(sys.argv[1])
    
    # Checks if Key is value, if not end
    if key <= 0:
        sys.exit("Usage: python caesar.py positivevalue")
        
    # Gets User feedback for plaintext
    ptxt = get_string("plaintext: ")
    print("ciphertext: ", end="")
    
    # enciphers the text by looping through each character in ptxt
    for c in ptxt:
        print(encipher(c, key), end="")
    print()
    
    
def encipher(ptxt, key):
    
    # Ord converts the character to ascii, we do math and chr converts backs
    if ptxt.isupper():
        return chr(((ord(ptxt) - 65) + key) % 26 + 65)
        
    elif ptxt.islower():
        return chr(((ord(ptxt) - 97) + key) % 26 + 97)
        
    else:
        return ptxt
        
        
if __name__ == "__main__":
    main()