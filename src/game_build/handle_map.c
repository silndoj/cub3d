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

static	int	map_line(char *trim)
{
	while (*trim)
	{
		if (!ft_strchr(" 01NSWE", *trim))
			return (0);
		trim++;
	}
	return (1);
}

static	int	find_start_of_map(t_parser *parser, int start_i)
{
	char	*trim;
	int		i;

	i = start_i - 1;
	while (parser->map2d[++i])
	{
		trim = ft_strtrim(parser->map2d[i], " \t\n");
		if (trim && *trim)
		{
			if (map_line(trim))
			{
				parser->start_line_map = i;
				free(trim);
				return (0);
			}
			// else
			// {
				free(trim);
				exit_error("Invalid line of map");
			// }
		}
		free(trim);
	}
	exit_error("Could not find start of map");
	return (1);
}

static	int	check_all_elements_file(char *trim, t_parser *parser)
{
	if (!ft_strncmp(trim, "NO ", 3))
		handle_north_texture(trim, parser);
	else if (!ft_strncmp(trim, "SO ", 3))
		handle_south_texture(trim, parser);
	else if (!ft_strncmp(trim, "EA ", 3))
		handle_east_texture(trim, parser);
	else if (!ft_strncmp(trim, "WE ", 3))
		handle_west_texture(trim, parser);
	else if (!ft_strncmp(trim, "F ", 2))
		handle_floor_color(trim, parser);
	else if (!ft_strncmp(trim, "C ", 2))
		handle_ceiling_color(trim, parser);
	if (parser->no_found && parser->so_found && parser->ea_found
		&& parser->we_found && parser->f_found && parser->c_found)
		parser->all_elements = true;
	return (0);
}

static	int	create_int_array(t_parser *parser)
{
	int		i;

	parser->map = ft_malloc(sizeof(int *) * parser->map_height);
	if (!parser->map)
		exit_error("Failed to alocate memory for rows");
	i = 0;
	while (i < parser->map_height)
	{
		parser->map[i] = ft_malloc(sizeof(int) * parser->map_width);
		if (!parser->map[i])
			exit_error("Failed to alocate memory for col");

		i++;
	}
	return (0);
}

static	void fill_map(t_parser *parser, char c, int len)
{
	if (parser->x < len)
	{
		c = parser->map2d[parser->start_line_map][parser->x];
		if (c == '\t')
			c = ' ';
	}
	else
		c = ' ';
	if (c == '1')
		parser->map[parser->y][parser->x] = 1;
	else if (c == '0')
		parser->map[parser->y][parser->x] = 0;
	else if (c == ' ')
		parser->map[parser->y][parser->x] = -1;
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		if (parser->player_found)
			exit_error("Multiple players found");
		if (parser->y == 0 || parser->y == parser->map_height - 1
			|| parser->x == 0 || parser->x == parser->map_width - 1)
			exit_error("Player on edge");
		parser->map[parser->y][parser->x] = 8;
		parser->player_found = true;
	}
	else
		exit_error("Invalid character");
}

static	int	put_map_elements(t_parser *parser)
{
	int		len;
	char	c;

	c = '\0';
	parser->y = 0;
	len = 0;
	while (parser->y < parser->map_height && parser->map2d[parser->start_line_map])
	{
		len = ft_strlen(parser->map2d[parser->start_line_map]);
		parser->x = 0;
		while (parser->x < parser->map_width)
		{
			fill_map(parser, c, len);
			parser->x++;
		}
		parser->y++;
		parser->start_line_map++;
	}
	if (!parser->player_found)
		exit_error("Missing player position");
	return (0);
}

static	void convert_map_to_int(t_parser *parser)
{
	int		i;
	int		map_width;
	int		map_height;
	int		len;
	char	*trim;

	i = parser->start_line_map;
	map_width = 0;
	map_height = 0;
	len = 0;
	while (parser->map2d[i])
	{
		trim = ft_strtrim(parser->map2d[i], " \t\n");
		if (trim && *trim)
		{
			map_height++;
			len = ft_strlen(trim);
			if (len > map_width)
				map_width = len;
		}
		free(trim);
		i++;
	}
	parser->map_height = map_height;
	parser->map_width = map_width;
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

// static void map_pos(t_parser *parser, int map_start)
// {
// 	int		i;
// 	char	*trim;

// 	i = 0;
// 	while (i < map_start)
// 	{
// 		trim = ft_strtrim(parser->map2d[i], " \t\n");
// 		if (trim && *trim)
// 		{
// 			free(trim);
// 			exit_error("Map should appear in the end of the file");
// 		}
// 		free(trim);
// 		i++;
// 	}
// }

static void clean_up(t_parser *parser, int **wall)
{
	int i;

	i = 0;
	while (i < parser->map_height)
	{
		free(wall[i]);
		i++;
	}
}

static void flood_fill(t_parser *parser, int **wall, int y, int x)
{
	if (x < 0 || y < 0 || y >= parser->map_height || x >= parser->map_width)
		exit_error("Map is not closed by walls");
	if (parser->map[y][x] == -1)
		exit_error("Map is not closed by walls");
	if (wall[y][x] || parser->map[y][x] == 1)
		return ;
	wall[y][x] = 1;
	flood_fill(parser, wall, y + 1, x);
	flood_fill(parser, wall, y - 1, x);
	flood_fill(parser, wall, y, x + 1);
	flood_fill(parser, wall, y, x - 1);
}

static void check_walls(t_parser *parser)
{
	//alloc memory
	int **wall;
	int	i;

	wall = ft_malloc(sizeof(int *) * parser->map_height);
	if(!wall)
		exit_error("faild alocation for check_walls()->H");
	i = 0;
	while (i < parser->map_height)
	{
		wall[i] = ft_calloc(parser->map_width, sizeof(int));
		if(!wall[i])
		{
			clean_up(parser, wall);
			free(wall);
			exit_error("failed alocation in check_wall()->W");
		}
		i++;
	}
	//check
	int y;
	int x;
	int start;

	y =0;
	start = 0;

	while (y < parser->map_height)
	{
		x = 0;
		while (x < parser->map_width)
		{
			if ((parser->map[y][x] == 0 || parser->map[y][x] == 8 ) )
			{
				flood_fill(parser, wall, y, x);
				start = 1;
			}
			x++;
		}
		y++;
	}
	//clean up 
	clean_up(parser, wall);
	free(wall);
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
		{
			if(check_all_elements_file(trim, parser))
				return (free(trim), 1);
		}
		free(trim);
	}
	if (!parser->no_found || !parser->so_found || !parser->ea_found
		|| !parser->we_found || !parser->f_found || !parser->c_found)
	{
		check_all(parser);
	}
	find_start_of_map(parser, i + 1);
	convert_map_to_int(parser);
	if (create_int_array(parser))
		return (1);
	put_map_elements(parser);
	check_walls(parser);
	extra_char(parser);
	return (0);
}
