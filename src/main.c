/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:11 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/07 17:34:54 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

	int		world[GRID_ROWS][GRID_COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, {1,0,0,1,0,1,1,1,0,0,1,0,1,0,0,1},
    {1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1}, {1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1},
    {1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1}, {1,0,0,0,0,1,0,1,0,0,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void clear_image(mlx_image_t *img)
{
	uint32_t x;
	uint32_t y;

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

void	handle_rotation(t_game *g, double r_spd, int dir)
{
    double oldDirX;
	double oldPlaneX;

	oldDirX = g->player.dirX;
    g->player.dirX = g->player.dirX * cos(dir * r_spd) - g->player.dirY * sin(dir * r_spd);
    g->player.dirY = oldDirX * sin(dir * r_spd) + g->player.dirY * cos(dir * r_spd);

	oldPlaneX = g->player.planeX;
    g->player.planeX = g->player.planeX * cos(dir * r_spd) - g->player.planeY * sin(dir * r_spd);
    g->player.planeY = oldPlaneX * sin(dir * r_spd) + g->player.planeY * cos(dir * r_spd);
}

void	handle_movement(t_game *g, double move_speed, int direction)
{
    double newX;
	double newY;
	
	newX = g->player.px + g->player.dirX * move_speed * direction;
	newY = g->player.py + g->player.dirY * move_speed * direction;
    if (world[(int)newY][(int)newX] == 0)
	{
        g->player.px = newX;
        g->player.py = newY;
    }
}

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
		if(world[g->player.mapY][g->player.mapX] > 0)
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
	int	l_height;
	int	d_start;
	int	d_end;
	int	color;

	d_end = l_height / 2 + HEIGHT / 2;
	g->player.pWallDist = g->player.side ? (g->player.sDistY - g->player.dDistY) : (g->player.sDistX - g->player.dDistX);
	l_height = (int)(HEIGHT / g->player.pWallDist);
	d_start = -l_height / 2 + HEIGHT / 2;
	d_start = d_start < 0 ? 0 : d_start;
	d_end = d_end >= HEIGHT ? HEIGHT - 1 : d_end;
	switch (world[g->player.mapY][g->player.mapX])
	{
		case 1: color = COLOR_W; break;
		default: color = COLOR_S; break;
	}
	if (g->player.side == 1)
		color = (color >> 1) & 0x7F7F7F7F;
	g->y = d_start - 1;
	while (g->y++ < d_end)
		mlx_put_pixel(g->img, x, g->y, color);
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		handle_movement(game, f_time * 5.0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		handle_movement(game, f_time * 5.0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		handle_movement(game, f_time * 5.0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		handle_movement(game, f_time * 5.0, 1);
	draw_square(game->player.px, game->player.py, 10, 0x00FF00FF, game->img);
}

int run_game(t_game *game)
{
    game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
    if (!game->mlx)
		errno_error_mlx();
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img)
		errno_error_mlx();
	game->player.py = HEIGHT / 2;
	game->player.px = WIDTH / 2;
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, ft_hook, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
    return (EXIT_SUCCESS);
}

int main()
{
    t_game game;

//    if (map_build(ac, av, &game.parser)) 
//        return (free_allocations(),1);
    run_game(&game);
    return (free_allocations(),0);
}
