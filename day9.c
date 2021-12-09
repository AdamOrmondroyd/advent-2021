#include <stdio.h>
#include <math.h>

int bubblesort(int num_elements, int elements[num_elements])
{
    int i, ii, temp;
    for (ii = 0; ii < num_elements - 1; ii++)
    {
        for (i = 0; i < num_elements - ii - 1; i++)
        {
            if (elements[i] > elements[i + 1])
            {
                temp = elements[i];
                elements[i] = elements[i + 1];
                elements[i + 1] = temp;
            }
        }
    }
}

int explore(int x, int y, int num_columns, int num_rows, int grid[num_rows][num_columns], int unexplored[num_rows][num_columns])
{
    if (!unexplored[y][x])
        return 0;
    int result = 1;
    unexplored[y][x] = 0;
    // printf("%d, %d\n", x, y);
    // printf("%d %d %d \n", (x > 0), (unexplored[y][x - 1]), (grid[y][x - 1] < 9));
    if ((x > 0) && (unexplored[y][x - 1]) && (grid[y][x - 1] < 9))
    {
        result += explore(x - 1, y, num_columns, num_rows, grid, unexplored);
    }
    if ((y > 0) && (unexplored[y - 1][x]) && (grid[y - 1][x] < 9))
    {
        result += explore(x, y - 1, num_columns, num_rows, grid, unexplored);
    }
    if ((x < num_columns - 1) && (unexplored[y][x + 1]) && (grid[y][x + 1] < 9))
    {
        result += explore(x + 1, y, num_columns, num_rows, grid, unexplored);
    }
    if ((y < num_rows - 1) && (unexplored[y + 1][x]) && (grid[y + 1][x] < 9))
    {
        result += explore(x, y + 1, num_columns, num_rows, grid, unexplored);
    }
    return result;
}

int day9a()
{
    unsigned long long int temp_llu;
    int num_rows = 0, num_columns = 0;
    int current_lowest_neighbour = 0;
    char temp_char;

    FILE *file;
    file = fopen("input9.txt", "r");

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
        // return 1;

        int grid[num_rows][num_columns];
        int unexplored[num_rows][num_columns];

        int i = 0, ii = 0;

        while (fscanf(file, "%c", &temp_char) != EOF)
        {
            if (temp_char != '\n')
            {
                grid[ii][i] = temp_char - '0';
                unexplored[ii][i] = 1;
                i++;
            }
            else
            {
                i = 0;
                ii++;
            }
        }

        printf("rows %d columns %d\n", num_rows, num_columns);
        int score_a = 0;
        int score_b = 1;
        int size;
        int largest_three[4]; // array of 4 so I can put most recent in and sort,
        // then just use three largest to calculate score
        int j;
        for (j = 0; j < 4; j++)
        {
            largest_three[j] = 0;
        }

        for (ii = 0; ii < num_rows; ii++)
        {
            for (i = 0; i < num_columns; i++)
            {
                current_lowest_neighbour = 10;
                // look up
                if (ii > 0 && grid[ii - 1][i] < current_lowest_neighbour)
                    current_lowest_neighbour = grid[ii - 1][i];
                // look right
                if (i < num_columns - 1 && grid[ii][i + 1] < current_lowest_neighbour)
                    current_lowest_neighbour = grid[ii][i + 1];
                // look down
                if (ii < num_rows - 1 && grid[ii + 1][i] < current_lowest_neighbour)
                    current_lowest_neighbour = grid[ii + 1][i];
                // look left
                if (i > 0 && grid[ii][i - 1] < current_lowest_neighbour)
                    current_lowest_neighbour = grid[ii][i - 1];
                if (current_lowest_neighbour > grid[ii][i])
                {
                    score_a += grid[ii][i] + 1;

                    size = explore(i, ii, num_columns, num_rows, grid, unexplored);

                    printf("basin found (%d, %d), size = %d\n", i, ii, size);

                    largest_three[0] = size;
                    bubblesort(4, largest_three);
                }
            }
        }
        score_b = largest_three[1] * largest_three[2] * largest_three[3];

        printf("part a: %d part b: %d\n", score_a, score_b);
    }
    fclose(file);
    return 0;
}

int main()
{
    day9a();
    return 1;
}