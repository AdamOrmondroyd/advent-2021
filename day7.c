#include <stdio.h>

int abs(int x)
{
    if (x >= 0)
        return x;
    return -x;
}

int cost(int difference, int partb)
{
    difference = abs(difference);
    if (partb)
    {
        return difference * (difference + 1) / 2;
    }
    return difference;
}

int day7(int partb)
{
    int num_crabs = 0;
    int min_initial_position;
    int max_initial_position;
    int temp_int;
    char temp_char;
    int i = 0;
    int position;
    int reached_end = 0;
    FILE *file;

    // count number of crabs
    file = fopen("input7.txt", "r");
    if (file)
    {
        while ((fscanf(file, "%d", &temp_int) != EOF) && !reached_end)
        {
            num_crabs++;
            if (fscanf(file, "%c", &temp_char) == EOF)
                reached_end = 1;
        }
    }
    fclose(file);
    printf("there are %d crabs \n", num_crabs);

    int initial_positions[num_crabs];

    // read in crabs
    reached_end = 0;
    file = fopen("input7.txt", "r");
    if (file)
    {
        while (!reached_end && (fscanf(file, "%d", &temp_int) != EOF))
        {
            // printf("%d\n", temp_int);
            initial_positions[i] = temp_int;
            i++;
            if ((fscanf(file, "%c", &temp_char) == EOF) || i == num_crabs)
                reached_end = 1;
            // printf("end? %d\n", reached_end);
        }
    }
    fclose(file);
    // for (i = 0; i < num_crabs; i++)
    //     printf("%d\n", initial_positions[i]);

    // find min and max positions to iterate through

    min_initial_position = initial_positions[0];
    max_initial_position = min_initial_position;
    for (i = 1; i < num_crabs; i++)
    {
        if (initial_positions[i] < min_initial_position)
            min_initial_position = initial_positions[i];
        if (initial_positions[i] > max_initial_position)
            max_initial_position = initial_positions[i];
    }
    // printf("min: %d, max: %d \n", min_initial_position, max_initial_position);

    int costs[max_initial_position - min_initial_position + 1];

    // work out cost for each position between min and max
    for (position = min_initial_position; position <= max_initial_position; position++)
    {
        costs[position - min_initial_position] = 0;
        for (i = 0; i < num_crabs; i++)
        {
            costs[position - min_initial_position] += cost(position - initial_positions[i], partb);
        }
        //printf("cost for position %d: %d \n", position, costs[position - min_initial_position]);
    }

    int min_cost_index = 0;
    int min_cost = costs[min_cost_index];
    for (i = 1; i < (max_initial_position - min_initial_position + 1); i++)
    {
        if (costs[i] < min_cost)
        {
            min_cost_index = i;
            min_cost = costs[min_cost_index];
        }
    }
    printf("minimum cost %d at position %d \n", min_cost, min_cost_index);
    return 0;
}

int main()
{
    day7(0);
    day7(1);
    return 0;
}