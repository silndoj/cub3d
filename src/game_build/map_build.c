/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:16:23 by tndreka           #+#    #+#             */
/*   Updated: 2025/05/12 23:02:40 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	map_build(int ac, char *av[], t_parser *parser)
{
	if (ac != 2)
		exit_error("Wrong number of arguments\n", parser);
	init_map(parser);
	return (check_map(av[1], parser));
}

int	check_map(char *file, t_parser *parser)
{
	int		fd;
	int		i;

	i = ft_strlen(file);
	if (i < 4 || ft_strcmp(file + i - 4, ".cub") != 0)
		exit_error("Try ./cub3d map_name.cub\n", parser);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (errno_exit(), 1);
	copy_map(fd, parser);
	close(fd);
	if (parse_map(parser))
		return (1);
	return (0);
}

void	copy_map(int fd, t_parser *parser)
{
	char	*line;
	char	*newline;
	int		i;

	i = 0;
	parser->map2d = (char **) malloc(sizeof(char *) * 1000);
	line = get_next_line(fd);
	while (line)
	{
		newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';
		parser->map2d[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	parser->map2d[i] = NULL;
}

void	print_map(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser->map2d[i])
	{
		printf("%s", parser->map2d[i]);
		i++;
	}
}

void	free_int_array(int **wall, int height)
{
	int	i;

	i = 0;
	if (!wall)
		return ;
	while (i < height)
	{
		free(wall[i]);
		i++;
	}
	free(wall);
}
