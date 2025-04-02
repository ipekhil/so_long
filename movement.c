#include "so_long.h"
#include <stdio.h>
int key_hook(int keycode, t_game *game)
{
    if (keycode == 65307)
        exit_game(game);
    else if (keycode == 119)
        move_player(game, 0, -1);
    else if (keycode == 115)
        move_player(game, 0, 1);
    else if (keycode == 97)
        move_player(game, -1, 0);
    else if (keycode == 100)
        move_player(game, 1, 0);
    return (0);
}

void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game -> moves);
}

void    move_player(t_game *game, int dx, int dy)
{
    int new_x;
    int new_y;

    new_x = game -> player_x + dx;
    new_y = game -> player_y + dy;
    if (game -> map[new_y][new_x] != '1')
	{
		if (game -> map[new_y][new_x] == 'C' && (game -> collectibles--))
		{
			game -> collected++;
			game -> map[new_y][new_x] = '0';
		}
		if (game -> map[new_y][new_x] == 'E')
		{
			if (game -> collectibles != 0)
			{
				render(game);
				ft_printf("All keys must be collected\n");
				return;
			}
			else
			{
				ft_printf("Congratulations!!\n");
				exit_game(game);
			}
		}
	}
	else
		return ;
    update_player_position(game, new_x, new_y);
    render(game);
}
