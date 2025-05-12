/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 05:37:45 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/12 23:04:06 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	find_start_of_map(t_parser *parser, int start_i)
{
	int		i;

	i = start_i - 1;
	while (parser->map2d[++i])
	{
		if (!parser->map2d[i] || !*parser->map2d[i]
			|| ft_is_empty_line(parser->map2d[i]))
			continue ;
		if (map_line(parser->map2d[i]))
		{
			parser->start_line_map = i;
			return (0);
		}
		else
		{
			continue ;
		}
	}
	exit_error("Could not find start of map", parser);
	return (1);
}

int	check_all_elements_file(char *trim, t_parser *parser)
{
	if (!ft_strncmp(trim, "NO", 2) && (trim[2] == ' ' || trim[2] == '\t'))
		handle_north_texture(trim, parser);
	else if (!ft_strncmp(trim, "SO", 2) && (trim[2] == ' ' || trim[2] == '\t'))
		handle_south_texture(trim, parser);
	else if (!ft_strncmp(trim, "EA", 2) && (trim[2] == ' ' || trim[2] == '\t'))
		handle_east_texture(trim, parser);
	else if (!ft_strncmp(trim, "WE", 2) && (trim[2] == ' ' || trim[2] == '\t'))
		handle_west_texture(trim, parser);
	else if (!ft_strncmp(trim, "F", 1) && (trim[1] == ' ' || trim[1] == '\t'))
		handle_floor_color(trim, parser);
	else if (!ft_strncmp(trim, "C", 1) && (trim[1] == ' ' || trim[1] == '\t'))
		handle_ceiling_color(trim, parser);
	if (parser->no_found && parser->so_found && parser->ea_found
		&& parser->we_found && parser->f_found && parser->c_found)
		parser->all_elements = true;
	return (0);
}

int	create_int_array(t_parser *parser)
{
	int		i;
	int		j;

	parser->map1 = ft_malloc(sizeof(int *) * parser->map_height);
	if (!parser->map1)
		exit_error("Failed to allocate memory for rows", parser);
	i = 0;
	while (i < parser->map_height)
	{
		parser->map1[i] = ft_malloc(sizeof(int) * parser->map_width);
		if (!parser->map1[i])
			exit_error("Failed to allocate memory for columns", parser);
		j = 0;
		while (j < parser->map_width)
		{
			parser->map1[i][j] = -1;
			j++;
		}
		i++;
	}
	return (0);
}

int	flood_fill(t_parser *parser, int **wall, int y, int x)
{
	if (y < 0 || y >= parser->map_height || x < 0 || x >= parser->map_width)
		return (0);
	if (wall[y][x] == 1 || parser->map1[y][x] == 1)
		return (0);
	wall[y][x] = 1;
	if (y == 0 || y == parser->map_height - 1
		|| x == 0 || x == parser->map_width - 1)
	{
		parser->invalid_map = true;
		exit_error("Map is not properly enclosed by walls", parser);
	}
	flood_fill(parser, wall, y + 1, x);
	flood_fill(parser, wall, y - 1, x);
	flood_fill(parser, wall, y, x + 1);
	flood_fill(parser, wall, y, x - 1);
	return (0);
}
