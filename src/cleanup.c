/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:23:26 by mmoser            #+#    #+#             */
/*   Updated: 2025/01/20 11:23:26 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_input(t_input *input)
{
	free(input->map.map);
	input->map.map = NULL;
	free(input->north_txtre);
	input->north_txtre = NULL;
	free(input->south_txtre);
	input->south_txtre = NULL;
	free(input->west_txtre);
	input->west_txtre = NULL;
	free(input->east_txtre);
	input->east_txtre = NULL;
}
