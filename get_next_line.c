#include "get_next_line.h"

char *get_next_line(int fd)
{
    static t_list *storage = NULL;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    line = NULL;
    read_and_store(fd, &storage);
    if (storage == NULL)
        return (NULL);
    take_line(storage, &line);
    clean_storage(&storage);
    if (line[0] == '\0')
    {
        free_storage(storage);
        storage = NULL;
        free(line);
        return (NULL);
    }
    return (line);
}

void read_and_store(int fd, t_list **storage)
{
    char    *buffer;
    int     count_chars_read;
    
    while(same_line(*storage) && count_chars_read != 0)
    {
        buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (buffer == NULL)
            return ;
        count_chars_read = 1;
        count_chars_read = (int) read(fd, buffer, BUFFER_SIZE);
        if ((*storage == NULL && count_chars_read == 0) || count_chars_read == -1)
        {
            free(buffer);
            return ;
        }

        buffer[count_chars_read] = '\0';
        add_to_storage(storage, buffer, count_chars_read);
        free(buffer);
    } 
}

void add_to_storage(t_list **storage, char *buffer, int count_chars_read)
{
    int i;
    t_list  *new;

    new = malloc(sizeof(t_list));
    if (new == NULL)
        return ;
    new->next = NULL;
    new->content = malloc(sizeof(char) * count_chars_read + 1);
    if (new->content == NULL)
        return ;
    i = 0;
    while (buffer[i] && i < count_chars_read)
    {
        new->content[i] = buffer[i];
        i++;
    }
    new->content[i] = '\0';
    if (*storage == NULL)
    {
        *storage = new;
        return ;
    }
    //&(*storage)->last;
    add_new_to_last(*storage, new);
}

void  take_line(t_list *storage, char **line)
{
    int i;
    int j;

    if (storage == NULL)
        return ;
    create_line(line, storage);
    if(*line == NULL)
        return ;
    j = 0;
    while (storage)
    {
        i = 0;
        while (storage->content[i])
        {
            if (storage->content[i] == '\n')
            {
                (*line)[j++] = storage->content[i];
                break;
            }
            (*line)[j++] = storage->content[i];
        }
        storage = storage->next;
    }
    (*line)[j] = '\0';
}

void clean_storage(t_list **storage)
{
    t_list *last;
    t_list *clean_node;
    int i;
    int j;

    clean_node = malloc(sizeof(t_list));
    if (storage == NULL || clean_node == NULL)
        return ;
    clean_node->next = NULL;
    last = get_last_element_from_list(*storage);
    i = 0;
    while (last -> content[i] && last->content[i] != '\n')
        i++;
    if (last->content && last->content[i] == '\n')
        i++;
    clean_node->content = malloc(get_string_length(last->content) - i  + 1);
    while(last->content[i])
        clean_node->content[j++] = last->content[i++];
    clean_node->content[j] = '\0';
    free_storage(*storage);
    *storage = clean_node;
}