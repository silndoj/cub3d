/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:13:23 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/07 18:54:55 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_floor_color(char *trim,t_parser  *parser)
{
	char	*floor;
	char	**value;

	floor = ft_strtrim(trim + 1, " \t");
	if (!floor)
		exit_error("Faild to find FLOOR_COLOR");
	value = ft_split(floor, ',');
	free(floor);
	parser->f_found = true;
	int i = 0;
	while (value[i])
		i++;
	printf("%d\n", i);
	if (i != 3)
		exit_error("Invalid Color Format.. try (R,G,B)");
	parser->floor.r = ft_atoi(value[0]);
	parser->floor.g = ft_atoi(value[1]);
	parser->floor.b = ft_atoi(value[2]);
	if ((parser->floor.r < 0 || parser->floor.r > 255)
		||(parser->floor.g < 0|| parser->floor.g > 255)
		|| (parser->floor.b < 0|| parser->floor.b > 255))
		exit_error("R,G,B values should be between the range of 0 to 255");
	// printf("%d\n", parser->floor.r);
	// printf("%d\n", parser->floor.g);
	// printf("%d\n", parser->floor.b);
	return 0;
}
