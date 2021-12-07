#include <stdio.h>
#include <stdlib.h>

struct list_element
{
    int value;
    struct list_element *next_element_ptr;
};

int list_append(struct list_element *list_ptr, int value)
{
    struct list_element *new_ptr = malloc(sizeof(struct list_element));
    new_ptr->value = value;
    new_ptr->next_element_ptr = NULL;

    struct list_element *current = list_ptr;

    while (current->next_element_ptr != NULL)
    {
        current = current->next_element_ptr;
    }

    current->next_element_ptr = new_ptr;
    return 0;
}

int print_list(struct list_element *list_ptr)
{
    printf("%d,", list_ptr->value);
    if (list_ptr->next_element_ptr)
    {
        return print_list(list_ptr->next_element_ptr);
    }
    printf("\n");
    return 0;
}

int iterate(struct list_element *current_fish_list, struct list_element *new_fish_list, int num_new_fish)
{
    if (current_fish_list->value == 0)
    {
        current_fish_list->value = 6;
        if (num_new_fish == 0)
        {
            struct list_element *new_ptr = malloc(sizeof(struct list_element));
            new_ptr->next_element_ptr = NULL;
            new_ptr->value = 8;
            new_fish_list = new_ptr;
        }
        else
        {
            list_append(new_fish_list, 8);
        }
        num_new_fish++;
    }
    else
    {
        current_fish_list->value--;
    }
    if (current_fish_list->next_element_ptr == NULL)
    {
        current_fish_list->next_element_ptr = new_fish_list;
        return num_new_fish;
    }
    else
    {
        return iterate(current_fish_list->next_element_ptr, new_fish_list, num_new_fish);
    }
}

int day6a()
{
    int temp_int;
    char temp_char;
    int num_days = 80;
    int i = 0;
    unsigned long long int num_fish = 0;
    int inc;
    struct list_element list, *list_ptr = &list;
    FILE *file;
    file = fopen("input_example.txt", "r");
    if (file)
    {
        while (fscanf(file, "%d%c", &temp_int, &temp_char) != EOF) // && (inc == 2))
        {
            if (i == 0) // create first element of list
            {
                list_ptr->value = temp_int;
                list_ptr->next_element_ptr = NULL;
            }
            else
            {

                list_append(list_ptr, temp_int);
            }
            i++;
            num_fish++;
        }
        fclose(file);
    }
    //print_list(list_ptr);

    for (i = 0; i < num_days; i++)
    {
        num_fish += iterate(list_ptr, NULL, 0);
        printf("after day %d, %d fish \n", i, num_fish);
        //print_list(list_ptr);
    }
    printf("%d \n", num_fish);
}

int main()
{
    day6a();
    return 0;
}