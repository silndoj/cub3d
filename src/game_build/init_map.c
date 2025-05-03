/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:05:47 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/03 21:50:51 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    init_textures(t_parser *parser)
{
    parser->no_texture = NULL;
    parser->so_texture = NULL;
    parser->we_texture = NULL;
    parser->ea_texture = NULL;
	parser->map_started = false;
	parser->all_elements = false;
}

