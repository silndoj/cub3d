/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:16:23 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/06 17:35:56 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	map_build(int ac, char *av[], t_parser *parser)
{
	if (ac != 2)
		exit_error("Error: Wrong number of arguments\n");
	parser = (t_parser *) ft_malloc(sizeof(t_parser));
	return (check_map(av[1], parser));
}

int	check_map(char *file, t_parser *parser)
{
	int		fd;
	int		i;

	i = ft_strlen(file);
	if (i < 4 || ft_strcmp(file + i - 4, ".cub") != 0)
		exit_error("Error: Try ./cub3d map_name.cub\n");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (errno_exit(), 1);
	copy_map(fd, parser);
	print_map(parser);
	close(fd);
	if (parse_map(parser))
		return (1);
	return (0);
}

void	copy_map(int fd, t_parser *parser)
{
	char	*line;
	int		i;

	i = 0;
	parser->map2d = (char **) ft_malloc(sizeof(char *) * 100);
	while ((line = get_next_line(fd)))
	{
		parser->map2d[i] = line;
		i++;
	}
	parser->map2d[i] = NULL;
}

void	print_map(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser->map2d[i])
	{
		printf("%s\n", parser->map2d[i]);
		i++;
	}
}
