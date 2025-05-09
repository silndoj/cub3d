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

static int ft_is_emty_line(char *line)
{
	while (*line)
	{
		if(!ft_isspace((int)*line))
			return (0);
		line++;
	}
	
	return (1);
}

static	int	map_line(char *trim)
{
	int has_valid_char;

	has_valid_char = 0;
	while (*trim)
	{
		if (!ft_strchr(" 01NSWE", *trim))
			return (0);
		if (ft_strchr("01NSWE", *trim))
			has_valid_char = 1;
		trim++;
	}
	return (1);
}

static	int	find_start_of_map(t_parser *parser, int start_i)
{
	int		i;

	i = start_i - 1;
	while (parser->map2d[++i])
	{
		if (!parser->map2d[i] || !*parser->map2d[i])
			ft_is_emty_line(parser->map2d[i]);
			continue;
		if (map_line(parser->map2d[i]))
		{
			parser->start_line_map = i;
			return (0);
		}
		else
		 	continue;
	}
	exit_error("Could not find start of map");
	return (1);
}

static	int	check_all_elements_file(char *trim, t_parser *parser)
{
	if (!ft_strncmp(trim, "NO ", 3) && (trim[2] != ' ' || trim[2] == '\t'))
		handle_north_texture(trim, parser);
	else if (!ft_strncmp(trim, "SO ", 3) && (trim[2] != ' ' || trim[2] == '\t'))
		handle_south_texture(trim, parser);
	else if (!ft_strncmp(trim, "EA ", 3) && (trim[2] != ' ' || trim[2] == '\t'))
		handle_east_texture(trim, parser);
	else if (!ft_strncmp(trim, "WE ", 3) && (trim[2] != ' ' || trim[2] == '\t'))
		handle_west_texture(trim, parser);
	else if (!ft_strncmp(trim, "F ", 2) && (trim[2] != ' ' || trim[2] == '\t'))
		handle_floor_color(trim, parser);
	else if (!ft_strncmp(trim, "C ", 2) && (trim[2] != ' ' || trim[2] == '\t'))
		handle_ceiling_color(trim, parser);
	if (parser->no_found && parser->so_found && parser->ea_found
		&& parser->we_found && parser->f_found && parser->c_found)
		parser->all_elements = true;
	return (0);
}

