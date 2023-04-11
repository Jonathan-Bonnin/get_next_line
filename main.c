/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathan <jonathan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 08:51:56 by jonathan          #+#    #+#             */
/*   Updated: 2023/04/11 08:58:49 by jonathan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main (void)
{
    size_t bytes = 5;
    int file_descriptor = 1;
    char buf[50];
    read(file_descriptor, buf, bytes);
    return (0);
}