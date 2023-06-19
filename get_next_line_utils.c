/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathan <jonathan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:41:53 by jonathan          #+#    #+#             */
/*   Updated: 2023/06/19 09:43:01 by jonathan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *list)
{
	int		i;
	t_list	*current;

	if (list == NULL)
		return (0);
	current = get_last_element_from_list(list);
	i = 0;
	while (current->string[i])
	{
		if (current->string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*get_last_element_from_list(t_list *list)
{
	t_list	*last;

	last = list;
	while (last && last->next)
		last = last->next;
	return (last);
}

void	create_line(char **line, t_list *list)
{
	int	i;
	int	j;

	j = 0;
	while (list)
	{
		i = 0;
		while (list->string[i])
		{
			if (list->string[i] == '\n')
			{
				j++;
				break ;
			}
			j++;
			i++;
		}
			list = list->next;
	}
	*line = malloc(j + 1);
}

int	get_string_length(const char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

void	free_list(t_list *list)
{
	t_list	*current;
	t_list	*next;

	current = list;
	while (current)
	{
		free(current->string);
		next = current->next;
		free(current);
		current = next;
	}
}
