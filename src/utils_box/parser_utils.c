/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 05:30:01 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/10 05:32:55 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_is_empty_line(char *line)
{
	while (*line)
	{
		if (!ft_isspace((int)*line))
			return (0);
		line++;
	}
	return (1);
}

int	map_line(char *line)
{
	int	has_valid_char;

	has_valid_char = 0;
	while (*line)
	{
		if (!ft_strchr(" 01NSWE", *line))
			return (0);
		if (ft_strchr("01NSWE", *line))
			has_valid_char = 1;
		line++;
	}
	return (has_valid_char);
}

void	check_all(t_parser *parser)
{
	if (!parser->all_elements)
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
