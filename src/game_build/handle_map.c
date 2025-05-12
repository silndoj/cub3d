/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:23:58 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/06 16:31:47 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_map_dimensions(t_parser *parser, int *width, int *height)
{
	int		i;
	int		len;

	*width = 0;
	*height = 0;
	i = parser->start_line_map;
	while (parser->map2d[i])
	{
		if (map_line(parser->map2d[i]))
		{
			(*height)++;
			len = ft_strlen(parser->map2d[i]);
			if (len > (*width))
				(*width) = len;
		}
		else if (!ft_is_empty_line(parser->map2d[i]))
		{
			break ;
		}
		else if ((*height) > 0)
			(*height)++;
		i++;
	}
}

void	convert_map_to_int(t_parser *parser)
{
	int		map_width;
	int		map_height;

	get_map_dimensions(parser, &map_width, &map_height);
	parser->map_height = map_height;
	parser->map_width = map_width;
	if (map_height == 0 || map_width == 0)
		exit_error("Invalid map dimensions", parser);
}

void	init_wall_array(int ***wall, t_parser *parser)
{
	int	i;

	(*wall) = malloc(sizeof(int *) * parser->map_height);
	if (!(*wall))
		exit_error("failed allocation for check_walls()->H", parser);
	i = 0;
	while (i < parser->map_height)
	{
		(*wall)[i] = NULL;
		i++;
	}
	i = 0;
	while (i < parser->map_height)
	{
		(*wall)[i] = ft_calloc(parser->map_width, sizeof(int));
		if (!(*wall)[i])
		{
			exit_error("failed allocation in check_wall()->W", parser);
		}
		i++;
	}
}

void	check_walkable_map(t_parser *parser, int **wall)
{
	int	y;
	int	x;

	y = 0;
	while (y < parser->map_height)
	{
		x = 0;
		while (x < parser->map_width)
		{
			if (parser->map1[y][x] == 0)
			{
				flood_fill(parser, wall, y, x);
				if (parser->invalid_map)
				{
					exit_error("Map is not enclosed by walls", parser);
				}
				y = parser->map_height;
				break ;
			}
			x++;
		}
		y++;
	}
}

void	check_walls(t_parser *parser)
{
	int	**wall;

	parser->invalid_map = false;
	init_wall_array(&wall, parser);
	if (parser->player_found)
	{
		flood_fill(parser, wall, parser->player_pos_y, parser->player_pos_x);
		if (parser->invalid_map)
		{
			free_int_array(wall, parser->map_height);
			exit_error("Map is not completely enclosed by walls", parser);
		}
	}
	else
		check_walkable_map(parser, wall);
	parser->wall_arr = wall;
}
