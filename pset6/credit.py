from cs50 import get_int

        
def checkLuhn(cc_number):
    # Converts to a list of integers 
    def digits_of(n):
        return [int(d) for d in str(n)]
    
    # Storing the list into a variable called digits   
    digits = digits_of(cc_number)
    # Iterating through the list, starting for the end and skipping every 2
    odd_digits = digits[-1::-2]
    # Iterating through the list, starting 1 from the end and skipping every 2
    even_digits = digits[-2::-2]
    # Adding the sum of all the list odd numbers
    checksum = 0
    checksum += sum(odd_digits)
    # Iterating through even numbers, then adds the sum of the multiplied
    for d in even_digits:
        checksum += sum(digits_of(d*2))
    # Modulos the checksum to see if its divisible by 10
    return checksum % 10
    
    
def is_valid(cc_number):
    return checkLuhn(cc_number) == 0
    
    
def main():
    while True:
        cc_number = get_int("Insert Credit Card Number: ")
        digits = len(str(cc_number))

        if cc_number >= 0:
            break
    
    cardBegin = int(str(cc_number)[:2])
    if digits == 15:
        if cardBegin == 34 or cardBegin == 37:
            # checkLuhm Algorithm
            if bool(is_valid(cc_number)):
                print("AMEX")
            else:
                print("INVALID")
        
    elif digits == 13 or digits == 16 and cardBegin // 10 == 4:
        if bool(is_valid(cc_number)):
            print("VISA")
        else:
            print("INVALID")
        
    elif digits == 16:
        if cardBegin == 51 or cardBegin == 52 or cardBegin == 53 or cardBegin == 54 or cardBegin == 55:
            
            if bool(is_valid(cc_number)):
                print("MASTERCARD")
            else:
                print("INVALID")
    
    else:
        print("INVALID")
        

if __name__ == "__main__":
    main()