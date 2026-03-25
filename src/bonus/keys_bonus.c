/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:00:00 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 17:36:48 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FILE: keys_bonus.c
** WHY: Bonus version of keys.c — identical to the mandatory one, except
**      for the handling of the E key to open doors (handle_doors).
**      Kept in a separate file: #ifdef inside function bodies
**      is forbidden by norminette. Compiled only with `make bonus`.
**      Replaces src/events/keys.c in the bonus build.
** CALLED FROM: mlx_hook (KeyPress/KeyRelease events), registered in events.c.
*/

#include "cub3d.h"

/* Initializes all key flags to 0 (not pressed). */
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

/* Key‑press handler: sets the corresponding flag to 1.
 * KEY_E opens the door in front of the player (doors bonus). */
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
	else if (keycode == KEY_E)
		handle_doors(game);
	else if (keycode == KEY_ESC)
		close_window(game);
	return (0);
}

/* Key‑release handler: sets the corresponding flag back to 0. */
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
