#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx_linux/mlx.h"

# ifndef HEIGHT
#  define HEIGHT 800
# endif

# ifndef WIDTH
#  define WIDTH 640
# endif

typedef struct s_img
{
	void	*img;
	char	*pixels;
	int	bpp;
	int	line_len;
	int	endian;
}	t_img;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

void	init(t_mlx *game);
void	event_listening(t_mlx *game);
int	handle_key(int keysym, t_mlx *game);
int	handle_mouse(int button, int x, int y, t_mlx *game);
int	handle_closing(t_mlx *game);

void	rendering(t_mlx *game);
void	put_pixels(int x, int y, t_img *img, int color);

void	malloc_error(void);
#endif
