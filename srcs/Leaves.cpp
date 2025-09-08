/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Leaves.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:50:21 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/08 13:39:25 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Leaves.hpp"

	/* ****************************************************************** */
/*                                                                            */
/*    Constructor and desctructor of the Leaves class.                        */
/*                                                                            */
	/* ****************************************************************** */

Leaves::Leaves(Grid &grid, const Vec2 &branchCoo) :
	_grid(grid),
	_branchCoo(branchCoo),
	_nbLeaves(4),
	_leafLen(4),
	_leavesChar("&%#@")
{
}

Leaves::Leaves(const Leaves &other) :
	_grid(other._grid),
	_branchCoo(other._branchCoo),
	_nbLeaves(4),
	_leafLen(4),
	_leavesChar("&%#@")
{
}

Leaves &Leaves::operator=(const Leaves &other)
{
	(void)other;
	return (*this);
}

Leaves::~Leaves(void)
{
}



	/* ****************************************************************** */
/*                                                                            */
/*    Methods of the Leaves class.                                            */
/*                                                                            */
	/* ****************************************************************** */

void	Leaves::draw(void)
{
	Vec2	g(0, -1);
	int		leafLen;

	for (int i = 0; i < _nbLeaves; i++)
	{
		Vec2	displacement(randFloatRange(-1, 1), randFloatRange(-1, 0));
		Vec2	leafPos(_branchCoo);

		leafLen = randIntRange(2, 3);
		leafPos.y += 1;
		displacement.normalize();
		for (int i = 0; i < leafLen; i++)
		{
			leafPos += displacement;
			char	toPrint = _leavesChar[randIntRange(0, _leavesChar.size() - 1)];

			_grid.placeChar(leafPos, toPrint, false);
			displacement += g * (i / leafLen);
		}
	}
}
