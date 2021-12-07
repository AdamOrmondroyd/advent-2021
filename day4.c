#include <stdio.h>
#include <string.h>

struct bingo_grid
{
    int numbers[5][5];
    int row_counters[5];
    int column_counters[5];
    int unmarked_sum;
    int finished;
};

int initialise_grid(struct bingo_grid *grid)
{
    grid->unmarked_sum = 0;
    grid->finished = 0;
    int i, ii;
    for (ii = 0; ii < 5; ii++)
    {
        grid->row_counters[ii] = 0;
        grid->column_counters[ii] = 0;
        for (i = 0; i < 5; i++)
        {
            grid->unmarked_sum += grid->numbers[ii][i];
        }
    }
    return 0;
}

int update_grid(struct bingo_grid *grid, int call)
{
    if (grid->finished)
        return 0;
    int i = 0;
    int ii = 0;
    int found = 0;
    while ((ii < 5) && !found)
    {
        i = 0;
        while ((i < 5) && !found)
        {
            if (call == (*grid).numbers[ii][i])
            {
                found = 1;
                grid->unmarked_sum -= call;
                grid->row_counters[ii]++;
                grid->column_counters[i]++;
            }
            i++;
        }
        ii++;
    }
    for (i = 0; i < 5; i++)
    {
        if ((grid->row_counters[i] == 5) || (grid->column_counters[i] == 5))
        {
            grid->finished = 1;
            return grid->unmarked_sum * call;
        }
    }
    return 0;
}

int day4a()
{
    int num_calls = 100;
    int num_players = 100;
    int calls[num_calls];
    struct bingo_grid grids[num_players];

    char temp;

    int i = 0;
    int ii = 0;
    int iii = 0;
    FILE *file;
    file = fopen("input4.txt", "r");
    if (file)
    {
        // get calls
        do
        {
            fscanf(file, "%d%c", &calls[i], &temp);
            i++;
        } while (temp != '\n');

        // get grids
        for (iii = 0; iii < num_players; iii++)
        {
            fscanf(file, "%c", &temp); // deal with blank line
            for (ii = 0; ii < 5; ii++)
            {
                for (i = 0; i < 5; i++)
                {
                    fscanf(file, "%d%c", &grids[iii].numbers[ii][i], &temp);
                }
            }
            initialise_grid(&grids[iii]);
        }
        fclose(file);
    }

    int won = 0;
    int score = 0;
    i = 0;
    ii = 0;

    while (!won && (ii < num_calls))
    {
        printf("%d \n", calls[ii]);
        for (i = 0; i < num_players; i++)
        {
            score = update_grid(&grids[i], calls[ii]);
            if (score > 0)
            {
                printf("The winning grid was %d with %d points \n", i, score);
                //won = 1;
            }
        }
        ii++;
    }
}

int main()
{
    day4a();
    return 1;
}