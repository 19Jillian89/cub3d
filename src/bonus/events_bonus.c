/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                    :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>       +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:00:00 by vhacman           #+#    #+#            */
/*   Updated: 2026/03/24 18:00:00 by vhacman          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

/*
** FILE: events_bonus.c
** WHY: Bonus version of events.c — identical except setup_hooks also
** registers the MotionNotify hook for mouse camera rotation.
** Kept separate to comply with norminette (no #ifdef in function bodies).
** Compiled only with make bonus. Replaces src/events/events.c.
*/

#include "cub3d.h"

void	*init_mlx(void)
{
	void	*mlx;

	mlx = mlx_init();
	if (!mlx)
		error_exit(NULL, "Failed to initialize miniLibX");
	return (mlx);
}

void	*create_window(void *mlx)
{
	void	*win;

	win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cube3D");
	if (!win)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		error_exit(NULL, "Failed to create window");
	}
	return (win);
}

void	setup_hooks(t_game *game)
{
	load_door_texture(game);
	mlx_hook(game->win, EVENT_DESTROY_NOTIFY, 0, close_window, game);
	mlx_hook(game->win, EVENT_KEY_PRESS, MASK_KEY_PRESS, key_press, game);
	mlx_hook(game->win, EVENT_KEY_RELEASE, MASK_KEY_RELEASE, key_release, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx, render, game);
}

void	start_loop(t_game *game)
{
	mlx_loop(game->mlx);
}

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
