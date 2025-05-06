/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:38:25 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/06 17:38:54 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int handle_north_texture(char *trim, t_parser *parser)
{
	parser->no_found = true;
	//store the path
	parser->no_texture = ft_strtrim(trim + 3, " \t\n");
	//if after the identifier there is no path return error
	if (!parser->no_texture || parser->no_texture[0] == '\0')
	{
		free(parser->no_texture);
		exit_error("Failed to find the path for NO_texture");
	}
	return 0;
}

int handle_south_texture(char *trim, t_parser *parser)
{
	parser->so_found = true;
	parser->so_texture = ft_strtrim(trim + 3, " \t");
	if (!parser->so_texture)
		exit_error("Failed to find the path for SO_texture");
	return 0;
}
int handle_east_texture(char *trim, t_parser *parser)
{
	parser->ea_found = true;
	parser->ea_texture = ft_strtrim(trim + 3, " \t");
	if (!parser->ea_texture)
		exit_error("Failed to find the path for EA_texture");
	return 0;
}

int handle_west_texture(char *trim, t_parser *parser)
{
	parser->we_found = true;
	parser->we_texture = ft_strtrim(trim + 3, " \t");
	if (!parser->we_texture)
		exit_error("Failed to find the path for WE_texture");
	return 0;
}
