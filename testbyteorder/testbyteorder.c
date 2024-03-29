/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testbyteorder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:35:26 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/29 03:13:46 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>

int	main(void)
{	
	uint16_t	x;

	x = 0x0001;
	printf("%s-endian\n", *((uint8_t *) &x) ? "little" : "big");
	return (0);
}
