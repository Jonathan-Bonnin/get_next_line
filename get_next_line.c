/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathan <jonathan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 08:36:05 by jonathan          #+#    #+#             */
/*   Updated: 2023/06/24 15:36:38 by jonathan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) == -1)
		return (NULL);
	line = NULL;
	read_and_store(fd, &list);
	if (list == NULL)
		return (NULL);
	create_line_from_list_data(list, &line);
	forward_list_to_new_line(&list);
	if (line[0] == '\0')
	{
		free_list(list);
		list = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_store(int fd, t_list **list)
{
	char	*buffer;
	int		count_read;

	count_read = 1;
	while (!found_new_line(*list) && count_read != 0)
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
		add_buffer_to_list(list, buffer, count_read);
		free(buffer);
	}
}

void	add_buffer_to_list(t_list **list, char *buffer, int count_read)
{
	int		i;
	t_list	*last;
	t_list	*new;

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
	last = get_last_element_from_list(*list);
	last->next = new;
}

void	create_line_from_list_data(t_list *list, char **line)
{
	int	str_index;
	int	line_index;

	if (list == NULL)
		return ;
	*line = malloc(get_line_length(list) + 1);
	if (*line == NULL)
		return ;
	line_index = 0;
	while (list)
	{
		str_index = 0;
		while (list->string[str_index])
		{
			if (list->string[str_index] == '\n')
			{
				(*line)[line_index++] = list->string[str_index];
				break ;
			}
			(*line)[line_index++] = list->string[str_index++];
		}
		list = list->next;
	}
	(*line)[line_index] = '\0';
}

void	forward_list_to_new_line(t_list **list)
{
	t_list	*last;
	t_list	*start_of_next_line;
	int		i;
	int		j;

	start_of_next_line = malloc(sizeof(t_list));
	if (list == NULL || start_of_next_line == NULL)
		return ;
	start_of_next_line->next = NULL;
	last = get_last_element_from_list(*list);
	i = 0;
	while (last->string[i] && last->string[i] != '\n')
		i++;
	if (last->string && last->string[i] == '\n')
		i++;
	start_of_next_line->string = malloc(get_string_length(last->string) - i + 1);
	if (start_of_next_line->string == NULL)
		return ;
	j = 0;
	while (last->string[i])
		start_of_next_line->string[j++] = last->string[i++];
	start_of_next_line->string[j] = '\0';
	free_list(*list);
	*list = start_of_next_line;
}
