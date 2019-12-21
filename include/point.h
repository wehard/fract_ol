/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:48:55 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/16 11:54:49 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct	s_p2f
{
	float		x;
	float		y;
}				t_p2f;

typedef struct	s_p2i
{
	int			x;
	int			y;
}				t_p2i;

t_p2f			make_p2f(float x, float y);
t_p2i			make_p2i(int x, int y);

#endif
