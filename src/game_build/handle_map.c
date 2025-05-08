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

static int map_line(char *trim)
{
	while (*trim)
	{
		if (!ft_strchr(" 01NSWE", *trim))
			return 0;
		trim++;
	}
	return 1;
}

static int find_start_of_map(t_parser *parser, int start_i)
{
	char	*trim;
	int		i;

	i = start_i - 1;
	while(parser->map2d[++i])
	{
		// printf("Checking line %d: [%s]\n", i, parser->map2d[i]);
		trim = ft_strtrim(parser->map2d[i], " \t\n");
		if (trim && *trim)
		{
			// printf("Trimmed line: [%s]\n", trim);
			if(map_line(trim))
			{
				parser->start_line_map = i;
				// printf("DEBUG: parser->map_started = %d\n", parser->start_line_map);
				// printf("%s\n", trim);
				free(trim);
				return (0);
			}
			else
			{
				free(trim);
				exit_error("Invalid line of map");
			}
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
	{
		handle_floor_color(trim, parser);
		// parser->f_found = true;
		// if (parser->floor_set)
		// 	exit_error("Floor Color Dublicated");
	}
	else if (!ft_strncmp(trim, "C ", 2))
	{
		handle_ceiling_color(trim, parser);
		// parser->c_found = true;
	}
	if (parser->no_found && parser->so_found && parser->ea_found
		&& parser->we_found && parser->f_found && parser->c_found)
		parser->all_elements = true;
	return (0);
}
static	int		create_int_array(t_parser *parser)
{
	int		i;

	parser->map = ft_malloc(sizeof(int *) * parser->map_height);
	if(!parser->map)
		exit_error("Failed to alocate memory for rows");
	i = 0;
	while (i < parser->map_height)
	{
		parser->map[i] = ft_malloc(sizeof(int) * parser->map_width);
		if (!parser->map[i])
			exit_error("Failed to alocate memory for col");
		i++;
	}
	return 0;
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
	printf("map height %d\n", map_height);
	printf("map width %d\n", map_width);
	parser->map_height = map_height;
	parser->map_width = map_width;
}

int	parse_map(t_parser *parser)
{
	char	*trim;
	int		i;

	i = -1;
	while (parser->map2d[++i] && !parser->all_elements)
	{
		trim = ft_strtrim(parser->map2d[i], " \t");
		if (trim && *trim)
		{
			if(check_all_elements_file(trim, parser))
				return (free(trim),1);
		}
		free(trim);
	}
	if(!parser->all_elements)
	{
		if (!parser->no_found)
			exit_error("Error: NO_texture not found\n");
		if (!parser->so_found)
			exit_error("Error: SO_texture not found\n");
		if (!parser->ea_found)
			exit_error("Error: EA_texture not found\n");
		if (!parser->we_found)
			exit_error("Error: WE_texture not found\n");
		if (!parser->f_found)
			exit_error("Error: Floor_Color not found\n");
		if (!parser->c_found)
			exit_error("Error: Ceiling_Color not found\n");
	}
	// printf("%d\n", i);
	find_start_of_map(parser, i + 1);
	convert_map_to_int(parser);
	create_int_array(parser);
	put_map_elements(parser);
	// printf("--> map count line :%d\n", parser->map_started);
	return (0);
}
