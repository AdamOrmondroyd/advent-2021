#include <stdio.h>

int day1a()
{
    int previous, current;
    int counter = 0;
    FILE *file;
    file = fopen("input1.txt", "r");
    if (file)
    {
        fscanf(file, "%d", &previous);
        while (fscanf(file, "%d", &current) != EOF)
        {
            if (current > previous)
                counter++;
            previous = current;
        }
        fclose(file);
        printf("There were %d increases \n", counter);
    }
}

int day1b()
{
    int length = 2000;
    int window_size = 3;
    int data[length];
    int previous_sum;
    int current_sum;
    int i = 0;
    int ii = 0;
    int counter = 0;
    FILE *file;
    file = fopen("input1.txt", "r");
    if (file)
    {
        while (fscanf(file, "%d", &data[i]) != EOF)
            i++;
        fclose(file);
    }
    i = 0;
    previous_sum = data[0] + data[1] + data[2];
    for (i = 1; i < length - 2; i++)
    {
        current_sum = 0;
        for (ii = 0; ii < window_size; ii++)
            current_sum += data[i + ii];
        if (current_sum > previous_sum)
            counter++;
        previous_sum = current_sum;
    }
    printf("There were %d increases with a window size of %d \n", counter, window_size);
}

int main()
{
    day1a();
    day1b();
    return 0;
}