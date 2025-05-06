/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:11 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/06 18:29:33 by silndoj          ###   ########.fr       */
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

void	handle_rotation(t_game *g, double rot_speed, int direction)
{
    double oldDirX;
	oldDirX = g->player.dirX;
    g->player.dirX = g->player.dirX * cos(direction * rot_speed) - g->player.dirY * sin(direction * rot_speed);
    g->player.dirY = oldDirX * sin(direction * rot_speed) + g->player.dirY * cos(direction * rot_speed);

    double oldPlaneX;
	oldPlaneX = g->player.planeX;
    g->player.planeX = g->player.planeX * cos(direction * rot_speed) - g->player.planeY * sin(direction * rot_speed);
    g->player.planeY = oldPlaneX * sin(direction * rot_speed) + g->player.planeY * cos(direction * rot_speed);
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

void	draw_square(int x, int y, int size, int color, mlx_image_t *img)
{
	int	i;

	i = 0;
	while (i++ < size)
		mlx_put_pixel(img, x + i, y, color);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(img, x, y + i, color);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(img, x + size, y + i-1, color);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(img, x+ i - 1, y + size, color);
}

void	ft_hook(void *param)
{
	static double	o_time;
	t_game			*game;
	double			c_time;
	double			f_time;

	o_time = 0;
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
