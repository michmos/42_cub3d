
#include "../../cub3d.h"

void	free_input(t_input *input)
{
	free(input->map.map);
	free(input->north_txtre);
	free(input->south_txtre);
	free(input->west_txtre);
	free(input->east_txtre);
}
