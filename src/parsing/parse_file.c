/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:28:28 by mmoser            #+#    #+#             */
/*   Updated: 2025/01/22 14:57:24 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static t_error	parse_txtrs(t_in_stream *f_content, t_input *input,
		int *in_flags)
{
	t_error	error;

	error = 0;
	if (ft_strncmp(cur_ptr(f_content), "NO ", 3) == 0 && !(*in_flags & NO))
	{
		error = parse_txtre_path(f_content, &input->north_txtre);
		*in_flags |= NO;
	}
	else if (ft_strncmp(cur_ptr(f_content), "SO ", 3) == 0 && !(*in_flags & SO))
	{
		error = parse_txtre_path(f_content, &input->south_txtre);
		*in_flags |= SO;
	}
	else if (ft_strncmp(cur_ptr(f_content), "WE ", 3) == 0 && !(*in_flags & WE))
	{
		error = parse_txtre_path(f_content, &input->west_txtre);
		*in_flags |= WE;
	}
	else if (ft_strncmp(cur_ptr(f_content), "EA ", 3) == 0 && !(*in_flags & EA))
	{
		error = parse_txtre_path(f_content, &input->east_txtre);
		*in_flags |= EA;
	}
	return (error);
}

static t_error	parse_rest(t_in_stream *f_content, t_input *input,
		int *in_flags)
{
	if (ft_strncmp(cur_ptr(f_content), "F ", 2) == 0 && !(*in_flags & F))
	{
		*in_flags |= F;
		return (parse_rgb(f_content, &input->floor));
	}
	else if (ft_strncmp(cur_ptr(f_content), "C ", 2) == 0 && !(*in_flags & C))
	{
		*in_flags |= C;
		return (parse_rgb(f_content, &input->ceiling));
	}
	else if (is_valid_map_char(cur_char(f_content))
		&& *in_flags == (NO | SO | WE | EA | C | F))
	{
		*in_flags |= M;
		go_back_to_line_start(f_content);
		return (parse_map(f_content, &input->map));
	}
	else
	{
		put_parsing_err(f_content, "Unexpected token");
		put_expected_tokens(*in_flags);
		return (-1);
	}
}

static t_error	parse_content(t_input *input, t_in_stream *file_content)
{
	int	error;
	int	input_flags;

	input_flags = 0;
	error = 0;
	while (cur_char(file_content) && !error)
	{
		skip_whitespaces(file_content);
		if ((ft_strncmp(cur_ptr(file_content), "NO ", 3) == 0
				&& !(input_flags & NO)) || (ft_strncmp(cur_ptr(file_content),
					"SO ", 3) == 0 && !(input_flags & SO))
			|| (ft_strncmp(cur_ptr(file_content), "WE ", 3) == 0
				&& !(input_flags & WE)) || (ft_strncmp(cur_ptr(file_content),
					"EA ", 3) == 0 && !(input_flags & EA)))
			error = parse_txtrs(file_content, input, &input_flags);
		else
		{
			error = parse_rest(file_content, input, &input_flags);
			if (input_flags == ALL_FLAGS)
				break ;
		}
	}
	if (error)
		return (free_input(input), -1);
	return (0);
}

static bool	has_cub_extension(const char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len >= 4 && ft_strncmp(".cub", &file_name[len - 4], 5) == 0)
	{
		return (true);
	}
	return (false);
}

t_error	parse_file(t_input *input, const char *map_path)
{
	t_in_stream	file_content;
	int			fd;

	if (!has_cub_extension(map_path))
	{
		put_err("Config file must end on .cub");
		return (-1);
	}
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (perror("open"), -1);
	file_content.buffer = read_file(fd);
	if (!file_content.buffer)
	{
		return (-1);
	}
	file_content.idx = 0;
	file_content.crnt_lne_nbr = 1;
	if (parse_content(input, &file_content) == -1)
	{
		free(file_content.buffer);
		return (-1);
	}
	free(file_content.buffer);
	return (0);
}
