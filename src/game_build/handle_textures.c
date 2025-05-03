/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:23:58 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/03 23:03:33 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int check_all_elements_file(char *trim)
{
	int no;
	int so;
	int we;
	int ea;
	int f;
	int c;
	
	no = 0;
	we = 0;
	so = 0;
	ea = 0;
	f = 0;
	c = 0;
	// if (!trim)
	// 	printf("\nhere\n");
	if(!ft_strncmp(trim, "NO", 2))
		no = 1;
	else if (!ft_strncmp(trim, "SO", 2))
		so = 1;
	else if (!ft_strncmp(trim, "EA", 2))
		ea = 1;
	else if (!ft_strncmp(trim, "WE", 2))
		we = 1;
	else if (!ft_strncmp(trim, "F", 1))
		f = 1;
	else if (!ft_strncmp(trim, "C", 1))
		c = 1;
	if (no == 0 || so == 0 || we == 0 || ea  == 0 || f == 0  || c == 0)	
		return 1;
	return 0;
}

static int check_map_pos(char *trim, t_parser *parser, int i)
{
	if (!trim || !*trim)
			return 0;
	if (check_all_elements_file(trim))
	{
		parser->all_elements = true;
		return 0;
	}
	if (ft_strchr("01NSWE", trim[0]))
	{
		// if (!parser->all_elements)
		// 	return (printf("Map is not in the correct order\n"), 1);
		parser->start_line_map = i;
		parser->map_started = true;	
		return 0;	
	}
	return 0;
}

int    parse_textures(t_parser *parser)
{
    char    *trim;
    int     i;
	int		ret_value;
	
    i = -1;
	
    init_textures(parser);
    while(parser->map2d[++i])
    {
		trim = ft_strtrim(parser->map2d[i], " \t");
        if((ret_value = check_map_pos(trim, parser, i)) == 1)
			return (free(trim), 1);
		if(ret_value == 0 && !parser->map_started)
		{
			printf("GAME OPEN ===>");
		}
		free(trim);
    }
    return (0);
}