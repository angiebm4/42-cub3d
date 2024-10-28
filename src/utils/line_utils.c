/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:00:20 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 14:00:22 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	line_is_empty(char *line, char *empty_set)
{
	int	index;

	index = 0;
	if (!line || !line[0])
		return (1);
	while (line[index])
	{
		if (ft_strchr(empty_set, line[index]) == NULL)
			return (0);
		index++;
	}
	return (1);
}

int	line_is_comment(char *line, char *comment_set)
{
	if (!line)
		return (0);
	return (ft_strchr(comment_set, line[0]) != NULL);
}

int	line_is_placeholder(char *supposed_ph, t_parsed_data *parsed)
{
	char	**spl;
	int		index;
	int		res;

	index = 0;
	res = -1;
	spl = ft_split(VIEWS_PLACEHOLDERS, SEPARATOR_PLACEHOLDER);
	if (!spl)
		parse_error(ERROR_MALLOC, parsed, 0);
	while (spl[index])
	{
		if (ft_strcmp(spl[index], supposed_ph) == 0)
		{
			res = index;
			break ;
		}
		index++;
	}
	ft_free_split(spl);
	return (res);
}

int	line_can_omitted(char *line)
{
	return (
		line_is_comment(line, COMMENT_SET) || \
		line_is_empty(line, EMPTY_SET)
	);
}
