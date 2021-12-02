/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmartin <edmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:07:39 by edmartin          #+#    #+#             */
/*   Updated: 2021/11/26 17:07:40 by edmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	generate_matrix(int height, int width)
{
	int		*color;
	int		i;
	t_map	map;

	i = 0;
	map.arr = (int **)malloc(height * sizeof(int *));
	color = (int *)malloc(height * width * sizeof(int *));
	while (i < height)
	{
		map.arr[i++] = (int *)malloc(width * sizeof(int));
	}
	map.color = color;
	return (map);
}

t_map	fill_map_aux(t_map map, char **line_array, int i, int j)
{
	char	**split_color;

	if (ft_strchr(line_array[j - 1], ','))
	{
		split_color = ft_split(line_array[j - 1], ',');
		(map.arr)[i - 1][j - 1] = \
		ft_atoi(split_color[0]);
		(map.color)[j + (i - 1) * map.width - 1] = \
		hex_to_int(split_color[1]);
		free(split_color[0]);
		free(split_color[1]);
		free(split_color);
	}
	else
	{
		(map.arr)[i - 1][j - 1] = ft_atoi(line_array[j - 1]);
		(map.color)[j + (i - 1) * map.width - 1] = 0;
	}
	return (map);
}

t_map	new_map(char *path)
{
	t_map	map;
	int		height;
	int		width;

	height = count_height(path);
	width = count_width(path);
	map = generate_matrix(height, width);
	map.height = height;
	map.width = width;
	fill_map(map, path);
	return (map);
}

void	fill_map(t_map map, char *path)
{
	char	**line_array;
	char	*line;
	int		i;
	int		j;
	int		fd;

	i = 1;
	j = 1;
	fd = open(path, O_RDONLY);
	while (i <= map.height)
	{
		line = get_next_line(fd);
		line_array = ft_split(line, ' ');
		free(line);
		while (j <= map.width)
		{
			fill_map_aux(map, line_array, i, j);
			free(line_array[j - 1]);
			j++;
		}
		j = 1;
		i++;
		free(line_array);
	}
}
