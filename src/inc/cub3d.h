/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:21 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/03 21:00:37 by silndoj          ###   ########.fr       */
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
#define HEIGHT 768


typedef struct s_parser
{
    char	**map2d;
}   t_parser;

typedef struct s_player
{
	float	px;
	float	py;
}	t_player;

typedef struct s_game
{
	void*		mlx;
	void*		win;
	void*		img;
	t_player	player;
	t_parser	parser;
}   t_game;

//***game_build/MAP_BUILD.C
int		map_build(int argc, char **argv, t_parser *parser);
int		check_map(char *file, t_parser *parser);
void    copy_map(int fd, t_parser *parser);
void	print_map(t_parser *parser);

//***utils_box/ERROR.C
void	errno_exit(void);
void	errno_error_mlx(void);

#endif
