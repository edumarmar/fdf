/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmartin <edmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:07:47 by edmartin          #+#    #+#             */
/*   Updated: 2021/11/26 17:07:48 by edmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*xy_create(int *arr, int x, int y)
{
	arr[0] = x;
	arr[1] = y;
	return (arr);
}

int	hex_to_int(char *hex)
{
	int		res;
	char	v;
	char	c;
	int		i;

	res = 0;
	i = 0;
	while (hex[i])
	{
		c = hex[i];
		v = (c & 0xF) + (c >> 6) | ((c >> 3) & 0x8);
		res = (res << 4) | (int) v;
		i++;
	}
	return (res);
}

int	count_height(char *path)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (i - 1);
}

int	count_width(char *path)
{
	char	**line_array;
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	line_array = ft_split(line, ' ');
	free(line);
	while (line_array[i])
	{
		i++;
	}
	free_array(line_array);
	return (i);
}
