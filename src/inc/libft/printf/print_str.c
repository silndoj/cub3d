/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:47:41 by silndoj           #+#    #+#             */
/*   Updated: 2025/05/10 07:06:52 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putstr_count(char *ptr, int *count)
{
	size_t	i;

	i = 0;
	if (!ptr)
		ptr = "(null)\0";
	while (ptr[i])
		i++;
	if (write(1, ptr, i) < 0)
	*count += i;
}
