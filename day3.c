#include <stdio.h>

int pow(int base, int exponent)
{
    int i;
    int result = 1;
    for (i = 0; i < exponent; i++)
        result *= base;
    return result;
}

int day3a()
{
    int line_length = 12;
    int num_lines = 0, i = 0, gamma = 0, epsilon = 0;

    int totals[line_length];
    for (i = 0; i < line_length; i++)
        totals[i] = 0;

    char str[line_length];

    FILE *file;
    file = fopen("input3.txt", "r");
    if (file)
    {
        while (fscanf(file, "%s", &str) != EOF)
        {
            num_lines++;
            for (i = 0; i < line_length; i++)
            {
                if (str[i] == '1')
                {
                    totals[i]++;
                }
            }
        }
        fclose(file);
    }
    for (i = 0; i < line_length; i++)
    {
        if ((float)totals[i] / (float)num_lines > 0.5)
            gamma += pow(2, line_length - i - 1);
    }
    epsilon = pow(2, line_length) - gamma - 1;
    printf("gamma = %d, epsilon = %d, power consumption = %d \n", gamma, epsilon, gamma * epsilon);

    return 0;
}

int day3b(int flipped)
{
    int line_length = 12;
    int num_lines = 1000;
    int i = 0, ii = 0, gamma = 0, epsilon = 0;
    int total;
    char good_bit;
    int num_good_strings = num_lines;

    struct line
    {
        char str[line_length + 1];
        int good; // boolean, 1 for true and 0 for false
    };
    struct line lines[num_lines];

    FILE *file;
    file = fopen("input3.txt", "r");
    if (file)
    {
        while (fscanf(file, "%s", lines[i].str) != EOF)
        {
            lines[i].good = 1;
            i++;
        }
        fclose(file);
    }

    for (ii = 0; (ii < line_length) && (num_good_strings > 1); ii++)
    {
        total = 0;
        for (i = 0; i < num_lines; i++)
        {
            if ((lines[i].good == 1) && (lines[i].str[ii] == '1'))
                total++;
        }
        if (flipped)
        {
            if ((float)total / (float)num_good_strings >= 0.5)
                good_bit = '0';
            else
                good_bit = '1';
        }
        else
        {
            if ((float)total / (float)num_good_strings >= 0.5)
                good_bit = '1';
            else
                good_bit = '0';
        }

        for (i = 0; i < num_lines; i++)
        {
            if ((lines[i].good == 1) && (lines[i].str[ii] != good_bit))
            {
                lines[i].good = 0;
                num_good_strings--;
            }
        }
    }

    int oxygen_generator = 0;
    for (ii = 0; ii < num_lines; ii++)
    {
        if (lines[ii].good == 1)
        {
            printf("%s \n", lines[ii].str);
            for (i = 0; i < line_length; i++)
                if (lines[ii].str[i] == '1')
                {
                    oxygen_generator += pow(2, line_length - i - 1);
                }
        }
    }
    if (flipped)
    {
        printf("CO2 scrubber: %d \n", oxygen_generator);
    }
    else
    {
        printf("oxygen generator: %d \n", oxygen_generator);
    }

    return oxygen_generator;
}

int main()
{
    day3a();
    printf("product: %d \n", day3b(0) * day3b(1));
    return 0;
}