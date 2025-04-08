/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:26:18 by hiipek            #+#    #+#             */
/*   Updated: 2025/04/08 11:03:21 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_map_cell(t_game *game, int row, int col, int *counts)
{
	if (game -> map[row][col] == 'P')
	{
		counts[0]++;
		game->player_x = col;
		game->player_y = row;
	}
	else if (game -> map[row][col] == 'C')
	{
		counts[1]++;
		game -> collectibles++;
	}
	else if (game -> map[row][col] == 'E')
		counts[2]++;
	else if (game -> map[row][col] != '0' && game -> map[row][col] != '1')
		return (0);
	return (1);
}

int	validate_map(t_game *game)
{
	int	row;
	int	col;
	int	counts[3];

	row = 0;
	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	while (row < game->height)
	{
		if ((int)ft_strlen(game -> map[row]) != game -> width)
			return (0);
		col = -1;
		while (game -> map[row][++col])
		{
			if (!check_map_cell(game, row, col, counts))
				return (0);
		}
		row++;
	}
	if (counts[0] != 1 || counts[1] < 1 || counts[2] != 1)
		return (0);
	return (1);
}

int	validate_walls(t_game *game)
{
	int	row;
	int	col;

	col = -1;
	while (++col < game -> width)
	{
		if ((game -> map[0][col] != '1') ||
			(game -> map[game -> height - 1][col] != '1'))
			return (0);
	}
	row = -1;
	while (++row < game -> height)
	{
		if ((game -> map[row][0] != '1') ||
			(game -> map[row][game -> width - 1] != '1'))
			return (0);
	}
	return (1);
}
