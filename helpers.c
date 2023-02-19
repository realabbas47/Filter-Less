#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

uint8_t clorprcnt(uint8_t c, int num, int den);
uint8_t gtles(uint8_t t);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float x = 1.0 * (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue);
            int a = (int)round(x / 3);

            image[i][j].rgbtRed = a;
            image[i][j].rgbtGreen = a;
            image[i][j].rgbtBlue = a;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tr, tg, tb;

            tr = (int)round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189));
            if (tr > 255)
            {
                tr = 255;
            }

            tg = (int)round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168));
            if (tg > 255)
            {
                tg = 255;
            }

            tb = (int)round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131));
            if (tb > 255)
            {
                tb = 255;
            }

            image[i][j].rgbtRed = tr;
            image[i][j].rgbtGreen = tg;
            image[i][j].rgbtBlue = tb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[(width - 1) - j].rgbtRed = image[i][j].rgbtRed;
            img[(width - 1) - j].rgbtGreen = image[i][j].rgbtGreen;
            img[(width - 1) - j].rgbtBlue = image[i][j].rgbtBlue;
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = img[j].rgbtRed;
            image[i][j].rgbtGreen = img[j].rgbtGreen;
            image[i][j].rgbtBlue = img[j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*t)
    [width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // Taking averages of 3x3 pixels
            int tr = 0, tg = 0, tb = 0;
            int n = 0;
            for (int i = -1; i <= 1; ++i)
            {
                if (x + i >= 0 && x + i < height)
                {
                    for (int j = -1; j <= 1; ++j)
                    {
                        if (y + j >= 0 && y + j < width)
                        {
                            tr = tr + image[x + i][y + j].rgbtRed;
                            tg = tg + image[x + i][y + j].rgbtGreen;
                            tb = tb + image[x + i][y + j].rgbtBlue;
                            n++;
                        }
                    }
                }
            }
            float r = tr * 1.0 / n;
            float g = tg * 1.0 / n;
            float b = tb * 1.0 / n;
            t[x][y].rgbtRed = (int)round(r);
            t[x][y].rgbtGreen = (int)round(g);
            t[x][y].rgbtBlue = (int)round(b);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = t[i][j].rgbtRed;
            image[i][j].rgbtGreen = t[i][j].rgbtGreen;
            image[i][j].rgbtBlue = t[i][j].rgbtBlue;
        }
    }

    return;
}

// Returns percentaged values
uint8_t clorprcnt(uint8_t c, int num, int den)
{
    float x = 0;
    x = c * num * 1.0;
    int a = (int)round(x / den);
    return a;
}

// Return lesser
uint8_t gtles(uint8_t t)
{
    if (t > 225)
    {
        return 225;
    }
    return t;
}