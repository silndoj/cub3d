/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 05:30:01 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/12 22:42:01 by tndreka          ###   ########.fr       */
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
			exit_error("NO_texture not found", parser);
		if (!parser->so_found)
			exit_error("SO_texture not found", parser);
		if (!parser->ea_found)
			exit_error("EA_texture not found", parser);
		if (!parser->we_found)
			exit_error("WE_texture not found", parser);
		if (!parser->f_found)
			exit_error("Floor_Color not found", parser);
		if (!parser->c_found)
			exit_error("Ceiling_Color not found", parser);
	}
}

void	extra_char(t_parser *parser)
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
			exit_error("Unexpected characters after map", parser);
		}
		free(trim);
		i++;
	}
}
