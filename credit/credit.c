#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    bool validCard(char *);
    void removeChar(char *, char);
    int count(char string[]), num;
    char card[19], pS[2];
    printf("card number: ");
    scanf("%s", &card[0]);
    removeChar(card, '-');
    num = count(card);
    pS[0] = card[0];
    pS[1] = card[1];
    if (num <= 12)
    {
        printf("INVALID");
    }
    else
    {
        // here i'm checking the length and the bank
        if (num >= 17)
        {
            printf("INVALID");
        }
        else
        {
            if (validCard(card))
            {
                // AMERICAN EXPRESS VALIDATOR
                if (pS[0] == '3')
                {
                    if (pS[1] == '4' || pS[1] == '7')
                    {
                        if (count(card) == 15)
                        {
                            printf("AMEX");
                        }
                        else
                        {
                            printf("INVALID");
                        }
                    }
                    else
                    {
                        printf("INVALID");
                    }
                }
                else
                {
                    // MASTERCARD VALIDATOR
                    if (pS[0] == '5')
                    {
                        if (pS[1] == '1' || pS[1] == '2' || pS[1] == '3' || pS[1] == '4' || pS[1] == '5')
                        {
                            if (count(card) == 16)
                            {
                                printf("MASTERCARD");
                            }
                            else
                            {
                                printf("INVALID");
                            }
                        }
                        else
                        {
                            printf("INVALID");
                        }
                    }
                    else
                    {
                        // VISA VALIDATOR
                        if (pS[0] == '4')
                        {
                            if (count(card) >= 13 && count(card) <= 16)
                            {
                                printf("VISA");
                            }
                            else
                            {
                                printf("INVALID");
                            }
                        }
                        else
                        {
                            printf("INVALID");
                        }
                    }
                }
            }
            else
            {
                printf("INVALID");
            }
        }
    }
    printf("\n");
}

int count(char string[])
{
    // character counter
    int numChar = 0;
    while (string[numChar] != '\0')
    {
        numChar++;
    }
    return numChar;
}

void removeChar(char *str, char charToRemmove)
{
    // character remover
    int i, j;
    int len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if (str[i] == charToRemmove)
        {
            for (j = i; j < len; j++)
            {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }
}

bool validCard(char *str)
{
    // card validater method
    int somaPar, somaImpar, result, temp, toInt(char), teste;
    char tempo[2];
    bool impar;
    somaPar = somaImpar = 0;
    if (count(str) % 2 == 0)
    {
        teste = 0;
    }
    else
    {
        teste = 1;
    }

    for (int i = (count(str) - 1); i >= 0; i--)
    {
        if ((i % 2) == teste)
        {
            temp = (toInt(str[i]));
            if (temp >= 5)
            {
                temp = (temp * 2) - 9;
            }
            else
            {
                temp = temp * 2;
            }
            somaPar += temp;
        }
        else
        {
            temp = toInt(str[i]);
            somaImpar += temp;
        }
    }
    result = (somaPar + somaImpar) % 10;
    if (result == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int toInt(char num)
{
    // char to int
    switch (num)
    {
        case '0':
            return 0;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break;
        case '3':
            return 3;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 5;
            break;
        case '6':
            return 6;
            break;
        case '7':
            return 7;
            break;
        case '8':
            return 8;
            break;
        case '9':
            return 9;
            break;
        default:
            return 0;
    }
}