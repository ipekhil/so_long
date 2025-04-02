#include "so_long.h"

static int	check_map_cell(t_game *game, int row, int col, int *p, int *c, int *e)
{
	if (game -> map[row][col] == 'P')
	{
		(*p)++;
		game->player_x = col;
		game->player_y = row;
	}
	else if (game -> map[row][col] == 'C')
	{
		(*c)++;			
		game -> collectibles++;
	}
	else if (game -> map[row][col] == 'E')
		(*e)++;
	else if (game -> map[row][col] != '0' && game -> map[row][col] != '1')
		return (0);	
	return (1);
}

int	validate_map(t_game *game)
{
	int	row;
	int	col;
	int	p_count;
	int	c_count;
	int	e_count;

	row = -1;
	p_count = 0;
	c_count = 0;
	e_count = 0;
	while (game -> map[++row])
	{
		if ((int)ft_strlen(game -> map[row]) != game -> width)
			return (0);
		col = -1;
		while (game -> map[row][++col])
		{
			if (!check_map_cell(game, row, col, &p_count, &c_count, &e_count))
				return (0);
		}
	}
	if (p_count != 1 || c_count < 1 || e_count != 1)
		return (0);
	return (1);	
}

int	validate_walls(t_game *game)
{
	int row;
	int	col;

	col = -1;
	while (++col < game -> width)
	{
		if ((game -> map[0][col] != '1') || (game -> map[game -> height - 1][col] != '1'))
				return(0);
	}
	row = -1;
	while (++row < game -> height)
	{
		if (game -> map[row][0] != '1' || game -> map[row][game -> width - 1] != '1')
			return (0);
	}
	return (1);
}
