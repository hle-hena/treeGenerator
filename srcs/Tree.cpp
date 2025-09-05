/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:50:37 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/05 13:00:21 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tree.hpp"

	/* ****************************************************************** */
/*                                                                            */
/*    Constructor and desctructor of the Tree class.                          */
/*                                                                            */
	/* ****************************************************************** */

Tree::Tree(Grid &grid, Vec2 &root) :
	_grid(grid),
	_root(root),
	_initialLen(15),
	_numOfLayers(10),
	_branchChar("~;:=")
{
}

Tree::Tree(const Tree &other) :
	_grid(other._grid),
	_root(other._root),
	_initialLen(15),
	_numOfLayers(10),
	_branchChar(other._branchChar)
{
}

Tree &Tree::operator=(const Tree &other)
{
	(void)other;
	return (*this);
}

Tree::~Tree(void)
{
}



	/* ****************************************************************** */
/*                                                                            */
/*    Methods of the Tree class.                                              */
/*                                                                            */
	/* ****************************************************************** */

Vec2	Tree::getEndCoo(Vec2 start, float len, float theta) const
{
	start += Vec2(len * sin(theta), len * cos(theta));
	return (start);
}

void	Tree::draw(void) const
{
	float	initialTheta = randNormal(0, 0.1f);

	drawBox("_____~");
	drawBranch(_root, 1, _initialLen,
		3, initialTheta);
}

void	Tree::drawBox(const std::string soilSet) const
{
	Vec2	pos(_root);
	int		boxWidth = std::max<int>(21, _grid.width * 0.5);
	int		endBox = pos.x + boxWidth / 2;
	char	toPrint;

	boxWidth += boxWidth % 2;
	pos.x -= boxWidth / 2;
	while (pos.x < endBox)
	{
		if (fabs(pos.x - _root.x + 2) < 0.2)
			toPrint = '/';
		else if (fabs(pos.x - _root.x - 2) < 0.2)
			toPrint = '\\';
		else
			toPrint = soilSet[randIntRange(0, soilSet.size() - 1)];
		_grid.placeChar(pos, toPrint, false);
		pos.x += 1;
	}
}

void	Tree::drawBranch(Vec2 startCoo, int layer, float len, float width,
	float theta) const
{
	if (layer >= _numOfLayers)
	{
		Leaves	leaves(_grid, startCoo);
		leaves.draw();
		return ;
	}
	Vec2	endCoo(startCoo);
	Vec2	normal(0, 0);

	endCoo = getEndCoo(startCoo, len, theta);
	_grid.drawLine(startCoo, endCoo, _branchChar);
	if (layer == 1)
	{
		startCoo.x += 1;
		_grid.drawLine(startCoo, endCoo, _branchChar);
		startCoo.x -= 2;
		_grid.drawLine(startCoo, endCoo, _branchChar);
		startCoo.x += 1;
	}
	drawBranchChild(startCoo, layer, len, width, theta);
}

void	Tree::drawBranchChild(Vec2 startCoo, int layer, float len, float width,
	float theta) const
{
	int		sign = (0.5 - randIntRange(0, 1)) * 2;
	int		nbBranch = round(randNormal(2.5, 0.5));
	float	step = nbBranch == 0 ? 0 : len / (float)nbBranch;
	float	newWidth = width == 1 ? width : width - 1;
	float	newLen = len * 0.75;
	float	newTheta;

	for (int i = 0; i < nbBranch; i++)
	{
		do
			newTheta = theta +
				static_cast<float>(sign) * randNormal(0.498132, randFloatRange(0.15, 0.3));
		while (fabs(newTheta) > 2 || fabs(newTheta) < 0.3);
		drawBranch(getEndCoo(startCoo, (i + 1) * step, theta),
			layer + 1, newLen, newWidth * (newTheta / 3), newTheta);
		sign *= -1;
	}
}
