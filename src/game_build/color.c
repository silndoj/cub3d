/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:13:23 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/12 22:50:00 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	void	ft_clean_split(char **split, int index)
{
	int		j;

	j = 0;
	while (j < index)
	{
		free(split[j]);
		j++;
	}
}

static	void	check_rgb_count(char **value, int i, t_parser *parser)
{
	while (value && value[i])
		i++;
	if (!value || i != 3)
	{
		if (value)
		{
			ft_clean_split(value, i);
			free(value);
		}
		exit_error("Invalid Color Format.. try (R,G,B)", parser);
	}
}

static int	validate_rgb(t_color *color, char **value, int i, t_parser *parser)
{
	color->r = ft_atoi(value[0]);
	color->g = ft_atoi(value[1]);
	color->b = ft_atoi(value[2]);
	if ((color->r < 0 || color->r > 255)
		|| (color->g < 0 || color->g > 255)
		|| (color->b < 0 || color->b > 255))
	{
		ft_clean_split(value, i);
		free(value);
		exit_error("values should be between the range of 0 to 255", parser);
	}
	return (0);
}

int	handle_floor_color(char *trim, t_parser *parser)
{
	char	*floor;
	char	**value;
	int		i;

	floor = ft_strtrim(trim + 1, " \t");
	if (!floor)
		exit_error("Failed to find FLOOR_COLOR", parser);
	value = ft_split(floor, ',');
	free(floor);
	i = 0;
	check_rgb_count(value, i, parser);
	validate_rgb(&parser->floor, value, i, parser);
	parser->floor_set = true;
	parser->f_found = true;
	i = 0;
	while (i < 3)
	{
		free(value[i]);
		i++;
	}
	free(value);
	return (0);
}

int	handle_ceiling_color(char *trim, t_parser *parser)
{
	char	*ceiling;
	char	**value;
	int		i;

	ceiling = ft_strtrim(trim + 1, " \t");
	if (!ceiling)
		exit_error("Failed to find CEILING_COLOR", parser);
	value = ft_split(ceiling, ',');
	free(ceiling);
	i = 0;
	check_rgb_count(value, i, parser);
	validate_rgb(&parser->ceiling, value, i, parser);
	parser->ceiling_set = true;
	parser->c_found = true;
	i = 0;
	while (i < 3)
	{
		free(value[i]);
		i++;
	}
	free(value);
	return (0);
}
