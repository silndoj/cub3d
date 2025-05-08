/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:21 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/08 21:17:39 by silndoj          ###   ########.fr       */
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

# define WIDTH 1024
# define HEIGHT 768
# define GRID_COLS 16
# define GRID_ROWS 12
# define COLOR_W 0xFF0000FF
# define COLOR_S 0xFFFFFFFF

typedef struct s_parser
{
    int map[GRID_ROWS][GRID_COLS];  // Static array
    int width;
    int height;
    int floor_r, floor_g, floor_b;
    int ceil_r, ceil_g, ceil_b;
}   t_parser;

typedef struct s_player
{
	double	px;
	double	py;
	double	dirX;
    double	dirY;
    double	planeX;
    double	planeY;
    double	cameraX;
	double	rDirX;
	double	rDirY;
	double	dDistX;
	double	dDistY;
	double	sDistX;
	double	sDistY;
	double	pWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		mapX;
	int		mapY;
}	t_player;

typedef struct s_game
{
	mlx_t*			mlx;
	mlx_image_t*	img;
	mlx_texture_t*	textures[4];
    mlx_image_t*	texture_img;
	int				y;
	double			wall_x;
    int				tex_x, tex_y;
    double			tex_pos, step;
	t_player		player;
	t_parser		parser;
}   t_game;

//***game_build/MAP_BUILD.C
int		map_build(int argc, char **argv, t_parser *parser);
int		check_map(char *file, t_parser *parser);
void    copy_map(int fd, t_parser *parser);
void	print_map(t_parser *parser);

//***utils_box/ERROR.C
void	errno_exit(void);
void	errno_error_mlx(void);

//***utils_box/MAP_DRAW.C 
void	cast_ray(t_game *g);

#endif
