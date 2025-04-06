/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:38:48 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/06 15:28:03 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	file_extension(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (i < 4)
		return (0);
	i -= 4;
	if (!(filename[i] == '.' && filename[i + 1] == 'b' \
		&& filename[i + 2] == 'e' && filename[i + 3] == 'r'))
		return (0);
	return (1);
}

static int	map_height(char	*filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	line = get_next_line(fd, 0);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, 1);
	close(fd);
	return (height);
}

static char	**read_map(char	*filename, int height)
{
	int		i;
	int		fd;
	char	**map;
	char	*line;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	line = get_next_line(fd, 0);
	i = 0;
	while (line && (i < height))
	{
		map[i++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd, 0);
	}
	map[i] = NULL;
	get_next_line(fd, 1);
	close(fd);
	return (map);
}

int	parse_map(char	*filename, t_game	*game)
{
	if (!file_extension(filename))
		return (handle_error("Invalid file name or \
			missing .ber extension", NULL, 1));
	initialize_game_values(game);
	game -> height = map_height(filename);
	if (game -> height == 0)
		return (handle_error("Map height could not be determined", NULL, 1));
	game -> map = read_map(filename, game -> height);
	if (!game -> map)
		return (handle_error("Map could not be read", game -> map, 1));
	game -> width = ft_strlen(game -> map[0]);
	if (!game -> width)
		return (handle_error("Map width is invalid\n", game -> map, 1));
	if (!validate_map(game))
		return (handle_error("Invalid map format.\n", game -> map, 1));
	if (!validate_walls(game))
		return (handle_error("Map is not enclosed by walls\n", game -> map, 1));
	flood_fill_controller(game);
	return (1);
}
