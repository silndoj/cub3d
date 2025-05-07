/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:13:23 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/07 18:52:46 by tndreka          ###   ########.fr       */
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
	printf("%d\n", parser->floor.r);
	return 0;
}
