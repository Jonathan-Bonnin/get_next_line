#include "get_next_line.h"

char *get_next_line(int fd)
{
    static t_list *list = NULL;
    char            *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    line = NULL;
    read_and_store(fd, &list);
    if (list == NULL)
        return (NULL);
    take_line(list, &line);
    clean_list(&list);
    if (line[0] == '\0')
    {
        free_list(list);
        list = NULL;
        free(line);
        return (NULL);
    }
    return (line);
}

void read_and_store(int fd, t_list **list)
{
    char    *buffer;
    int     count_read;

    count_read = 1;    
    while(!found_newline(*list) && count_read != 0)
    {
        buffer = malloc(BUFFER_SIZE + 1);
        if (buffer == NULL)
            return ;
        count_read = (int) read(fd, buffer, BUFFER_SIZE);
        if ((*list == NULL && count_read == 0) || count_read == -1)
        {
            free(buffer);
            return ;
        }

        buffer[count_read] = '\0';
        add_to_list(list, buffer, count_read);
        free(buffer);
    } 
}

void add_to_list(t_list **list, char *buffer, int count_read)
{
    int i;
    t_list  *last;
    t_list  *new;

    new = malloc(sizeof(t_list));
    if (new == NULL)
        return ;
    new->next = NULL;
    new->string = malloc(count_read + 1);
    if (new->string == NULL)
        return ;
    i = 0;
    while (buffer[i] && i < count_read)
    {
        new->string[i] = buffer[i];
        i++;
    }
    new->string[i] = '\0';
    if (*list == NULL)
    {
        *list = new;
        return ;
    }
    //&(*list)->last;
    last = get_last_element_from_list(*list);
    last->next = new;
    //add_new_to_last(*list, new);
}

void  take_line(t_list *list, char **line)
{
    int i;
    int j;

    if (list == NULL)
        return ;
    create_line(line, list);
    if(*line == NULL)
        return ;
    j = 0;
    while (list)
    {
        i = 0;
        while (list->string[i])
        {
            if (list->string[i] == '\n')
            {
                (*line)[j++] = list->string[i];
                break;
            }
            (*line)[j++] = list->string[i++];
        }
        list = list->next;
    }
    (*line)[j] = '\0';
}

void clean_list(t_list **list)
{
    t_list *last;
    t_list *clean_node;
    int i;
    int j;

    clean_node = malloc(sizeof(t_list));
    if (list == NULL || clean_node == NULL)
        return ;
    clean_node->next = NULL;
    last = get_last_element_from_list(*list);
    i = 0;
    while (last->string[i] && last->string[i] != '\n')
        i++;
    if (last->string && last->string[i] == '\n')
        i++;
    clean_node->string = malloc(get_string_length(last->string) - i  + 1);
    if (clean_node->string == NULL)
		return ;
    j = 0;
    while(last->string[i])
        clean_node->string[j++] = last->string[i++];
    clean_node->string[j] = '\0';
    free_list(*list);
    *list = clean_node;
}