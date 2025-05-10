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

static void	check_assign_map_elements(t_parser *parser, int x, int y, int len)
{
	char	c;

	if (x < len)
		c = parser->map2d[parser->start_line_map][x];
	else
		c = ' ';
	if (c == '1')
		parser->map1[y][x] = 1;
	else if (c == '0')
		parser->map1[y][x] = 0;
	else if (c == ' ' || c == '\t')
		parser->map1[y][x] = -1;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (parser->player_found)
			exit_error("Multiple players found");
		parser->map1[y][x] = 0;
		parser->player_found = true;
		parser->player_pos_x = x;
		parser->player_pos_y = y;
		parser->player_dir = c;
	}
	else if (c != '\n' && c != '\0')
		exit_error("Invalid character in map");
}

static	int	put_map_elements(t_parser *parser)
{
	int	start_line;
	int	x;
	int	y;
	int	len;

	start_line = parser->start_line_map;
	y = -1;
	parser->player_found = false;
	while (++y < parser->map_height && parser->map2d[parser->start_line_map])
	{
		len = ft_strlen(parser->map2d[parser->start_line_map]);
		x = -1;
		while (++x < parser->map_width)
			check_assign_map_elements(parser, x, y, len);
		parser->start_line_map++;
	}
	parser->y2 = y;
	parser->x = x;
	if (!parser->player_found)
		exit_error("Missing player position");
	parser->start_line_map = start_line;
	return (0);
}

static void	get_map_dimensions(t_parser *parser, int *width, int *height)
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

static void	convert_map_to_int(t_parser *parser)
{
	int		map_width;
	int		map_height;

	get_map_dimensions(parser, &map_width, &map_height);
	parser->map_height = map_height;
	parser->map_width = map_width;
	if (map_height == 0 || map_width == 0)
		exit_error("Invalid map dimensions");
}

static void	init_wall_array(int ***wall, t_parser *parser)
{
	int	i;

	(*wall) = ft_malloc(sizeof(int *) * parser->map_height);
	if (!(*wall))
		exit_error("failed allocation for check_walls()->H");
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
			exit_error("failed allocation in check_wall()->W");
		}
		i++;
	}
}

static	void check_walkable_map(t_parser *parser, int **wall)
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
				exit_error("Map is not completely enclosed by walls");
			}
			y = parser->map_height;
			break;
		}
				x++;
			}
			y++;
		}
}

static	void check_walls(t_parser *parser)
{
	int **wall;

	parser->invalid_map = false;
	init_wall_array(&wall, parser);
	if (parser->player_found)
	{
		flood_fill(parser, wall, parser->player_pos_y, parser->player_pos_x);
		if (parser->invalid_map)
		{
			exit_error("Map is not completely enclosed by walls");
		}
	}
	else
	{
		int y = 0;
		while (y < parser->map_height)
		{
			int x = 0;
			while (x < parser->map_width)
			{
				if (parser->map1[y][x] == 0)
				{
					flood_fill(parser, wall, y, x);
					if (parser->invalid_map)
					{
						exit_error("Map is not completely enclosed by walls");
					}
					y = parser->map_height;
					break;
				}
				x++;
			}
			y++;
		}
	}
}

int	parse_map(t_parser *parser)
{
	char	*trim;
	int		i;

	i = -1;
	while (parser->map2d[++i] && !parser->all_elements)
	{
		trim = ft_strtrim(parser->map2d[i], " \t\r\n");
		if (trim && *trim)
			check_all_elements_file(trim, parser);
		free(trim);
	}
	check_all(parser);
	find_start_of_map(parser, i + 1);
	convert_map_to_int(parser);
	create_int_array(parser);
	put_map_elements(parser);
	check_walls(parser);
	extra_char(parser);
	for (i = 0; i < parser->map_height && i < GRID_ROWS; i++)
	{
		for (int j = 0; j < parser->map_width && j < GRID_COLS; j++)
		{
			parser->map[i][j] = parser->map1[i][j];
		}
	}
	return (0);
}