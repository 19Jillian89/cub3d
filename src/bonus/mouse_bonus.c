/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                     :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+     */
/*   By: ilnassi <ilnassi@student.42roma.it>       +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:00:00 by ilnassi           #+#    #+#            */
/*   Updated: 2026/03/24 17:38:31 by vhacman          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

/*
** FILE: mouse_bonus.c
** WHY: Bonus — camera rotation via mouse MotionNotify (event 6).
** delta_x relative to window center drives rotate_player speed.
** Cursor is recentered every call to prevent it leaving the window.
** Hook registered in render_bonus.c setup or events.c with:
**   mlx_hook(game->win, 6, 1L<<6, mouse_move, game);
*/

#include "cub3d.h"

/* Recenters mouse cursor to the middle of the window. */
static void	recenter_mouse(t_game *game)
{
	mlx_mouse_move(game->mlx, game->win,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

/* Rotates player proportionally to horizontal mouse delta.
** Sensitivity scaled to avoid too-fast rotation. */
static void	apply_mouse_rotation(t_game *game, int x)
{
	double	delta;

	delta = (double)(x - SCREEN_WIDTH / 2);
	if (delta == 0)
		return ;
	rotate_player(game, delta * 0.001);
}

/* MotionNotify callback: called when mouse moves inside window.
** Computes delta_x from center, rotates player, recenters cursor. */
int	mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (x == SCREEN_WIDTH / 2)
		return (0);
	apply_mouse_rotation(game, x);
	recenter_mouse(game);
	return (0);
}
