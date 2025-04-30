/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:23:58 by tndreka           #+#    #+#             */
/*   Updated: 2025/04/30 19:25:12 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int    parse_textures(t_parser *parser)
{
    char    *trim;
    int     i;

    i = -1;
    init_textures(parser);
    while(parser->map2d[++i])
    {
		trim = ft_strtrim(parser->map2d[i], " \t");
		if (!trim || !*trim)
			free(trim);
        
    }
    return (0);
}