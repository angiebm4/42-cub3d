/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:22:09 by lpastor-          #+#    #+#             */
/*   Updated: 2024/06/02 00:22:56 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isnumber(char *str)
{
	size_t	index;

	index = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		index++;
	while (str[index] && ft_isdigit(str[index]))
		index++;
	return (str[index] == '\0');
}
