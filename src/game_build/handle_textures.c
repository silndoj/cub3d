/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:23:58 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/03 20:46:47 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int check_map_pos(char *trim)
{
	if (ft_strchr("01NSWE", trim[0]))
		return(printf("bad_map POSITIOn\n"), 1);
	return 0;
}

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
        if(check_map_pos(trim))
			return (free(trim), 1);
    }
    return (0);
}