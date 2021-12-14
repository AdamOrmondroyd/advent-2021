#include <stdio.h>

int print_paper(int num_dots, int dots[2][num_dots], int last_x_fold, int last_y_fold)
{
    int i, ii, iii;
    char dot_here;
    for (iii = 0; iii < last_y_fold; iii++)
    {
        for (ii = 0; ii < last_x_fold; ii++)
        {
            dot_here = 0;

            for (i = 0; i < num_dots; i++)
            {
                if (dots[0][i] == ii && dots[1][i] == iii)
                {
                    dot_here = 1;
                }
            }
            if (dot_here)
            {
                printf("#");
            }
            else
            {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int day13a()
{
    int num_dots = 0;
    int num_folds = 0;
    char counting_folds = 0;
    char str[21];
    int x, y, i, ii;

    FILE *file;
    file = fopen("input13.txt", "r");
    if (file)
    {
        // find number of dots and inputs
        while (fscanf(file, "%s", str) != EOF)
        {
            if ('f' == str[0])
            {
                counting_folds = 1;
            }

            if (counting_folds)
            {
                num_folds++;
            }
            else
            {
                num_dots++;
            }
        }
        rewind(file);
        num_folds = num_folds / 3;

        int dots[2][num_dots];

        char fold_axis;
        int fold_position;
        // piece of paper is only as big as the last fold in that direction
        int last_x_fold, last_y_fold;

        // read dots
        for (i = 0; i < num_dots; i++)
        {
            if (fscanf(file, "%d,%d", &dots[0][i], &dots[1][i]) != EOF)
            {
                ;
            }
        }

        // iterate through folds

        for (ii = 0; ii < num_folds; ii++)
        {
            if (fscanf(file, "%*s %*s %c=%d", &fold_axis, &fold_position) != EOF)
            {

                for (i = 0; i < num_dots; i++)
                {
                    if (('x' == fold_axis) && (dots[0][i] > fold_position))
                    {
                        dots[0][i] = 2 * fold_position - dots[0][i];
                        last_x_fold = fold_position;
                    }
                    if (('y' == fold_axis) && (dots[1][i] > fold_position))
                    {
                        dots[1][i] = 2 * fold_position - dots[1][i];
                        last_y_fold = fold_position;
                    }
                }
            }

            if (0 == ii)
            {
                // count non_duplicates
                char duplicate;
                int counter = 0;

                for (ii = 0; ii < num_dots; ii++)
                {
                    duplicate = 0;
                    for (i = 0; (i < ii && !duplicate); i++)
                    {
                        if (dots[0][i] == dots[0][ii] && dots[1][i] == dots[1][ii])
                        {
                            duplicate = 1;
                        }
                    }
                    if (!duplicate)
                    {
                        counter++;
                    }
                }
                printf("there are %d holes remaining after the first fold\n", counter);
            }
            if (num_folds - 1 == ii)
            {
                print_paper(num_dots, dots, last_x_fold, last_y_fold);
            }
        }

        fclose(file);
    }
    return 0;
}

int main()
{
    day13a();
    return 0;
}