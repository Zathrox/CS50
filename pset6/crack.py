import crypt
import sys
import itertools


def main():
    
    # Checks for the correct arguements
    if len(sys.argv) != 2:
        sys.exit("Usage: python crack.py hash")
    
    user_input = sys.argv[1]
    
    # A List of the alphabet
    alpha = ['', 'e', 'E', 'a', 'A', 'r', 'R', 'i', 'I', 'o', 'O', 't', 'T', 'n', 'N', 's', 'S', 'l', 'L', 'c', 'C', 'u', 'U', 'd', 'D', 'p', 
             'P', 'm', 'M', 'h', 'H', 'g', 'G', 'b', 'B', 'f', 'F', 'y', 'Y', 'w', 'W', 'k', 'K', 'v', 'V', 'x', 'X', 'z', 'Z', 'j', 'J', 'q', 'Q']
    
    salt = str(user_input)[:2]
    
    guess = []
    counter = 0
    for fifth in alpha:
        for fourth in alpha:
            for third in alpha:
                for second in alpha:
                    for first in alpha:
                        
                        # Adding all 5 Iterated loops into a list
                        guess = [first, second, third, fourth, fifth]
                        if crack(user_input, guess, salt):
                            print("Password is: ", end="")
                            print("".join(guess))
                            sys.exit()
                            
    print("Cannot Hash")                        
    sys.exit()
            
            
def crack(user_input, guess, salt):
    # Joining the list together into a string to be cracked
    crpt_guess = "".join(guess)
    encrypted_guess = crypt.crypt(crpt_guess, salt)
    if encrypted_guess == user_input:
        return True
    else:
        return False
        
    
if __name__ == "__main__":
    main()

# Cracked passwords:

# brian:51.xJagtPnb6s => TF
# bjbrown:50GApilQSG3E2 => UPenn
# emc:502sDZxA/ybHs
# greg:50C6B0oz0HWzo => FTW
# jana:50WUNAFdX/yjA => Yale
# lloyd:50n0AAUD.pL8g => lloyd
# malan:50CcfIk1QrPr6 => maybe
# natmelo:50JIIyhDORqMU => nope
# rob:51v3Nh6ZWGHOQ => ROFL
# veronica:61v1CDwwP95bY => hola
# walker:508ny6Rw0aRio => sean
# zamyla:50cI2vYkF0YU2 => LOL