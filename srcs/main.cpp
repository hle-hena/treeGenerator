/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:32:07 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/08 09:40:26 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tree.hpp"

int	main(int ac, char **av)
{
	if (ac == 1)
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
	else
	{
		Grid			grid(800, 500);
		Vec2			root(400, 0);
		Tree			tree(grid, root, 100, 17);
		std::ofstream	out(av[1]);

		tree.draw();
		grid.out(out);
		out.close();
	}
}
