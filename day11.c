#include <stdio.h>

int print_array(int num_columns, int num_rows, int array[num_rows][num_columns])
{
    int i, ii;
    for (ii = 0; ii < num_rows; ii++)
    {
        for (i = 0; i < num_columns; i++)
        {
            printf("%d", array[ii][i]);
        }
        printf("\n");
    }
    printf("\n");
}

int increment_all(int num_columns, int num_rows, int grid[num_rows][num_columns])
{
    int i, ii;

    for (ii = 0; ii < num_rows; ii++)
    {
        for (i = 0; i < num_columns; i++)
        {
            grid[ii][i]++;
        }
    }
    return 0;
}

int reset_flashed(int num_columns, int num_rows, int grid[num_rows][num_columns], int flashed[num_rows][num_columns])
{
    int i, ii;
    for (ii = 0; ii < num_rows; ii++)
    {
        for (i = 0; i < num_columns; i++)
        {
            if (flashed[ii][i])
            {
                flashed[ii][i] = 0;
                grid[ii][i] = 0;
            }
        }
    }
    return 0;
}

int count_9s(int num_columns, int num_rows, int grid[num_rows][num_columns], int flashed[num_rows][num_columns])
{
    int i, ii;
    int counter = 0;
    for (ii = 0; ii < num_rows; ii++)
    {
        for (i = 0; i < num_columns; i++)
        {
            if ((grid[ii][i] > 9) && !flashed[ii][i])
                counter++;
        }
    }
    return counter;
}

int increment_surrounding(int x, int y, int num_columns, int num_rows, int grid[num_rows][num_columns])
{
    int i, ii;
    for (ii = -1; ii <= 1; ii++)
    {
        for (i = -1; i <= 1; i++)
        {
            if (((i != 0) || (ii != 0)) && (x + i >= 0) && (x + i < num_columns) && (y + ii >= 0) && (y + ii < num_rows))
            {
                grid[y + ii][x + i]++;
            }
        }
    }
    return 0;
}

int flash(int x, int y, int num_columns, int num_rows, int grid[num_rows][num_columns], int flashed[num_rows][num_columns])
{
    if (!flashed[y][x] && (grid[y][x] > 9))
    {
        flashed[y][x] = 1;
        increment_surrounding(x, y, num_columns, num_rows, grid);
        return 1;
    }
    return 0;
}

int all_flashed(int flash_counter, int num_columns, int num_rows)
{
    if (num_columns * num_rows == flash_counter)
    {
        return 1;
    }
    return 0;
}

int step(int num_columns, int num_rows, int grid[num_rows][num_columns], int flashed[num_rows][num_columns])
{
    int flash_counter = 0;
    increment_all(num_columns, num_rows, grid);
    int i, ii;
    while (count_9s(num_columns, num_rows, grid, flashed) > 0)
    {
        for (ii = 0; ii < num_rows; ii++)
        {
            for (i = 0; i < num_columns; i++)
            {
                flash_counter += flash(i, ii, num_columns, num_rows, grid, flashed);
            }
        }
    }
    reset_flashed(num_columns, num_rows, grid, flashed);
    return flash_counter;
}

int day9a()
{
    int num_rows = 0, num_columns = 0;
    char temp_char;

    FILE *file;
    file = fopen("input11.txt", "r");

    if (file)
    {
        while ((fscanf(file, "%c", &temp_char)) != EOF)
        {
            if (temp_char == '\n') // newline is 32522
            {
                break;
            }
            num_columns++;
        }
        rewind(file);
        char *temp_str[num_columns + 1];

        while (fscanf(file, "%s", &temp_str) != EOF)
        {
            num_rows++;
        }

        rewind(file);

        int grid[num_rows][num_columns];
        int flashed[num_rows][num_columns];

        int i = 0, ii = 0;

        while (fscanf(file, "%c", &temp_char) != EOF)
        {
            if (temp_char != '\n')
            {
                grid[ii][i] = temp_char - '0';
                flashed[ii][i] = 0;
                i++;
            }
            else
            {
                i = 0;
                ii++;
            }
        }

        print_array(num_columns, num_rows, grid);

        int j;
        int total_flash_counter = 0;
        int step_flash_counter = 0;
        for (j = 0; j < 1000; j++)
        {
            step_flash_counter = step(num_columns, num_rows, grid, flashed);
            if (all_flashed(step_flash_counter, num_columns, num_rows))
            {
                printf("All flashed on step %d\n", j + 1);
            }
            total_flash_counter += step_flash_counter;
            // print_array(num_columns, num_rows, grid);
        }
        printf("total number of flashes: %d\n", total_flash_counter);
    }
    fclose(file);

    return 0;
}

int main()
{
    day9a();
    return 1;
}