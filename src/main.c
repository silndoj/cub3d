/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:11 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/09 01:46:44 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "inc/libft/includes/garbage_collector.h"

int	run_game(t_game *game)
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
	game->parser.floor_r = 255;
	game->parser.floor_g = 0;
	game->parser.floor_b = 255;
	game->parser.ceil_r = 100;   // Example: Light blue ceiling
	game->parser.ceil_g = 235;
	game->parser.ceil_b = 0;
	game->parser.width = GRID_COLS;
	game->parser.height = GRID_ROWS;
	game->player.py = 6.0;
	game->player.px = 3.0;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
	game->textures[0] = mlx_load_png("textures/wood.png");
	game->textures[1] = mlx_load_png("textures/wall_1.png");
	game->textures[2] = mlx_load_png("textures/wall_2.png");
	game->textures[3] = mlx_load_png("textures/wall_3.png");
	if (!game->textures[0] || !game->textures[1] 
		|| !game->textures[2] || !game->textures[3])
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
