/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmartin <edmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:07:56 by edmartin          #+#    #+#             */
/*   Updated: 2021/11/26 17:07:57 by edmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.height)
	{
		free(vars->map.arr[i++]);
	}
	free(vars->map.color);
	free(vars->map.arr);
	free(vars->iso.x_coord);
	free(vars->iso.y_coord);
}

void	free_array(char **array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_origin(int *xy_o, int *xy_f)
{
	free(xy_o);
	free(xy_f);
}
