/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:23:58 by tndreka           #+#    #+#             */
/*   Updated: 2025/03/28 19:24:02 by tndreka          ###   ########.fr       */
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
        if(!trim || !*trim)
        {
            free(trim);
            continue;
        }
        if(ft_strchr("01NSEW", trim[0]))
        {
            parser->start_line_map = i;
            free(trim);
            break;
        }
    }
    return (0);
}