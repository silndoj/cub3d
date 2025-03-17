/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:40:39 by silndoj           #+#    #+#             */
/*   Updated: 2024/11/09 01:40:41 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H
# include <unistd.h>
# include <stdlib.h>

void	*ft_malloc(int size);
void	**get_allocation_array(size_t *count);
void	add_to_allocation_array(void *ptr);
void	free_allocations(void);

#endif
