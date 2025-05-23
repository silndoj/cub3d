/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:56:10 by silndoj           #+#    #+#             */
/*   Updated: 2025/05/11 23:28:29 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	dda_loop(t_game *g)
{
	while (!g->player.hit)
	{
		if (g->player.sdist_x < g->player.sdist_y)
		{
			g->player.sdist_x += g->player.ddist_x;
			g->player.map_x += g->player.step_x;
			g->player.side = 0;
		}
		else
		{
			g->player.sdist_y += g->player.ddist_y;
			g->player.map_y += g->player.step_y;
			g->player.side = 1;
		}
		if (g->parser.map[g->player.map_y][g->player.map_x] > 0)
			g->player.hit = 1;
	}
}

void	dda_algo(t_game *g)
{
	double	*temp;

	temp = &g->player.sdist_x;
	if (g->player.rdir_x < 0)
	{
		g->player.step_x = -1;
		*temp = (g->player.px - g->player.map_x) * g->player.ddist_x;
	}
	else
	{
		g->player.step_x = 1;
		*temp = (g->player.map_x + 1.0 - g->player.px) * g->player.ddist_x;
	}
	temp = &g->player.sdist_y;
	if (g->player.rdir_y < 0)
	{
		g->player.step_y = -1;
		*temp = (g->player.py - g->player.map_y) * g->player.ddist_y;
	}
	else
	{
		g->player.step_y = 1;
		*temp = (g->player.map_y + 1.0 - g->player.py) * g->player.ddist_y;
	}
	dda_loop(g);
}

void	put_textures(t_game *g, int tex_index, int x)
{
	uint32_t	t_c;

	g->start = g->parser.d_s;
	g->end = g->parser.d_e;
	draw_ceiling_and_floor(g, x);
	if (g->textures[tex_index])
	{
		calculate_texture_position(g, tex_index);
		draw_texture_wall(g, tex_index, x);
	}
	else
	{
		t_c = 0xFFAAAAAA;
		g->y = g->start;
		while (g->y < g->end)
			mlx_put_pixel(g->img, x, g->y++, t_c);
	}
}

void	draw_walls(t_game *g, int x)
{
	int	tex_index;

	if (g->player.side)
		g->player.pw_dist = g->player.sdist_y - g->player.ddist_y;
	else
		g->player.pw_dist = g->player.sdist_x - g->player.ddist_x;
	g->parser.l_h = HEIGHT / g->player.pw_dist;
	g->parser.d_s = fmax(-g->parser.l_h / 2 + HEIGHT / 2, 0);
	g->parser.d_e = fmin(g->parser.l_h / 2 + HEIGHT / 2, HEIGHT - 1);
	if (g->player.side == 0)
	{
		if (g->player.rdir_x > 0)
			tex_index = 0;
		else
			tex_index = 1;
	}
	else
	{
		if (g->player.rdir_y > 0)
			tex_index = 2;
		else
			tex_index = 3;
	}
	put_textures(g, tex_index, x);
}

void	cast_ray(t_game *g)
{
	int		x;
	double	*t1;
	double	*t2;

	x = 0;
	t1 = &g->player.rdir_x;
	t2 = &g->player.rdir_y;
	while (x < WIDTH)
	{
		g->player.camera_x = 2 * x / (double)WIDTH - 1;
		*t1 = g->player.dir_x + g->player.plane_x * g->player.camera_x;
		*t2 = g->player.dir_y + g->player.plane_y * g->player.camera_x;
		g->player.map_x = (int)g->player.px;
		g->player.map_y = (int)g->player.py;
		g->player.ddist_x = fabs(1 / g->player.rdir_x);
		g->player.ddist_y = fabs(1 / g->player.rdir_y);
		g->player.hit = 0;
		dda_algo(g);
		draw_walls(g, x);
		x++;
	}
}
