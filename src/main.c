/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:11 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/03 22:08:30 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

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
	t_game *game;
	game = param;
	clear_image(game->img);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->player.py -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->player.py += 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.px -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.px += 5;
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
