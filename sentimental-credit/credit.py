def validCard(card):
    somaPar = somaImpar = 0
    if len(card) % 2 == 0:
        teste = 0
    else:
        teste = 1

    for i in range(len(card) - 1, -1, -1):
        if (i % 2) == teste:
            temp = int(card[i])
            if temp >= 5:
                temp = (temp * 2) - 9
            else:
                temp = temp * 2
            somaPar = somaPar + temp
        else:
            temp = int(card[i])
            somaImpar = somaImpar + temp
    result = (somaPar + somaImpar) % 10
    if result == 0:
        return True
    else:
        return False


card = str(input("card number: "))

if len(card) <= 12:
    print("INVALID")
elif validCard(card):
    if card[0] == '3' and (card[1] == '4' or card[1] == '7') and len(card) == 15:
        print("AMEX")
    elif card[0] == '5' and (card[1] == '1' or card[1] == '2' or card[1] == '3' or card[1] == '4' or card[1] == '5') \
            and len(card) == 16:
        print("MASTERCARD")
    elif card[0] == '4' and (13 <= len(card) <= 16):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")