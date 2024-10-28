/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:59:03 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:59:05 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	add_map(t_parsed_data *parsed, char *buffer)
{
	if (buffer && parsed)
		parsed->map = save_map(parsed, buffer);
}

static int	add_placeholder(t_parsed_data *parsed, char *buffer)
{
	char	**spl;
	int		placeholder;
	int		res;
	char	*trimmed;

	trimmed = ft_strtrim(buffer, EMPTY_SET);
	if (!trimmed)
		parse_error(ERROR_MALLOC, parsed, 0);
	spl = ft_split(trimmed, ' ');
	if (!spl)
		parse_error(ERROR_MALLOC, parsed, 0);
	free(trimmed);
	placeholder = line_is_placeholder(spl[0], parsed);
	res = save_placeholder(parsed, spl, placeholder);
	ft_free_split(spl);
	return (res);
}

void	parse_file(t_parsed_data *parsed)
{
	char	*buffer;

	buffer = get_next_line(parsed->fd);
	while (buffer)
	{
		if (!line_can_omitted(buffer))
		{
			if (!add_placeholder(parsed, buffer))
				break ;
		}
		free(buffer);
		buffer = get_next_line(parsed->fd);
	}
	add_map(parsed, buffer);
	save_doors(parsed);
}
