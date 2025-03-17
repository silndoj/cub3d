/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:40:25 by silndoj           #+#    #+#             */
/*   Updated: 2025/03/17 20:23:36 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/garbage_collector.h"

void	free_2d(void **ptr, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		free(*(ptr + i));
	free(ptr);
}

void	**get_allocation_array(size_t *count)
{
	static void		**allocation_array;
	static size_t	allocation_count;

	if (allocation_array == NULL)
	{
		allocation_array = (void **)malloc(10000 * sizeof(void *));
		if (allocation_array == NULL)
		{
			write(1, "Failed to initialize allocation array.\n", 39);
			return (NULL);
		}
		allocation_count = 0;
		*count = allocation_count;
		return (allocation_array);
	}
	allocation_count ++;
	*count = allocation_count;
	return (allocation_array);
}

void	add_to_allocation_array(void *ptr)
{
	size_t	count;
	void	**allocation_array;

	allocation_array = get_allocation_array(&count);
	if (count >= 10000)
	{
		write(1, "Reached maximum allocation capacity.\n", 37);
		return ;
	}
	allocation_array[count] = ptr;
}

void	*ft_malloc(int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		write(1, "Failed to initialize allocation array.\n", 39);
		free_allocations();
		return (NULL);
	}
	add_to_allocation_array(ptr);
	return (ptr);
}

void	free_allocations(void)
{
	void	**allocation_array;
	size_t	count;

	allocation_array = get_allocation_array(&count);
	free_2d(allocation_array, count);
	write(1, "All allocated memory freed.\n", 28);
}
