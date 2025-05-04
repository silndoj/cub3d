/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:23:58 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/04 19:35:52 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	int	check_all_elements_file(char *trim, t_parser *parser)
{
	if (!ft_strncmp(trim, "NO ", 3))
		parser->no_found = true;
	else if (!ft_strncmp(trim, "SO ", 3))
		parser->so_found = true;
	else if (!ft_strncmp(trim, "EA ", 3))
		parser->ea_found = true;
	else if (!ft_strncmp(trim, "WE ", 3))
		parser->we_found = true;
	else if (!ft_strncmp(trim, "F ", 2))
		parser->f_found = true;
	else if (!ft_strncmp(trim, "C ", 2))
		parser->c_found = true;
	if (parser->no_found && parser->so_found && parser->ea_found
		&& parser->we_found && parser->f_found && parser->c_found)
		parser->all_elements = true;
	return (0);
}

// static int check_map_pos(char *trim, t_parser *parser, int i)
// {
// 	if (!trim || !*trim)
// 			return 0;
// 	// if (check_all_elements_file(trim, parser))
// 	// {
// 	// 	parser->all_elements = true;
// 	// 	return 0;
// 	// }
// 	if (ft_strchr("01NSWE", trim[0]))
// 	{
// 		if (!parser->all_elements)
// 			return (printf("Map is not in the correct order\n"), 1);
// 		if(!parser->map_started)
// 			parser->start_line_map = i;
// 		parser->map_started = true;	
// 		return 0;	
// 	}
// 	return 0;
// }

int	parse_textures(t_parser *parser)
{
	char	*trim;
	int		i;

	i = -1;
	init_textures(parser);
	while (parser->map2d[++i] && !parser->all_elements)
	{
		trim = ft_strtrim(parser->map2d[i], " \t");
		if (trim && *trim)
			check_all_elements_file(trim, parser);
		free(trim);
	}
	return (0);
}