static	int	create_int_array(t_parser *parser)
{
	int		i;
	int		j;


	parser->map1 = ft_malloc(sizeof(int *) * parser->map_height);
	if (!parser->map1)
		exit_error("Failed to alocate memory for rows");
	i = 0;
	while (i < parser->map_height)
	{
		parser->map1[i] = ft_malloc(sizeof(int) * parser->map_width);
		if (!parser->map1[i])
			exit_error("Failed to alocate memory for col");
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

static	int fill_map(t_parser *parser)
{
	int start_line;
	int x;
	int len;
	int y;
	char c;

	start_line = parser->start_line_map;
	y = 0;
	x = 0;
	parser->player_found = false;
	while (y < parser->map_height && parser->map2d[parser->start_line_map])
	{
		len = ft_strlen(parser->map2d[parser->start_line_map]);
		x = 0;
		while (x < parser->map_width)
		{
			if (x < len)
			{
				c = parser->map2d[parser->start_line_map][x];
			}
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
					exit_error("Miltiple players found");
				parser->map1[y][x] = 0;
				parser->player_found = true;
				parser->player_pos_x = x;
				parser->player_pos_y = y;
				parser->player_direction = c;	
			}
			else if (c != '\n' && c != '\0')
				exit_error("invalid characters");
			x++;
		}
		y++;
		parser->start_line_map++;		
	}
	parser->y2 = y;
	parser->x = x;
	if (!parser->player_found)
		exit_error("Missing player position");
	parser->start_line_map = start_line;
	return (0);
}

static	void convert_map_to_int(t_parser *parser)
{
	int		i;
	int		map_width;
	int		map_height;
	int		len;

	i = parser->start_line_map;
	map_width = 0;
	map_height = 0;
	len = 0;

	while (parser->map2d[i])
	{

		if (map_line(parser->map2d[i]))
		{
			map_height++;
			len = ft_strlen(parser->map2d[i]);
			if (len > map_width)
				map_width = len;
		}
		else if (!ft_is_emty_line(parser->map2d[i]))
			break;
		else if (map_height > 0)
		{
			map_height++;
			len = ft_strlen(parser->map2d[i]);
			if (len > map_width)
				map_width = len;
		}
		if (map_height > 0)
		{
			map_height++;
		}
		i++;
	}
	parser->map_height = map_height;
	parser->map_width = map_width;
	if (map_height == 0 || map_width == 0)
		exit_error("Map is empty");
}

static void check_all(t_parser *parser)
{
	if(!parser->all_elements)
	{
		if (!parser->no_found)
			exit_error("NO_texture not found");
		if (!parser->so_found)
			exit_error("SO_texture not found");
		if (!parser->ea_found)
			exit_error("EA_texture not found");
		if (!parser->we_found)
			exit_error("WE_texture not found");
		if (!parser->f_found)
			exit_error("Floor_Color not found");
		if (!parser->c_found)
			exit_error("Ceiling_Color not found");
	}
}

static void extra_char(t_parser *parser)
{
	int		i;
	char	*trim;

	i = parser->start_line_map + parser->map_height;
	while (parser->map2d[i])
	{
		trim = ft_strtrim(parser->map2d[i], " \t\n");
		if (trim && *trim)
		{
			free(trim);
			exit_error("Unexpected characters after map");
		}
		free(trim);
		i++;
	}
}

static int flood_fill(t_parser *parser, int **wall, int y, int x)
{
	if (y < 0 || y >= parser->map_height || x < 0 || x >= parser->map_width)
		return (0);
	if (wall[y][x] == 1 || parser->map[y][x] == 1)
		return (0);
	wall[y][x] = 1;
	if (y == 0 || y == parser->map_height - 1
		|| x == 0 || x == parser->map_width - 1)
	{
		parser->invalid_map = true;
		exit_error("Map is not closed by walls");
	}
	flood_fill(parser, wall, y + 1, x);
	flood_fill(parser, wall, y - 1, x);
	flood_fill(parser, wall, y, x + 1);
	flood_fill(parser, wall, y, x - 1);


	flood_fill(parser, wall, y + 1, x + 1);
	flood_fill(parser, wall, y + 1, x - 1);
	flood_fill(parser, wall, y - 1, x + 1);
	flood_fill(parser, wall, y - 1, x - 1);
	return (0);
}


static void check_walls(t_parser *parser)
{
	int **wall;
	int	i;

	parser->invalid_map = false;
	wall = ft_malloc(sizeof(int *) * parser->map_height);
	if(!wall)
		exit_error("faild alocation for check_walls()->H");
	i = 0;
	while (i < parser->map_height)
	{ 
		wall[i] = NULL;
		i++;
	}
	i = 0;
	while (i < parser->map_height)
	{
		wall[i] = ft_calloc(parser->map_width, sizeof(int));
		if(!wall[i])
			exit_error("failed alocation in check_wall()->W");
		i++;
	}
	if (parser->player_found)
	{
		flood_fill(parser, wall, parser->player_pos_y, parser->player_pos_x);
		if (parser->invalid_map)
			exit_error("Map is not closed by walls");
	}
	else
	{
		int y = 0;
		while (y < parser->map_height)
		{
			int x = 0;
			while (x < parser->map_width)
			{
				if (parser->map[y][x] == 0 )
				{
					flood_fill(parser, wall, y, x);
					if(parser->invalid_map)
						exit_error("Map is not closed by walls");
					y = parser->map_height;
					break;
				}
			}
			x++;
		}
		y++;
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
	fill_map(parser);
	check_walls(parser);
	extra_char(parser);
	return (0);
}
