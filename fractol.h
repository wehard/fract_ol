/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:29:31 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/16 17:29:13 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIN_W 800
# define WIN_H 600
# define MAX_ITER 256
# define ESC 53

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

typedef struct		s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_frame_buffer	*frame_buffer;
	float			zoom_level;
	int				mouse_x;
	int				mouse_y;
}					t_mlx_data;

typedef struct		s_complex
{
	double			r;
	double			i;
}					t_complex;

void				plot_mandelbrot(t_mlx_data *mlx_data, float width, float height);
void				plot_julia(t_mlx_data *mlx_data, float width, float height);
t_complex			make_complex(double r, double i);

t_frame_buffer		*create_frame_buffer(t_mlx_data *mlx_data);
void				frame_buffer_set(t_frame_buffer *fb, int x, int y, int c);
void				clear_frame_buffer(t_frame_buffer *fb);

#endif
