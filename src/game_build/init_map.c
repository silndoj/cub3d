/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:05:47 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/08 16:48:57 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_parser *parser)
{
	parser->no_texture = NULL;
	parser->so_texture = NULL;
	parser->we_texture = NULL;
	parser->ea_texture = NULL;
	parser->map_found = false;
	parser->start_line_map = 0;
	parser->all_elements = false;
	parser->no_found = false;
	parser->so_found = false;
	parser->we_found = false;
	parser->ea_found = false;
	parser->f_found = false;
	parser->c_found = false;
	parser->ceiling_set = false;
	parser->floor_set = false;
}
