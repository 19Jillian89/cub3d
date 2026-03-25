/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:21:00 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 17:40:30 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Includes the main project header. */
#include "cub3d.h"

/* Initializes the state of all keys to "not pressed".
 * The flags are used for smooth movement: actual movement is handled
 * in the game loop, not directly on key press. */
void	init_keys(t_game *game)
{
	game->keys.w = 0;
	game->keys.s = 0;
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.esc = 0;
}

/* Key‑press handler: sets the corresponding key flag to 1.
 * If ESC is pressed, it closes the game immediately.
 * Returns 0 as required by mlx_hook convention. */
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		game->keys.w = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		game->keys.s = 1;
	else if (keycode == KEY_A || keycode == KEY_Q)
		game->keys.a = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	else if (keycode == KEY_ESC)
		close_window(game);
	return (0);
}

/* Key‑release handler: resets the corresponding key flag to 0.
 * Returns 0 as required by mlx_hook convention. */
int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		game->keys.w = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		game->keys.s = 0;
	else if (keycode == KEY_A || keycode == KEY_Q)
		game->keys.a = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}
