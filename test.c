/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:18:40 by jcohen            #+#    #+#             */
/*   Updated: 2024/06/04 17:20:07 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	func(void)
{
	static int	i = 0;

	i++;
	printf("La fonction a été appelée %d fois\n", i);
}

int	main(void)
{
	func();
	func();
	func();
	return (0);
}