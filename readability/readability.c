#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    int letters, words, sentences;

    string text = get_string("Text: ");

    letters = sentences = 0;
    words = 1;

    for (int a = 0; a < strlen(text); a++)
    {
        if (isalpha(text[a]))
        {
            letters++;
        }
        else if (text[a] == ' ')
        {
            words++;
        }

        else if (text[a] == '.' || text[a] == '?' || text[a] == '!')
        {
            sentences++;
        }
    }

    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}