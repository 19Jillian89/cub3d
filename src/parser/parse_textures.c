/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:24:03 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 17:45:28 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Maps prefix to TEX_NO/SO/WE/EA (0-3). Uses ft_strncmp("XX ", 3) since
 * line contains path after space. Returns -1 if unknown. */
static int	get_tex_index(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (TEX_NO);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (TEX_SO);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (TEX_WE);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (TEX_EA);
	return (-1);
}

/* Extracts XPM path after "XX " using skip_whitespace + trim_newline.
 * Returns strdup(path) or NULL if empty/malloc fail. */
static char	*extract_path(char *line)
{
	char	*path;

	path = skip_whitespace(line + 3);
	trim_newline(path);
	if (*path == '\0')
		return (NULL);
	return (ft_strdup(path));
}

/* Parses texture line → game->textures[idx].path.
 * Checks idx>=0, no duplicates (path==NULL sentinel), valid path.
 * Returns: 0 ok, 1 error (error_exit called). */
int	parse_texture(t_game *game, char *line)
{
	int		idx;
	char	*path;

	idx = get_tex_index(line);
	if (idx < 0)
	{
		error_exit(game, "Unknown texture identifier");
		return (1);
	}
	if (game->textures[idx].path)
	{
		error_exit(game, "Duplicate texture definition");
		return (1);
	}
	path = extract_path(line);
	if (!path)
	{
		error_exit(game, "Missing or empty texture path");
		return (1);
	}
	game->textures[idx].path = path;
	return (0);
}
