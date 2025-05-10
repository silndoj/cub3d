/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:21 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/10 03:42:47 by tndreka          ###   ########.fr       */
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

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_parser
{
	char	**map2d;
	int		**map1;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	player_dir;
	int		start_line_map;
	int		map_width;
	int		map_height;
	int		x;
	int		y2;
	int		player_pos_x;
	int		player_pos_y;
	t_color	floor;
	t_color	ceiling;
	bool	map_found;
	bool	all_elements;
	bool	no_found;
	bool	so_found;
	bool	we_found;
	bool	ea_found;
	bool	f_found;
	bool	c_found;
	bool	floor_set;
	bool	ceiling_set;
	bool	player_found;
	bool	invalid_map;
	int		map[GRID_ROWS][GRID_COLS];
	int		width;
	int		height;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceil_r;
	int		ceil_g;
	int		ceil_b;
	int		l_h;
	int		d_s;
	int		d_e;
	int		y1;
	int		t_x;
	int		t_y;

}				t_parser;

typedef struct s_player
{
	double	px;
	double	py;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	rdir_x;
	double	rdir_y;
	double	ddist_x;
	double	ddist_y;
	double	sdist_x;
	double	sdist_y;
	double	pw_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
}				t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*texture_img;
	mlx_texture_t	*textures[4];
	int				y;
	int				tex_x;
	int				tex_y;
	int				start;
	int				end;
	double			wall_x;
	double			tex_pos;
	double			step;
	t_player		player;
	t_parser		parser;
}				t_game;

//***game_build/MAP_BUILD.C
int			map_build(int argc, char **argv, t_parser *parser);
int			check_map(char *file, t_parser *parser);
void		copy_map(int fd, t_parser *parser);
void		print_map(t_parser *parser);
int			parse_map(t_parser *parser);
void		init_map(t_parser *parser);

//***utils_box/ERROR.C
void	errno_exit(void);
void	errno_error_mlx(void);
int		exit_error(const char *msg);


//***utils_box/MAP_DRAW.C 
void	cast_ray(t_game *g);

//***utils_box/HANDLE_HOOK.C 
void	ft_hook(void *param);

//***utils_box/UTILS.C
uint32_t	make_mlx_color(int r, int g, int b);
void		clear_image(mlx_image_t *img);
void		draw_ceiling_and_floor(t_game *g, int x);
void		close_hook(t_game *game);

//HANDLE TEXTURES
int			handle_north_texture(char *trim, t_parser *parser);
int			handle_south_texture(char *trim, t_parser *parser);
int			handle_east_texture(char *trim, t_parser *parser);
int			handle_west_texture(char *trim, t_parser *parser);
//COLORS
int			handle_floor_color(char *trim, t_parser *parser);
int			handle_ceiling_color(char *trim, t_parser *parser);

#endif
