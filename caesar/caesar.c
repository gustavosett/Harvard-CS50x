#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    int x;
    string word;
    char letter;
    if (argc != 2)
    {
        printf("Usage:  ./caesar key\n");
        return 1;
    }
    if (islower(argv[1][1]))
    {
        printf("Usage:  ./caesar key\n");
        return 1;
    }
    for (int z = 0, y = strlen(argv[1]); z < y; z++)
    {
        if (!(isdigit(argv[1][z])))
        {
            printf("Usage:  ./caesar key\n");
            return 1;
        }
        x = atoi(argv[1]);
        word = get_string("Text:  ");
        printf("Ciphertext:  ");
        for (int w = 0, p = strlen(word); w < p; w++)
        {
            letter = word[w];
            if (isupper(letter))
            {
                printf("%c", (letter - 65 + x) % 26 + 65);
            }
            else
            {
                if (islower(letter))
                {
                    printf("%c", (letter - 97 + x) % 26 + 97);
                }
                else
                {
                    printf("%c", letter);
                }
            }
        }
        printf("\n");
        return 0;
    }
}