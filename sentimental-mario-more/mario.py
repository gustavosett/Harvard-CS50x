
while(True):
    height = input("Height: ")
    if (height.isalpha() or height == ""):
        print("invalid!")
    else:
        height = int(height)
        if (height <= 0 or height >= 9):
            print("invalid!")
        else:
            break

spaces = height - 1

for i in range(height):
    hashNum = i + 1
    print(" " * spaces + "#" * hashNum + "  " + "#" * hashNum)
    spaces = spaces - 1