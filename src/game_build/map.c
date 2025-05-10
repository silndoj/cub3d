/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 07:40:39 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/11 00:51:52 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	put_map_elements(t_parser *parser)
{
	int	start_line;
	int	x;
	int	y;
	int	len;

	x = 0;
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

void	check_assign_map_elements(t_parser *parser, int x, int y, int len)
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

void	pass_data_to_final_map(t_parser *parser)
{
	int		i;
	int		j;

	i = 0;
	while (i < parser->map_height && i < GRID_ROWS)
	{
		j = 0;
		while (j < parser->map_width && j < GRID_COLS)
		{
			parser->map[i][j] = parser->map1[i][j];
			j++;
		}
		i++;
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
	pass_data_to_final_map(parser);
	return (0);
}
