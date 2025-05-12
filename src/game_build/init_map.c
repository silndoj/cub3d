/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:05:47 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/12 23:01:34 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_parser *parser)
{
	parser->map2d = NULL;
	parser->no_texture = NULL;
	parser->so_texture = NULL;
	parser->we_texture = NULL;
	parser->ea_texture = NULL;
	parser->map_found = false;
	parser->start_line_map = 0;
	parser->all_elements = false;
	parser->no_found = false;
	parser->so_found = false;
	parser->we_found = false;
	parser->ea_found = false;
	parser->f_found = false;
	parser->c_found = false;
	parser->ceiling_set = false;
	parser->floor_set = false;
	parser->player_found = false;
}

void	free_parser(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser->map2d[i])
	{
		free(parser->map2d[i]);
		i++;
	}
	free(parser->map2d);
	if (parser->wall_arr)
		free_int_array(parser->wall_arr, parser->map_height);
	free(parser->no_texture);
	free(parser->so_texture);
	free(parser->ea_texture);
	free(parser->we_texture);
	free_allocations();
}

void	set_north_south(t_game *game)
{
	if (game->parser.player_dir == 'N')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (game->parser.player_dir == 'S')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	set_east_west(t_game *game)
{
	if (game->parser.player_dir == 'E')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->parser.player_dir == 'W')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

void	set_player_direction(t_game *game)
{
	set_north_south(game);
	set_east_west(game);
}
