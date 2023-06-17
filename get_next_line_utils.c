#include "get_next_line.h"

int same_line (t_list *storage) 
{
    int i;

    t_list *current;

    if (storage == NULL)
        return (0);
    storage = get_last_element_from_list(storage);

    i = 0;
    while (storage->content[i]) 
    {
        if (storage->content[i] == '\n')
            return (0);
        i++;
    }
    return (1);     
}

t_list *get_last_element_from_list (t_list *list)
{
    while(list && list->next)
        list = list->next;
    return (list);
}

void add_new_to_last(t_list *list, t_list *new)
{
    list = get_last_element_from_list(list);
    list->next = new;
}

void create_line(char **line, t_list *storage)
{
    int i;
    int j;

    j = 0;
    while (storage)
    {
        i = 0;
        while (storage->content[i])
        {
            if(storage->content[i] == '\n')
            {
                j++;
                break;
            }
            j++;
            i++;
        }
        storage = storage->next;
    }
    *line = malloc(j + 1);
}

int get_string_length(char *string)
{
    int i;
    i = 0;
    while (string[i])
        i++;
    return (i);
}

void free_storage(t_list *storage)
{
    t_list *current;
    t_list *next;

    current = storage;
    while (current)
    {
        free(current->content);
        next = current->next;
        free(current);
        current = next;
    }
}