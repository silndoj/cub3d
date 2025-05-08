/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:56:10 by silndoj           #+#    #+#             */
/*   Updated: 2025/05/08 22:38:06 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	dda_loop(t_game* g)
{
	while (!g->player.hit)
	{
		if (g->player.sDistX < g->player.sDistY)
		{
			g->player.sDistX +=	g->player.dDistX;
			g->player.mapX += g->player.stepX;
			g->player.side = 0;
		}
		else
		{
			g->player.sDistY += g->player.dDistY;
			g->player.mapY += g->player.stepY;
			g->player.side = 1;
		}
		if(g->parser.map[g->player.mapY][g->player.mapX] > 0)
			g->player.hit = 1;
	}
}

void	dda_algo(t_game* g)
{
	if (g->player.rDirX < 0)
	{
		g->player.stepX = -1;
		g->player.sDistX = (g->player.px - g->player.mapX) * g->player.dDistX;
	}
	else
	{
		g->player.stepX = 1;
		g->player.sDistX = (g->player.mapX + 1.0 - g->player.px) * g->player.dDistX;
	}
	if (g->player.rDirY < 0)
	{
		g->player.stepY = -1;
		g->player.sDistY = (g->player.py - g->player.mapY) * g->player.dDistY;
	}
	else
	{
		g->player.stepY = 1;
		g->player.sDistY = (g->player.mapY + 1.0 - g->player.py) * g->player.dDistY;
	}
	dda_loop(g);
}

void draw_walls(t_game* g, int x)
{
    int l_h, d_s, d_e, y, t_x, t_y;
    double w_x, st, t_p;
    uint32_t t_c;
    int tex_index; // Add texture index variable

    g->player.pWallDist = g->player.side ? 
        (g->player.sDistY - g->player.dDistY) : 
        (g->player.sDistX - g->player.dDistX);
    l_h = HEIGHT / g->player.pWallDist;
    d_s = fmax(-l_h/2 + HEIGHT/2, 0);
    d_e = fmin(l_h/2 + HEIGHT/2, HEIGHT-1);

    // Determine texture index based on wall side and direction
    if (g->player.side == 0)
    {
        if (g->player.rDirX > 0)
            tex_index = 0; // East wall
        else
            tex_index = 1; // West wall
    }
    else
    {
        if (g->player.rDirY > 0)
            tex_index = 2; // South wall
        else
            tex_index = 3; // North wall
    }

    if (g->textures[tex_index])
    {
        w_x = g->player.side ? 
            g->player.px + g->player.pWallDist * g->player.rDirX :
            g->player.py + g->player.pWallDist * g->player.rDirY;
        w_x -= floor(w_x);
        t_x = (int)(w_x * (double)g->textures[tex_index]->width);
        // Adjust texture direction if necessary
        if ((g->player.side == 0 && g->player.rDirX < 0) || 
            (g->player.side == 1 && g->player.rDirY > 0))
            t_x = g->textures[tex_index]->width - t_x - 1;

        st = (double)g->textures[tex_index]->height / l_h;
        t_p = (d_s - HEIGHT/2 + l_h/2) * st;
        y = d_s;
        while (y < d_e)
        {
            t_y = (int)t_p & (g->textures[tex_index]->height - 1);
            t_c = ((uint32_t*)g->textures[tex_index]->pixels)
                 [t_y * g->textures[tex_index]->width + t_x];
            if (g->player.side) t_c = (t_c >> 1) & 0x7F7F7F7F; // Darken for y-sides
            mlx_put_pixel(g->img, x, y++, t_c);
            t_p += st;
        }
    }
    else
    {
        // Fallback colors if texture isn't loaded
        int c = g->parser.map[g->player.mapY][g->player.mapX] == 1 ? 
            (g->parser.floor_r << 16 | g->parser.floor_g << 8 | g->parser.floor_b) : 
            (g->parser.ceil_r << 16 | g->parser.ceil_g << 8 | g->parser.ceil_b);
        y = d_s;
        while (y < d_e)
            mlx_put_pixel(g->img, x, y++, g->player.side ? (c >> 1) & 0x7F7F7F7F : c);
    }
}

void	cast_ray(t_game *g)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		g->player.cameraX = 2 * x / (double)WIDTH - 1;
		g->player.rDirX = g->player.dirX + g->player.planeX * g->player.cameraX;
		g->player.rDirY = g->player.dirY + g->player.planeY * g->player.cameraX;
		g->player.mapX = (int)g->player.px;
		g->player.mapY = (int)g->player.py;
		g->player.dDistX = fabs(1 / g->player.rDirX);
		g->player.dDistY = fabs(1 / g->player.rDirY);
		g->player.hit = 0;
		dda_algo(g);
		draw_walls(g, x);
		x++;
	}
}

