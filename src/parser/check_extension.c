/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:58:33 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:58:36 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_extension(char *filename, char *extension)
{
	size_t	flnm_length;
	size_t	ext_length;

	flnm_length = ft_strlen(filename);
	ext_length = ft_strlen(extension);
	if (flnm_length < ext_length)
		return (0);
	return (ft_strcmp(extension, &filename[flnm_length - ext_length]) == 0);
}
