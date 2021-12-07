#include <stdio.h>

int day2a()
{
    char str[10];
    int stepsize = 0, x = 0, y = 0;
    FILE *file;
    file = fopen("input2.txt", "r");
    if (file)
    {
        while (fscanf(file, "%s %d", &str, &stepsize) != EOF)
        {
            if (str[0] == 'f')
                x += stepsize;
            if (str[0] == 'd')
                y += stepsize;
            if (str[0] == 'u')
                y -= stepsize;
        }

        fclose(file);
    }
    printf("The final position is %d, %d, which multiply to make %d \n", x, y, x * y);
    return 0;
}

int day2b()
{
    char str[10];
    int stepsize = 0, x = 0, y = 0, aim = 0;
    FILE *file;
    file = fopen("input2.txt", "r");
    if (file)
    {
        while (fscanf(file, "%s %d", &str, &stepsize) != EOF)
        {
            if (str[0] == 'f')
            {
                x += stepsize;
                y += aim * stepsize;
            }
            if (str[0] == 'd')
                aim += stepsize;
            if (str[0] == 'u')
                aim -= stepsize;
        }

        fclose(file);
    }
    printf("After actually figuring out the meanings, the final position is actually %d, %d, which multiply to make %d \n", x, y, x * y);
    return 0;
}

int main()
{
    day2a();
    day2b();
    return 0;
}