/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isxdigit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 15:17:56 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/28 11:42:42 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isxdigit(int c)
{
	return (ft_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}
