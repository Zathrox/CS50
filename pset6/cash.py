from cs50 import get_float

quarter = 25
dime = 10
nickel = 5
penny = 1
coins = 0

while True:
    f = get_float("Changed owed: ")
    if f > 0:
        break
    
# Converts Dollars into Cents
cents = round(f * 100)

# Counts the cents via division + works out any remainder to pass on
coins += cents // quarter
cents = (cents % quarter)
    
# Counts the dimes via division + works out any remainder to pass on
coins += cents // dime
cents = (cents % dime)

# Counts the nickels via division + works out any remainder to pass on
coins += cents // nickel
cents = (cents % nickel)

# Counts the pennys via division + works out any remainder to pass on
coins += cents // penny
cents = (cents % penny)
    
print(coins)
