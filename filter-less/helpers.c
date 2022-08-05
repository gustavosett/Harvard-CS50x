#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            float Red = image[a][b].rgbtRed;
            float Green = image[a][b].rgbtGreen;
            float Blue = image[a][b].rgbtBlue;
            int ave = round((Red + Blue + Green) / 3);
            image[a][b].rgbtRed = image[a][b].rgbtGreen = image[a][b].rgbtBlue = ave;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            float oRed = image[a][b].rgbtRed;
            float oGreen = image[a][b].rgbtGreen;
            float oBlue = image[a][b].rgbtBlue;
            int sR = round(0.393 * oRed + 0.769 * oGreen + 0.189 * oBlue);
            int sG = round(0.349 * oRed + 0.686 * oGreen + 0.168 * oBlue);
            int sB = round(0.272 * oRed + 0.534 * oGreen + 0.131 * oBlue);
            if (sR > 255)
            {
                sR = 255;
            }
            if (sG > 255)
            {
                sG = 255;
            }
            if (sB > 255)
            {
                sB = 255;
            }
            image[a][b].rgbtRed = sR;
            image[a][b].rgbtBlue = sB;
            image[a][b].rgbtGreen = sG;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width / 2; b++)
        {
            RGBTRIPLE temp = image[a][b];
            image[a][b] = image[a][width - (b + 1)];
            image[a][width - (b + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            temp[a][b] = image[a][b];
        }
    }

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            int  tRed, tBlue, tGreen;
            tRed = tBlue = tGreen = 0;
            float count = 0.00;

            for (int c = -1; c < 2; c++)
            {
                for (int d = -1; d < 2; d++)
                {
                    int cX = a + c;
                    int cY = b + d;

                    if (cX < 0 || cX > (height - 1) || cY < 0 || cY > (width - 1))
                    {
                        continue;
                    }

                    tRed += image[cX][cY].rgbtRed;
                    tGreen += image[cX][cY].rgbtGreen;
                    tBlue += image[cX][cY].rgbtBlue;

                    count++;
                }

                temp[a][b].rgbtRed = round(tRed / count);
                temp[a][b].rgbtGreen = round(tGreen / count);
                temp[a][b].rgbtBlue = round(tBlue / count);
            }
        }
    }

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = temp[a][b].rgbtRed;
            image[a][b].rgbtGreen = temp[a][b].rgbtGreen;
            image[a][b].rgbtBlue = temp[a][b].rgbtBlue;
        }
    }
    return;
}
