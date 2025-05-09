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

int	handle_north_texture(char *trim, t_parser *parser)
{
	int	fd;
	int len;

	if (parser->no_texture)
		exit_error("NO_texture is dublicated");
	parser->no_texture = ft_strtrim(trim + 3, " \t\n");
	if (!parser->no_texture || parser->no_texture[0] == '\0')
	{
		free(parser->no_texture);
		exit_error("Failed to find the path for NO_texture");
	}
	len = ft_strlen(parser->no_texture);
	if (len < 4 || ft_strcmp(parser->no_texture + len - 4, ".png") != 0)
		exit_error("NO_texture should be a .png file");
	fd = open(parser->no_texture, O_RDONLY);
	if (fd == -1)
		exit_error("NO_texture not found or inaccessible");
	close(fd);
	parser->no_found = true;
	return (0);
}

int	handle_south_texture(char *trim, t_parser *parser)
{
	int	fd;
	int len;

	if (parser->so_texture)
		exit_error("SO_texture is dublicated");
	parser->so_texture = ft_strtrim(trim + 3, " \t\n");
	if (!parser->so_texture || parser->so_texture[0] == '\0')
	{
		free(parser->so_texture);
		exit_error("Failed to find the path for SO_texture");
	}
	len = ft_strlen(parser->so_texture);
	if (len < 4 || ft_strcmp(parser->so_texture + len - 4, ".png") != 0)
		exit_error("NO_texture should be a .png file");
	fd = open(parser->so_texture, O_RDONLY);
	if (fd == -1)
		exit_error("SO_texture not found or inaccessible");
	close(fd);
	parser->so_found = true;
	return (0);
}

int	handle_east_texture(char *trim, t_parser *parser)
{
	int	fd;
	int len;

	if (parser->ea_texture)
		exit_error("EA_texture is dublicated");
	parser->ea_texture = ft_strtrim(trim + 3, " \t\n");
	if (!parser->ea_texture || parser->ea_texture[0] == '\0')
	{
		free(parser->ea_texture);
		exit_error("Failed to find the path for EA_texture");
	}
	len = ft_strlen(parser->ea_texture);
	if (len < 4 || ft_strcmp(parser->ea_texture + len - 4, ".png") != 0)
		exit_error("NO_texture should be a .png file");
	fd = open(parser->ea_texture, O_RDONLY);
	if (fd == -1)
		exit_error("EA_texture not found or inaccessible");
	close(fd);
	parser->ea_found = true;
	return (0);
}

int	handle_west_texture(char *trim, t_parser *parser)
{
	int	fd;
	int len;

	if (parser->we_texture)
		exit_error("WE_texture is dublicated");
	parser->we_texture = ft_strtrim(trim + 3, " \t\n");
	if (!parser->we_texture || parser->we_texture[0] == '\0')
	{
		free(parser->we_texture);
		exit_error("Failed to find the path for WE_texture");
	}
	len = ft_strlen(parser->we_texture);
	if (len < 4 || ft_strcmp(parser->we_texture + len - 4, ".png") != 0)
		exit_error("NO_texture should be a .png file");
	fd = open(parser->we_texture, O_RDONLY);
	if (fd == -1)
		exit_error("WE_texture not found or inaccessible");
	close(fd);
	parser->we_found = true;
	return (0);
}
