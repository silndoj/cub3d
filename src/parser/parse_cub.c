/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:16:26 by tndreka           #+#    #+#             */
/*   Updated: 2025/03/17 22:06:28 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "inc/get_next_line.h"
#include "inc/garbage_collector.h"


int parse_cub(int ac, char *av[], t_parser *parser)
{
    if (ac != 2)
    {
        printf("Error: Wrong number of arguments\n");
        return (1);
    }
    parser = (t_parser *) ft_malloc(sizeof(t_parser));
    return (check_map(av[1], parser));
}

int check_map(char *file, t_parser *parser)
{
    int fd;
    int i;


    i = ft_strlen(file);
    
    if (i < 4 || ft_strcmp(file + i - 4, ".cub") != 0)
    {
        printf("Error: Run ./cub3d map_name.cub\n");
        return (1);
    }
    fd = open(file, O_RDONLY);
    if (fd == -1)
	{
		printf("Error: File not found\n");
        return (1);
	}
    copy_map(fd, parser);
    print_map(parser);
    close(fd);
    return (0);
}

void    copy_map(int fd, t_parser *parser)
{
    char    *line;
    int     i;

    i = 0;
    parser->map2d = (char **) ft_malloc(sizeof(char *) * 100);
    while ((line = get_next_line(fd)))
    {
        parser->map2d[i] = line;
        i++;
    }
    parser->map2d[i] = NULL;
}

void print_map(t_parser *parser)
{
    int i;

    i = 0;
    while (parser->map2d[i])
    {
        printf("%s", parser->map2d[i]);
        i++;
    }
}