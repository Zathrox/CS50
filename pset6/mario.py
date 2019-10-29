from cs50 import get_int

while True:
    h = get_int("Height: ")
    if h > 0 and h <= 8:
        break

for i in range(h):
    # Generates the Nudge
    for j in range(h-i):
        if j >= 1:
            print(" ", end="")
    
    # Generates the left pillar
    for j in range(i):
        print("#", end="")
    print("#", end="")
    
    # Generates the Gap
    print("  ", end="") 
    
    # Generates the right pillar
    for j in range(i):
        print("#", end="")
    print("#", end="")
    print()