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

# include "libft.h"
# include "point.h"

# define WIN_W 1280
# define WIN_H 720
# define NUM_THREADS 8
# define NUM_PALETTE 3
# define MAX_ITER 255
# define FRAC_JULIA 0
# define FRAC_MANDELBROT 1
# define FRAC_POOP 2
# define HUD_TEXT 0xFFFFFF
# define HUD_BG 0x404040
# define HUD_FG 0x606060
# define HUD_BTN_S 0x8888FF
# define HUD_BTN 0x1010FF

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

typedef struct		s_ui_button
{
	t_p2i			pos;
	t_p2i			size;
	char			*label;
	int				selected;
}					t_ui_button;

typedef struct		s_env
{
	t_mlx			*mlx;
	t_mlx_img		*fractal_img;
	t_mlx_img		*hud_img;
	int				thread_index;
	int				**thread_data;
	int				thread_range_start;
	int				thread_range_end;
	int				width;
	int				height;
	t_ui_button		*ui_buttons;
	int				mouse_x;
	int				mouse_y;
	int				fractal_type;
	double			zoom;
	double			move_x;
	double			move_y;
	int				color_palette;
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

t_mlx_img			*create_mlx_image(t_env *env, int width, int height);
void				clear_mlx_img(t_mlx_img *img);
void				put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c);

void				setup_controls(t_env *env);
int 				close(void *param);
int 				expose(void *param);
int 				mouse_press(int button, int x, int y, void *param);
int 				mouse_move(int x, int y, void *param);
int					key_press(int key, void *param);

int					get_color(int i, int palette);

void				draw_hud(t_env *env);
int					create_ui_buttons(t_env *env);

#endif
