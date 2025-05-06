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

static	int	check_all_elements_file(char *trim, t_parser *parser)
{
	if (!ft_strncmp(trim, "NO ", 3))
	{
		parser->no_found = true;
		//store the path
		parser->no_texture = ft_strtrim(trim + 3, " \t");
		if (!parser->no_found)
			exit_error("Failed to find the path for NO_texture");
	}
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

int	parse_map(t_parser *parser)
{
	char	*trim;
	int		i;

	i = -1;
	init_map(parser);
	while (parser->map2d[++i] && !parser->all_elements)
	{
		trim = ft_strtrim(parser->map2d[i], " \t");
		if (trim && *trim)
			check_all_elements_file(trim, parser);
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
	if (parser->no_texture)
		printf("---> PATH <---------> %s\n", parser->no_texture);
	if (parser->so_texture)
		printf("---> PATH <---------> %s\n", parser->no_texture);
	return (0);
}
