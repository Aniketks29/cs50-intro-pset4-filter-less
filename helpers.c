#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width;  j++)
        {
            // Calculating average of each pixel
            float average = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            // Assigning avg value to original Blue value
            image[i][j].rgbtBlue = (int)round(average);

            // Assigning avg value to original Green value
            image[i][j].rgbtGreen = (int)round(average);

            // Assigning avg value to original Red value
            image[i][j].rgbtRed = (int)round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaBlue = 0, sepiaRed = 0, sepiaGreen = 0; //Defining temporary sepia Red, Green and Blue
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculating sepiaRed from formula
            sepiaRed = (0.393 * (float)image[i][j].rgbtRed) + (0.769 * (float)image[i][j].rgbtGreen) + (0.189 * (float)image[i][j].rgbtBlue);

            //Calculating sepiaGreen from formula
            sepiaGreen = (0.349 * (float)image[i][j].rgbtRed) + (0.686 * (float)image[i][j].rgbtGreen) + (0.168 * (float)image[i][j].rgbtBlue);

            //Calculating sepiaBlue from formula
            sepiaBlue = (0.272 * (float)image[i][j].rgbtRed) + (0.534 * (float)image[i][j].rgbtGreen) + (0.131 * (float)image[i][j].rgbtBlue);

            if (sepiaBlue > 255)            //Capping the sepiaBlue value to 255 if it exceeds 255
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = (int)round(sepiaBlue);   // Assigning sepiaBlue to original Blue
            }

            if (sepiaGreen > 255)           //Capping the sepiaGreen value to 255 if it exceeds 255
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = (int)round(sepiaGreen); // Assigning sepiaGreen to original Green
            }

            if (sepiaRed > 255)             //Capping the sepiaRed value to 255 if it exceeds 255
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = (int)round(sepiaRed);     // Assigning sepiaRed to original Red
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0, j = width - 1; k < j; k++, j--)
        {
            RGBTRIPLE temp = image[i][k];       // Assigning image value to temp value for swapping
            image[i][k] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];      //creating a temp value storing file so that we don't alter the calculations

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    float avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4;

                    float avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4;

                    float avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4;

                    //storing avg red value in temp red
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    //storing avg green value in temp green
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    //storing avg blue value in temp blue
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else if (j == width - 1)
                {
                    float avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4;

                    float avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4;

                    float avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4;

                    //storing avg red value in temp red
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    //storing avg green value in temp green
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    //storing avg blue value in temp blue
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else
                {
                    float avgRed = (float)(image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;

                    float avgGreen = (float)(image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;

                    float avgBlue = (float)(image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;

                    //storing avg red value in temp red
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    //storing avg green value in temp green
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    //storing avg blue value in temp blue
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    float avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4;

                    float avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4;

                    float avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4;

                    //storing avg red value in temp red
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    //storing avg green value in temp green
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    //storing avg blue value in temp blue
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else if (j == width - 1)
                {
                    float avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4;

                    float avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4;

                    float avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4;

                    //storing avg red value in temp red
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    //storing avg green value in temp green
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    //storing avg blue value in temp blue
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else
                {
                    float avgRed = (float)(image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6;

                    float avgGreen = (float)(image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6;

                    float avgBlue = (float)(image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6;

                    //storing avg red value in temp red
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    //storing avg green value in temp green
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    //storing avg blue value in temp blue
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
            }
            else if ((i > 0) && (i < height - 1))
            {
                if (j == 0)
                {
                    float avgRed = (float)(image[i][j + 1].rgbtRed + image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;

                    float avgGreen = (float)(image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;

                    float avgBlue = (float)(image[i][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;

                    //storing avg red value in temp red
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    //storing avg green value in temp green
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    //storing avg blue value in temp blue
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else if (j == width - 1)
                {
                    float avgRed = (float)(image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6;

                    float avgGreen = (float)(image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6;

                    float avgBlue = (float)(image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6;

                    //storing avg red value in temp red
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    //storing avg green value in temp green
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    //storing avg blue value in temp blue
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else
                {
                    float avgRed = (float)(image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9;

                    float avgGreen = (float)(image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9;

                    float avgBlue = (float)(image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9;

                    //storing avg red value in temp red
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    //storing avg green value in temp green
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    //storing avg blue value in temp blue
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
            }
        }
    }


    // assigning temp value to original value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            image[i][j].rgbtRed = temp[i][j].rgbtRed;

            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;

            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
