/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:16:23 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/08 21:52:33 by tndreka          ###   ########.fr       */
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
# define HEIGHT 1024

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_parser
{
	char	**map2d;
	int		**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		start_line_map;
	int		map_width;
	int		map_height;
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
}	t_parser;

typedef struct s_game
{
	mlx_t		*mlx;
	t_parser	parser;
}	t_game;

//MAP_BUILD.C
int			map_build(int argc, char **argv, t_parser *parser);
int			check_map(char *file, t_parser *parser);
void		copy_map(int fd, t_parser *parser);
void		print_map(t_parser *parser);
int			parse_map(t_parser *parser);
void		init_map(t_parser *parser);

//HANDLE TEXTURES
int			handle_north_texture(char *trim, t_parser *parser);
int			handle_south_texture(char *trim, t_parser *parser);
int			handle_east_texture(char *trim, t_parser *parser);
int			handle_west_texture(char *trim, t_parser *parser);
//COLORS
int			handle_floor_color(char *trim, t_parser *parser);
int			handle_ceiling_color(char *trim, t_parser *parser);
//Util Box
int			errno_exit(void);
int			exit_error(const char *msg);
#endif