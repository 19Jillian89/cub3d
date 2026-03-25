/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:51:06 by ilnassi           #+#    #+#             */
/*   Updated: 2026/03/24 17:52:07 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Prints an error message and terminates the program
Parameters:
- game: pointer to t_game (can be NULL if an error occurs before allocation)
- message: string with the error message
What it does:
- Prints "Error\n" to stderr
- Prints the error message to stderr
- If game != NULL: frees all memory
- Exits the program with exit(1)*/
void	error_exit(t_game *game, char *message)
{
	write(2, "Error\n", 6);
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	if (game)
		free_game(game);
	exit(1);
}
