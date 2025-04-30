/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:11 by tndreka           #+#    #+#             */
/*   Updated: 2025/04/30 17:32:48 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

#define BPP sizeof(int32_t)



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
		mlx_put_pixel(img, x + size, y, color);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(img, x, y + size, color);
}


int run_game(t_game *game)
{
    game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
    if (!game->mlx)
		errno_error_mlx();
    mlx_image_t *img = mlx_new_image(game->mlx, HEIGHT, WIDTH);
    if (!img || (mlx_image_to_window(game->mlx, img, 0, 0) < 0))
		errno_error_mlx();
	draw_square(HEIGHT / 2, WIDTH / 2, 100, 0x00FF00, img);
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
