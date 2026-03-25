/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:21:28 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 17:42:30 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Implements a manual realloc: allocates a new array of (count + 2) pointers,
 * copies the lines already collected, then appends the new line at the end.
 * We use calloc so the final NULL terminator is already present
 * in the last slot.
 * realloc is not in the allowed functions for the 42 project, so this
 * is the only option.
 * On failure, frees both line and lines to avoid leaks in the call chain
 * of read_all_lines. */
static char	**append_line(char **lines, char *line, int count)
{
	char	**tmp;

	tmp = calloc(count + 2, sizeof(char *));
	if (!tmp)
	{
		free(line);
		free_str_array(lines);
		return (NULL);
	}
	if (lines)
		ft_memcpy(tmp, lines, sizeof(char *) * count);
	if (lines)
		free(lines);
	tmp[count] = line;
	return (tmp);
}

/* Reads the file line by line using get_next_line and stores the result
 * in a NULL‑terminated array.
 * We do not know the number of lines in advance, so the array grows
 * dynamically at each iteration through append_line.
 * If append_line fails, cleanup has already been done inside it:
 * just return NULL. */
char	**read_all_lines(int fd)
{
	char	**lines;
	char	*line;
	int		count;

	lines = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines = append_line(lines, line, count++);
		if (!lines)
			return (NULL);
		line = get_next_line(fd);
	}
	return (lines);
}

/* Detects configuration (header) lines of the .cub file.
 * We use ft_strncmp with prefix + space ("NO ", "F ", ...) instead of
 * comparing only the letters so that a line like "NORTH" is not mistaken
 * for "NO". The space is part of the format specified by the subject. [web:40]
 * Returns 1 if the line is a header, 0 otherwise. */
int	is_header_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

/* Advances the pointer past leading spaces and tabs without allocating.
 * Useful after detecting the line type (e.g. "NO ") to isolate
 * the following value, which may contain extra padding spaces. */
char	*skip_whitespace(char *line)
{
	if (!line)
		return (NULL);
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

/* Removes the trailing '\n' that get_next_line leaves in the string.
 * Operates in‑place: no allocation needed.
 * All parsing functions call this before using the line,
 * so they do not have to handle the newline in comparisons or paths. */
void	trim_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}
