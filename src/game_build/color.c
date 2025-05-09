/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:13:23 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/09 19:44:35 by tndreka          ###   ########.fr       */
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

int	handle_floor_color(char *trim, t_parser *parser)
{
	char	*floor;
	char	**value;
	int		i;

	floor = ft_strtrim(trim + 1, " \t");
	if (!floor)
		exit_error("Faild to find FLOOR_COLOR");
	value = ft_split(floor, ',');
	free(floor);
	i = 0;
	while (value[i])
		i++;
	if (!value || i != 3)
	{
		if(value)
		{
			ft_clean_split(value, i);
			free(value);
		}
		exit_error("Invalid Color Format.. try (R,G,B)");
	}
	parser->floor.r = ft_atoi(value[0]);
	parser->floor.g = ft_atoi(value[1]);
	parser->floor.b = ft_atoi(value[2]);
	if ((parser->floor.r < 0 || parser->floor.r > 255)
		|| (parser->floor.g < 0 || parser->floor.g > 255)
		|| (parser->floor.b < 0 || parser->floor.b > 255))
	{
		ft_clean_split(value, i);
		free(value);
		exit_error("R,G,B values should be between the range of 0 to 255");
	}
	parser->floor_set = true;
	parser->f_found = true;
	ft_clean_split(value, i);
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
		exit_error("Faild to find CEILING_COLOR");
	value = ft_split(ceiling, ',');
	free(ceiling);
	i = 0;
	while (value[i])
		i++;
	if (!value || i != 3)
	{
		if(value)
		{
			ft_clean_split(value, i);
			free(value);
		}
		exit_error("Invalid Color Format.. try (R,G,B)");
	}
	parser->ceiling.r = ft_atoi(value[0]);
	parser->ceiling.g = ft_atoi(value[1]);
	parser->ceiling.b = ft_atoi(value[2]);
	if ((parser->ceiling.r < 0 || parser->ceiling.r > 255)
		|| (parser->ceiling.g < 0 || parser->ceiling.g > 255)
		|| (parser->ceiling.b < 0 || parser->ceiling.b > 255))
	{
		ft_clean_split(value, i);
		free(value);
		exit_error("R,G,B values should be between the range of 0 to 255");
	}
	parser->ceiling_set = true;
	parser->c_found = true;
	ft_clean_split(value, i);
	free(value);
	return (0);
}
