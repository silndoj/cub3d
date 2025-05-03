/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:16:23 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/03 20:41:09 by tndreka          ###   ########.fr       */
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
/*   Updated: 2025/04/30 02:38:18 by silndoj          ###   ########.fr       */
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
# include <errno.h>


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

//MAP_BUILD.C
int		map_build(int argc, char **argv, t_parser *parser);
int 	check_map(char *file, t_parser *parser);
void    copy_map(int fd, t_parser *parser);
void 	print_map(t_parser *parser);
int    parse_textures(t_parser *parser);
void 	init_textures(t_parser *parser);

//Util Box
int	errno_exit(void);

#endif