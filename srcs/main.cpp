/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:32:07 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/05 13:04:03 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tree.hpp"

int	main(void)
{
	Grid	grid(80,50);
	Vec2	root(40,0);
	char	c;
	
	while (1)
	{
		Tree	tree(grid, root);

		tree.draw();
		grid.out();
		c = std::cin.get();
		if (c != '\n')
			break ;
		grid.clear();
	}
}
