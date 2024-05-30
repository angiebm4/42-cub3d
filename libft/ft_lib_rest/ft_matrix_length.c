/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor-@student.42madrid.com <lpastor-    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:06:31 by lpastor-@st       #+#    #+#             */
/*   Updated: 2024/05/30 18:08:22 by lpastor-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_matrix_length(char **matrix)
{
	size_t	index;

	index = 0;
	while (matrix[index])
		index++;
	return (index);
}
