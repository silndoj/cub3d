/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:11 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/12 23:04:16 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "inc/libft/includes/garbage_collector.h"

void	set_color_position(t_game *game)
{
	game->parser.floor_r = game->parser.floor.r;
	game->parser.floor_g = game->parser.floor.g;
	game->parser.floor_b = game->parser.floor.b;
	game->parser.ceil_r = game->parser.ceiling.r;
	game->parser.ceil_g = game->parser.ceiling.g;
	game->parser.ceil_b = game->parser.ceiling.b;
	game->player.px = game->parser.player_pos_x + 0.5;
	game->player.py = game->parser.player_pos_y + 0.5;
}

int	run_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!game->mlx)
		return (errno_error_mlx(), EXIT_FAILURE);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->mlx || !game->img)
		return (errno_error_mlx(), EXIT_FAILURE);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	set_color_position(game);
	set_player_direction(game);
	game->textures[0] = mlx_load_png(game->parser.no_texture);
	game->textures[1] = mlx_load_png(game->parser.so_texture);
	game->textures[2] = mlx_load_png(game->parser.ea_texture);
	game->textures[3] = mlx_load_png(game->parser.we_texture);
	if (!game->textures[0] || !game->textures[1]
		||!game->textures[2] || !game->textures[3])
		errno_error_mlx();
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_game	game;

	if (map_build(ac, av, &game.parser))
	{
		return (free_parser(&game.parser), 1);
	}
	run_game(&game);
	free_parser(&game.parser);
	return (0);
}
