/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:19:44 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 18:01:20 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calls mlx_init() and returns the MLX handle.
 * Exits the program if initialization fails. */
void	*init_mlx(void)
{
	void	*mlx;

	mlx = mlx_init();
	if (!mlx)
		error_exit(NULL, "Failed to initialize miniLibX");
	return (mlx);
}

/* Creates a window of size SCREEN_WIDTH × SCREEN_HEIGHT.
 * If mlx_new_window fails, destroys the display and frees the mlx
 * pointer before exiting (mlx_init uses malloc internally). */
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

/* Registers the callbacks for: window close, key press,
 * key release, and the game loop (render called roughly ~60 fps). */
void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, EVENT_DESTROY_NOTIFY, 0, close_window, game);
	mlx_hook(game->win, EVENT_KEY_PRESS, MASK_KEY_PRESS, key_press, game);
	mlx_hook(game->win, EVENT_KEY_RELEASE, MASK_KEY_RELEASE, key_release, game);
	mlx_loop_hook(game->mlx, render, game);
}

/* Enters the MLX event loop. Does not return. */
void	start_loop(t_game *game)
{
	mlx_loop(game->mlx);
}

/* Frees all allocated memory and exits the program.
 * Called on window close (X button) and on ESC key press. */
int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
