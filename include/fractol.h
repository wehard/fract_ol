/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:29:31 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/21 22:48:02 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "point.h"

# define WIN_W 1280
# define WIN_H 720
# define NUM_THREADS 8
# define MAX_ITER 255
# define FRAC_JULIA 0
# define FRAC_MANDELBROT 1
# define FRAC_POOP 2

typedef struct		s_frame_buffer
{
	void			*img;
	char			*d_addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				w;
	int				h;
}					t_frame_buffer;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx;

typedef struct		s_env
{
	t_mlx			*mlx;
	t_frame_buffer	*frame_buffer;
	int				thread_index;
	int				**thread_data;
	int				thread_range_start;
	int				thread_range_end;
	int				width;
	int				height;
	int				mouse_x;
	int				mouse_y;
	int				fractal_type;
	double			zoom;
	double			move_x;
	double			move_y;
}					t_env;

typedef struct		s_complex
{
	double			r;
	double			i;
}					t_complex;

typedef void		*(*t_fractal_func)(void*);

void 				plot_fractal(t_env *env, int width, int height);
void				*plot_mandelbrot(void *env_ptr);
void				*plot_julia(void *env_ptr);
t_complex			make_complex(double r, double i);

t_frame_buffer		*create_frame_buffer(t_env *env);
void				frame_buffer_set(t_frame_buffer *fb, int x, int y, int c);
void				clear_frame_buffer(t_frame_buffer *fb);

void				setup_controls(t_env *env);
int 				close(void *param);
int 				expose(void *param);
int 				mouse_press(int button, int x, int y, void *param);
int 				mouse_move(int x, int y, void *param);
int					key_press(int key, void *param);

int					get_color(int i);

#endif
