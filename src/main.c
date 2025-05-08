/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:11 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/08 22:39:03 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "inc/libft/includes/garbage_collector.h"

void	clear_image(mlx_image_t *img)
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
    if (g->parser.map[(int)newY][(int)newX] == 0)
	{
        g->player.px = newX;
        g->player.py = newY;
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
		handle_movement(game, f_time * 5.0, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		handle_rotation(game, f_time * 3.0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		handle_rotation(game, f_time * 3.0, -1);
	cast_ray(game);
}

int run_game(t_game *game)
{
    game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
    if (!game->mlx || !(game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT)))
		errno_error_mlx();
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	int	static_map[GRID_ROWS][GRID_COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, {1,0,0,1,0,1,1,1,0,0,1,0,1,0,0,1},
    {1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1}, {1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1},
    {1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1}, {1,0,0,0,0,1,0,1,0,0,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	memcpy(game->parser.map, static_map, sizeof(static_map));
    game->parser.width = GRID_COLS;
    game->parser.height = GRID_ROWS;
	game->player.py = 6.0;
	game->player.px = 3.0;
	game->player.dirX = -1;
	game->player.dirY = 0;
	game->player.planeX = 0;
	game->player.planeY = 0.66;
	game->textures[0] = mlx_load_png("textures/wood.png");
	game->textures[1] = mlx_load_png("textures/wall_1.png");
	game->textures[2] = mlx_load_png("textures/wall_2.png");
	game->textures[3] = mlx_load_png("textures/wall_3.png");
	if (!game->textures[0] || !game->textures[1] || !game->textures[2] || !game->textures[3])
        errno_error_mlx();
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
