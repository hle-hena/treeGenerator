/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Leaves.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:38:37 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/05 11:57:14 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAVES_HPP
# define LEAVES_HPP

# include <iostream>
# include "Vec2.hpp"
# include "Grid.hpp"

class	Leaves
{
	private:
		Leaves(void);

		Grid				&_grid;
		const Vec2			_branchCoo;
		const int			_nbLeaves;
		const int			_leafLen;
		const std::string	_leavesChar;

	public:
		Leaves(Grid &grid, const Vec2 &branchCoo);
		Leaves(const Leaves &other);
		Leaves &operator=(const Leaves &other);
		~Leaves(void);

		void	draw(void);
};

#endif