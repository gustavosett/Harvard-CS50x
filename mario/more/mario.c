#include <cs50.h>
#include <stdio.h>

int hashTag(int);

int main(void)
{
    int heigh, i, a;
    printf("Heigh: ");
    scanf("%d", &heigh);
    // aqui é se der caquinha :(
    while (true)
    {
        if (heigh <= 0)
        {
            printf("Digite um valor maior que 0!\n");
            scanf("%d", &heigh);
        }
        else
        {
            if (heigh > 8)
            {
                printf("Digite um valor menor que 9!\n");
                scanf("%d", &heigh);
            }
            else
            {
                break;
            }
        }
    }
    for (i = 1; i <= heigh; i++)
    {
        for (a = (heigh - 1); a >= i; a--)
        {
            printf(" ");
        }
        hashTag(i);
        printf("  ");
        hashTag(i);
        printf("\n");
    }
}
// aqui faz os hashtag
int hashTag(int num)
{
    int a;
    for (a = 1; a <= num; a++)
    {
        printf("#");
    }
    return 0;
}