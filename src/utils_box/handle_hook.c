/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 00:19:38 by silndoj           #+#    #+#             */
/*   Updated: 2025/05/09 04:30:02 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	handle_rotation(t_game *g, double r_spd, int dir)
{
	double	odir_x;
	double	oplane_x;
	double	cos_t;
	double	sin_t;
	double	angle;

	angle = dir * r_spd;
	cos_t = cos(angle);
	sin_t = sin(angle);
	odir_x = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * cos_t - g->player.dir_y * sin_t;
	g->player.dir_y = odir_x * sin_t + g->player.dir_y * cos_t;
	oplane_x = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * cos_t - g->player.plane_y * sin_t;
	g->player.plane_y = oplane_x * sin_t + g->player.plane_y * cos_t;
}

void	handle_movement(t_game *g, double move_speed, int direction)
{
	double	new_x;
	double	new_y;

	new_x = g->player.px + g->player.dir_x * move_speed * direction;
	new_y = g->player.py + g->player.dir_y * move_speed * direction;
	if (g->parser.map[(int)new_y][(int)new_x] == 0)
	{
		g->player.px = new_x;
		g->player.py = new_y;
	}
}

void	handle_strafe(t_game *g, double move_speed, int direction)
{
	double	new_x;
	double	new_y;

	new_x = g->player.px + g->player.plane_x * move_speed * direction;
	new_y = g->player.py + g->player.plane_y * move_speed * direction;
	if (g->parser.map[(int)new_y][(int)new_x] == 0)
	{
		g->player.px = new_x;
		g->player.py = new_y;
	}
}

void	ft_hook(void *param)
{
	static double	o_time = 0;
	t_game			*game;
	double			c_time;
	double			f_time;

	game = param;
	c_time = mlx_get_time();
	f_time = c_time - o_time;
	o_time = c_time;
	clear_image(game->img);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		return (close_hook(game));
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		handle_movement(game, f_time * 5.0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		handle_strafe(game, f_time * 5.0, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		handle_movement(game, f_time * 5.0, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		handle_strafe(game, f_time * 5.0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		handle_rotation(game, f_time * 3.0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		handle_rotation(game, f_time * 3.0, -1);
	cast_ray(game);
}
