/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:59:30 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:59:37 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#define SUBSTITUTE_LINE	" \n"

static char	*add_line(char *line, char *buffer, t_parsed_data *parsed)
{
	char	*aux;

	aux = buffer;
	if (line_is_empty(line, EMPTY_SET))
		line = SUBSTITUTE_LINE;
	if (!line_is_comment(line, COMMENT_SET))
	{
		aux = ft_strjoin(buffer, line);
		if (!aux)
			parse_error(ERROR_MALLOC, parsed, 0);
		free(buffer);
	}
	return (aux);
}

char	**save_map(t_parsed_data *parsed, char *line)
{
	char	*buffer;
	char	**map;

	buffer = line;
	line = get_next_line(parsed->fd);
	while (line)
	{
		buffer = add_line(line, buffer, parsed);
		free(line);
		line = get_next_line(parsed->fd);
	}
	map = ft_split(buffer, '\n');
	if (!map)
		parse_error(ERROR_MALLOC, parsed, 0);
	free(buffer);
	return (map);
}
