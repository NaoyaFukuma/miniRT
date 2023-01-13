#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	void *mlx = mlx_init();
	printf("%p\n", mlx);

// 	free(mlx);
#ifdef DEBUG
	printf("debug mode\n");
#endif

	return 0;
}
