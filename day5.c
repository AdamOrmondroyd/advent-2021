#include <stdio.h>

int abs(int x)
{
    if (x >= 0)
        return x;
    return -x;
}

int points(int coordinate_pair[], int grid[1000][1000])
{
    int delta_x = coordinate_pair[2] - coordinate_pair[0];
    int delta_y = coordinate_pair[3] - coordinate_pair[1];

    printf("%d %d \n", delta_x, delta_y);

    // // if not horizontal or vertical
    // if ((delta_x != 0) && (delta_y != 0))
    //     return 0;

    int x_step = 0;
    if (delta_x != 0)
        x_step = delta_x / abs(delta_x);
    int y_step = 0;
    if (delta_y != 0)
        y_step = delta_y / abs(delta_y);

    int num_steps;
    int i = 0;
    if (delta_x != 0)
    {
        num_steps = abs(delta_x);
    }
    else
    {
        num_steps = abs(delta_y);
    }

    for (i = 0; i <= num_steps; i++)
    {
        printf("%d, %d \n", coordinate_pair[0] + x_step * i, coordinate_pair[1] + y_step * i);
        grid[coordinate_pair[1] + y_step * i][coordinate_pair[0] + x_step * i]++;
    }
    return 1;
}

int day5a()
{
    int i = 0;
    int ii = 0;
    int coordinates[4];
    int grid[1000][1000];

    for (ii = 0; ii < 1000; ii++)
    {
        for (i = 0; i < 1000; i++)
        {
            grid[ii][i] = 0;
        }
    }

    FILE *file;
    file = fopen("input5.txt", "r");
    printf("here");
    if (file)
    {
        while (fscanf(file, "%d,%d -> %d,%d", &coordinates[0], &coordinates[1], &coordinates[2], &coordinates[3]) != EOF)
        {
            printf("here\n");
            points(coordinates, grid);
        }
    }

    int counter = 0;
    for (ii = 0; ii < 1000; ii++)
    {
        for (i = 0; i < 1000; i++)
        {
            if (grid[ii][i] > 1)
                counter++;
            printf("%d ", grid[ii][i]);
        }
        printf("\n");
    }
    printf("There are %d overlaps", counter);
}

int main()
{
    day5a();
    return 1;
}