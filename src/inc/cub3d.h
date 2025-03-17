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

/*
========== INCLUDES =========
*/


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>

/*
 * ========= STRUCTURES =========
 *
 * */
typedef struct s_parser
{
}   t_parser;

typedef struct s_game
{
}   t_game;

/*
 * ========= PROTOTYPES =========
 *
 * */
int parse_cub(int argc, char **argv);
int check_map(char *file);




/*
    * ========= UTILS =========
    *
*/
int ft_strlen(char *str);
int ft_strcmp(char *s1, char *s2);
#endif
