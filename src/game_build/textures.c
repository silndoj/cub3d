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
	int	fd;

	parser->no_found = true;
	//check dublicate
	if (parser->no_texture)
		exit_error("NO_texture is dublicated");
	//store the path
	parser->no_texture = ft_strtrim(trim + 3, " \t\n");
	//if after the identifier there is no path return error
	if (!parser->no_texture || parser->no_texture[0] == '\0')
	{
		free(parser->no_texture);
		exit_error("Failed to find the path for NO_texture");
	}
	// printf("\nPATH\n%s\n", parser->no_texture);
	fd = open(parser->no_texture, O_RDONLY);
	if (fd == -1)
		exit_error("NO_texture not found or inaccessible");
	close(fd);
	return 0;
}

int handle_south_texture(char *trim, t_parser *parser)
{
	int fd;

	parser->so_found = true;
	if (parser->so_texture)
		exit_error("SO_texture is dublicated");
	parser->so_texture = ft_strtrim(trim + 3, " \t\n");
	if (!parser->so_texture || parser->so_texture[0] == '\0')
	{
		free(parser->so_texture);
		exit_error("Failed to find the path for SO_texture");
	}
	// printf("\nPATH\n%s\n", parser->so_texture);
	fd = open(parser->so_texture, O_RDONLY);
	if (fd == -1)
		exit_error("SO_texture not found or inaccessible");
	close(fd);
	return 0;
}
int handle_east_texture(char *trim, t_parser *parser)
{
	int fd;
	
	parser->ea_found = true;
	if (parser->ea_texture)
		exit_error("EA_texture is dublicated");
	parser->ea_texture = ft_strtrim(trim + 3, " \t\n");
	if (!parser->ea_texture || parser->ea_texture[0] == '\0')
	{
		free(parser->ea_texture);
		exit_error("Failed to find the path for EA_texture");
	}
	// printf("\nPATH\n%s\n", parser->ea_texture);
	fd = open(parser->ea_texture, O_RDONLY);
	if (fd == -1)
		exit_error("EA_texture not found or inaccessible");
	close(fd);
	return 0;
}

int handle_west_texture(char *trim, t_parser *parser)
{
	int fd;
	
	parser->we_found = true;
	if (parser->we_texture)
		exit_error("WE_texture is dublicated");
	parser->we_texture = ft_strtrim(trim + 3, " \t\n");
	if (!parser->we_texture || parser->we_texture[0] == '\0')
	{
		free(parser->we_texture);
		exit_error("Failed to find the path for WE_texture");
	}
	fd = open(parser->we_texture, O_RDONLY);
	if (fd == -1)
		exit_error("WE_texture not found or inaccessible");
	close(fd);
	return 0;
}
