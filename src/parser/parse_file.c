/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:22:48 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 17:44:31 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Header-line dispatcher: routes to parse_texture or parse_color based on
 * the prefix. If the line does not match any known identifier, we return 1
 * (error): process_lines calls this only on lines that is_header_line has
 * already validated, so arriving here with unknown prefix = bug.
 * Returns: 0 on success, 1 on error. */
static int	process_header_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(game, line));
	if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(game, line));
	return (1);
}

/* Scans the array of lines in two passes:
 * 1. Header: empty or header lines → process_header_line, stop at map start.
 * 2. Map: remaining lines → parse_map.
 * No explicit separator in .cub: line type change signals boundary.
 * Frees lines in all paths. Returns: 0 success, 1 error. */
static int	process_lines(t_game *game, char **lines)
{
	int	i;

	i = 0;
	while (lines[i] && (lines[i][0] == '\0' || is_header_line(lines[i])))
	{
		if (lines[i][0] != '\0' && process_header_line(game, lines[i]))
		{
			free_str_array(lines);
			return (1);
		}
		i++;
	}
	if (!lines[i])
	{
		free_str_array(lines);
		error_exit(game, "No map found in file");
		return (1);
	}
	game->raw_lines = lines;
	if (parse_map(game, lines + i))
		return (1);
	free_str_array(lines);
	game->raw_lines = NULL;
	return (0);
}

/* Checks .cub extension from path end (last 4 chars).
 * Rejects "./maps/test.cub.bak", excludes ".cub" (no filename).
 * Returns: 0 ok, 1 invalid. */
static int	check_extension(t_game *game, char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
	{
		error_exit(game, "File must have .cub extension");
		return (1);
	}
	return (0);
}

/* Opens file, reads with read_all_lines, closes fd always.
 * Returns: NULL-terminated lines array or NULL on fail. */
static char	**open_and_read(t_game *game, char *path)
{
	int		fd;
	char	**lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		error_exit(game, "Cannot open map file");
		return (NULL);
	}
	lines = read_all_lines(fd);
	close(fd);
	if (!lines)
		error_exit(game, "Failed to read map file");
	return (lines);
}

/* Entry: check ext → read file → process lines.
 * Each step fails early on error. Returns: 0 success, 1 error. */
int	parse_file(t_game *game, char *cub_path)
{
	char	**lines;

	if (check_extension(game, cub_path))
		return (1);
	lines = open_and_read(game, cub_path);
	if (!lines)
		return (1);
	return (process_lines(game, lines));
}
