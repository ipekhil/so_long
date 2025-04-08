/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:25:36 by hiipek            #+#    #+#             */
/*   Updated: 2025/04/08 08:54:25 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (game -> height + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < game -> height)
	{
		copy[i] = ft_strdup(game -> map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
	}
	copy[i] = NULL;
	return (copy);
}

static void	flood_fill(t_game *game, char **map, int row, int col)
{
	if (row < 0 || col < 0 || row >= game -> height || col >= game -> width)
		return ;
	else if (map[row][col] == '1' || map[row][col] == 'F')
		return ;
	else if (map[row][col] == 'C')
		game -> count++;
	else if (map[row][col] == 'E')
		game -> exit_reached = 1;
	map[row][col] = 'F';
	flood_fill(game, map, row - 1, col);
	flood_fill(game, map, row + 1, col);
	flood_fill(game, map, row, col - 1);
	flood_fill(game, map, row, col + 1);
}

void	flood_fill_controller(t_game *game)
{
	char	**copy;

	copy = copy_map(game);
	flood_fill(game, copy, game -> player_x, game -> player_y);
	if (game -> collectibles != game -> count || game -> exit_reached != 1)
	{
		free_map(copy);
		handle_error("Unable to achieve targets\n", game -> map, 1);
	}
	free_map(copy);
}
