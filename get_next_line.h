/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathan <jonathan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 08:54:25 by jonathan          #+#    #+#             */
/*   Updated: 2023/06/19 09:31:52 by jonathan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/* Struct*/
typedef struct s_list
{
	char			*string;
	struct s_list	*next;
} t_list;
int found_newline (t_list *list);
t_list *get_last_element_from_list (t_list *list);
int get_string_length(const char *string);
void read_and_store(int fd, t_list **list);
void take_line(t_list *list, char **line);
void free_list(t_list *list);
void clean_list(t_list **list);
void add_to_list(t_list **list, char *buffer, int count_read);
//void add_new_to_last(t_list *list, t_list *new);
void create_line(char **line, t_list *list);
char *get_next_line(int fd);

#endif