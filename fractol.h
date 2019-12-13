/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:29:31 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/13 17:41:58 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define ESC 53

typedef struct		s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx_data;

void	ft_mandelbrot(float left, float top, float width, float height);

#endif
