/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:16:23 by tndreka           #+#    #+#             */
/*   Updated: 2025/03/28 18:55:02 by tndreka          ###   ########.fr       */
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
/*   Updated: 2025/03/20 17:42:39 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>


# include "../../MLX42/include/MLX42/MLX42.h"
# include "libft/includes/libft.h"

#define WIDTH 1024
#define HEIGHT 1024


typedef struct s_parser
{
    char	**map2d;
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    int     start_line_map;
}   t_parser;

typedef struct s_game
{
	mlx_t*		mlx;
	t_parser	parser;
}   t_game;

//MAP_BUILD
int     map_build(int argc, char **argv, t_parser *parser);
int     check_map(char *file, t_parser *parser);
void    copy_map(int fd, t_parser *parser);
void    print_map(t_parser *parser);
//INIT_MAP
void    init_textures(t_parser *parser);
//PARSE_TEXTURES
int     parse_textures(t_parser *parser);
#endif
