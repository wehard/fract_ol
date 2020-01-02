/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 12:55:44 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/02 13:43:36 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "point.h"

# define WIN_W 1200
# define WIN_H 800
# define NUM_THREADS 64
# define NUM_PALETTE 3
# define MAX_ITER 255
# define FRAC_JULIA 1
# define FRAC_MANDELBROT 2
# define FRAC_BURNING_SHIP 3
# define UI_TEXT 0xFFFFFF
# define UI_BG 0x202020
# define UI_FG 0x303030
# define FRAC_JULIA_STR "   JULIA"
# define FRAC_MANDEL_STR " MANDELBROT"
# define FRAC_BURNING_STR "BURNING SHIP"

typedef struct		s_mlx_img
{
	void			*img;
	char			*d_addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				w;
	int				h;
}					t_mlx_img;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx;

typedef struct		s_ui
{
	t_mlx_img		*img;
	t_p2i			pos;
}					t_ui;

typedef struct		s_env
{
	t_mlx			*mlx;
	t_ui			*ui;
	t_mlx_img		*fractal_img;
	int				thread_index;
	int				**thread_data;
	int				thread_range_start;
	int				thread_range_end;
	int				width;
	int				height;
	int				mouse_x;
	int				mouse_y;
	int				fractal_type;
	char			*fractal_name;
	double			zoom;
	double			move_x;
	double			move_y;
	int				color_palette;
	int				free_julia;
	int				iterations;
}					t_env;

typedef struct		s_complex
{
	double			r;
	double			i;
}					t_complex;

typedef void		*(*t_fractal_func)(void*);

t_env				*init_env(char *title, int w, int h);
void				del_env(t_env *env);

char				*get_fractal_name(int i);

void				plot_fractal(t_env *env);
void				*plot_julia(void *env_ptr);
void				*plot_mandelbrot(void *env_ptr);
void				*plot_burning_ship(void *env_ptr);
t_complex			make_complex(double r, double i);

t_mlx_img			*create_mlx_image(t_env *env, int width, int height);
void				clear_mlx_img(t_mlx_img *img);
void				put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c);
void				draw_rect(t_mlx_img *img, t_p2i pos, t_p2i size, int color);

void				setup_controls(t_env *env);
int					close(void *param);
int					expose(void *param);
int					mouse_press(int button, int x, int y, void *param);
int					mouse_move(int x, int y, void *param);
int					key_press(int key, void *param);

int					get_color(int i, int iterations, int palette);

void				draw_ui(t_env *env);
int					ui_init(t_env *env);
#endif
