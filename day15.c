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

int print_uarray(int num_columns, int num_rows, unsigned int array[num_rows][num_columns])
{
    int i, ii;
    for (ii = 0; ii < num_rows; ii++)
    {
        for (i = 0; i < num_columns; i++)
        {
            printf("%u ", array[ii][i]);
        }
        printf("\n");
    }
    printf("\n");
}

int decrement_surrounding(int x, int y, unsigned int current_distance, int num_columns, int num_rows, unsigned int grid[num_rows][num_columns], unsigned int distances[num_rows][num_columns])
{
    int i, ii;
    for (ii = -1; ii <= 1; ii++)
    {
        for (i = -1; i <= 1; i++)
        {
            if (((i != 0) || (ii != 0)) && (x + i >= 0) && (x + i < num_columns) && (y + ii >= 0) && (y + ii < num_rows))
            {
                if ((i != ii) && (i != -ii))
                { // to omit diagonals
                    if (current_distance + grid[y + ii][x + i] < distances[y + ii][x + i])
                    {
                        distances[y + ii][x + i] = current_distance + grid[y + ii][x + i];
                    }
                }
            }
        }
    }
    return 0;
}

int find_next_node(int *current_x, int *current_y, int num_columns, int num_rows, unsigned int distances[num_rows][num_columns], char visited[num_rows][num_columns])
{
    int i, ii;
    unsigned int smallest = -1;
    for (ii = 0; ii < num_rows; ii++)
    {
        for (i = 0; i < num_columns; i++)
        {
            if (!visited[ii][i] && distances[ii][i] < smallest)
            {
                printf("%d %d %u %u\n", i, ii, distances[ii][i], smallest);
                smallest = distances[ii][i];
                *current_x = i;
                *current_y = ii;
            }
        }
    }
}

int day15a()
{
    int num_rows = 0, num_columns = 0;
    char temp_char;

    FILE *file;
    file = fopen("input15.txt", "r");

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

        unsigned int grid[num_rows][num_columns];
        unsigned int distances[num_rows][num_columns];
        char visited[num_rows][num_columns];

        int i = 0, ii = 0;

        while (fscanf(file, "%c", &temp_char) != EOF)
        {
            if (temp_char != '\n')
            {
                grid[ii][i] = temp_char - '0';
                distances[ii][i] = -1;
                visited[ii][i] = 0;
                i++;
            }
            else
            {
                i = 0;
                ii++;
            }
        }

        print_uarray(num_columns, num_rows, grid);
        print_uarray(num_columns, num_rows, distances);

        int current_x = 0, current_y = 0;
        unsigned int current_distance = 0;
        distances[0][0] = 0;
        while ((current_x < num_columns - 1) || current_y < num_columns - 1)
        {
            printf("current %d %d \n", current_x, current_y);
            visited[current_y][current_x] = 1;
            current_distance = distances[current_y][current_x];
            decrement_surrounding(current_x, current_y, current_distance, num_columns, num_rows, grid, distances);
            find_next_node(&current_x, &current_y, num_columns, num_rows, distances, visited);
        }
        print_uarray(num_columns, num_rows, distances);
        printf("minimum distance to bottom right: %u\n", distances[num_rows - 1][num_columns - 1]);
    }
}

int main()
{
    day15a();
    return 0;
}