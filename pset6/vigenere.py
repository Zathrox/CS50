import sys
from cs50 import get_string


def main():
    
    # Checks for the correct arguements
    if len(sys.argv) != 2:
        sys.exit("Usage: python vigenere.py keyword")
    
    # Stores the key
    key = sys.argv[1]
    
    for a in key:
        if a.isalpha() != True:
            sys.exit("Usage: python vigenere.py keyword")
    
    # Gets User feedback for plaintext
    ptxt = get_string("plaintext: ")
    print("ciphertext: ", end="")
    
    j = 0
    # enciphers the text by looping through each character in ptxt
    for c in ptxt:
        if c.isalpha():
            cipher_key = shift(key[j % len(key)])
            j += 1
        else:
            cipher_key = 0
        print(encipher(c, cipher_key), end="")
    print()    


def shift(c):
    # Ord converts the character to ascii, we do math and chr converts backs
    if c.isupper():
        return ord(c) - 65
    else:
        return ord(c) - 97
        
       
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