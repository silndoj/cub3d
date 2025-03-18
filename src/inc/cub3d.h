/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:14:38 by tndreka           #+#    #+#             */
/*   Updated: 2025/03/18 16:34:39 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:21 by tndreka           #+#    #+#             */
/*   Updated: 2025/03/17 21:56:05 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>

#include "get_next_line.h"
#include "garbage_collector.h"


typedef struct s_parser
{
    char **map2d;
}   t_parser;

typedef struct s_game
{
}   t_game;


int parse_cub(int argc, char **argv, t_parser *parser);
int check_map(char *file, t_parser *parser);
void    copy_map(int fd, t_parser *parser);
void print_map(t_parser *parser);

int ft_strlen(char *str);
int ft_strcmp(char *s1, char *s2);
#endif
