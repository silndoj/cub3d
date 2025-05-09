/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 00:23:03 by silndoj           #+#    #+#             */
/*   Updated: 2025/05/09 02:21:05 by silndoj          ###   ########.fr       */
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
