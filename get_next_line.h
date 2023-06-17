/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathan <jonathan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 08:54:25 by jonathan          #+#    #+#             */
/*   Updated: 2023/06/16 09:55:39 by jonathan         ###   ########.fr       */
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
	char			*content;
	struct s_list	*next;
	struct s_list 	*last;
} t_list;
t_list *get_last_element_from_list (t_list *list);
int get_string_length(char *string);
void read_and_store(int fd, t_list **storage);
void take_line(t_list *storage, char **line);
void free_storage(t_list *storage);
int same_line (t_list *storage);
void clean_storage(t_list **storage);
void add_to_storage(t_list **storage, char *buffer, int count_chars_read);
void add_new_to_last(t_list *list, t_list *new);
void create_line(char **line, t_list *storage);
char *get_next_line(int fd);

#endif