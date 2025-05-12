/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 00:23:03 by silndoj           #+#    #+#             */
/*   Updated: 2025/05/12 23:24:43 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clear_image(mlx_image_t *img)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	x = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

uint32_t	make_mlx_color(int r, int g, int b)
{
	return ((b << 16) | (g << 8) | r);
}

void	draw_ceiling_and_floor(t_game *g, int x)
{
	uint32_t	f_color;
	uint32_t	c_color;
	int			y;

	f_color = make_mlx_color(
			g->parser.floor_r,
			g->parser.floor_g,
			g->parser.floor_b
			);
	c_color = make_mlx_color(
			g->parser.ceil_r,
			g->parser.ceil_g,
			g->parser.ceil_b
			);
	y = 0;
	while (y < g->parser.d_s)
		mlx_put_pixel(g->img, x, y++, c_color);
	y = g->parser.d_e;
	while (y < HEIGHT)
		mlx_put_pixel(g->img, x, y++, f_color);
}

void	calculate_texture_position(t_game *g, int tex_index)
{
	double	w_x;

	if (g->player.side)
		w_x = g->player.px + g->player.pw_dist * g->player.rdir_x;
	else
		w_x = g->player.py + g->player.pw_dist * g->player.rdir_y;
	w_x -= floor(w_x);
	g->parser.t_x = (int)(w_x * (double)g->textures[tex_index]->width);
	if ((g->player.side == 0 && g->player.rdir_x < 0)
		|| (g->player.side == 1 && g->player.rdir_y > 0))
		g->parser.t_x = g->textures[tex_index]->width - g->parser.t_x - 1;
}

void	draw_texture_wall(t_game *g, int tex_index, int x)
{
	double		st;
	double		t_p;
	uint32_t	t_c;

	st = (double)g->textures[tex_index]->height / g->parser.l_h;
	t_p = (g->parser.d_s - HEIGHT / 2 + g->parser.l_h / 2) * st;
	g->parser.y1 = g->parser.d_s;
	while (g->parser.y1 < g->parser.d_e)
	{
		g->parser.t_y = (int)t_p & (g->textures[tex_index]->height - 1);
		t_c = ((uint32_t *) g->textures[tex_index]->pixels)
		[g->parser.t_y * g->textures[tex_index]->width + g->parser.t_x];
		if (g->player.side)
			t_c = (t_c >> 1) & 0x7F7F7F7F;
		mlx_put_pixel(g->img, x, g->parser.y1++, t_c);
		t_p += st;
	}
}
