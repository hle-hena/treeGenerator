/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:50:37 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/08 14:10:38 by hle-hena         ###   ########.fr       */
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
	_numOfLayers(8),
	_branchChar("~;:=")
{
}

Tree::Tree(Grid &grid, Vec2 &root, int initialLen, int numOfLayers) :
	_grid(grid),
	_root(root),
	_initialLen(initialLen),
	_numOfLayers(numOfLayers),
	_branchChar("~;:=")
{
}
Tree::Tree(const Tree &other) :
	_grid(other._grid),
	_root(other._root),
	_initialLen(15),
	_numOfLayers(8),
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

	drawBox("_____~", static_cast<double>(_initialLen) / 5.0);
	drawBranch(_root, 1, _initialLen,
		static_cast<double>(_initialLen) / 5.0,
		initialTheta);
}

void	Tree::drawBox(const std::string soilSet, float width) const
{
	Vec2	pos(_root);
	char	toPrint;
	float	width_left = width;
	float	width_right = width;
	float	dif;

	while (width_left > 1 && width_right > 1)
	{
		int		boxWidth = std::max<int>(21, _grid.width * 0.5);
		int		endBox = pos.x + boxWidth / 2;

		boxWidth += boxWidth % 2;
		pos.x -= boxWidth / 2;
		while (pos.x < endBox)
		{
			dif = fabs(pos.x - _root.x);
			if (dif < width_left && pos.x < _root.x)
				toPrint = '|';
			else if (dif < width_right && pos.x > _root.x)
				toPrint = '|';
			else if (pos.y == _root.y)
				toPrint = soilSet[randIntRange(0, soilSet.size() - 1)];
			else
				toPrint = ' ';
			_grid.placeChar(pos, toPrint, false);
			pos.x += 1;
		}
		pos.y += 1;
		pos.x = _root.x;
		width_left *= randFloatRange(0.75, 0.9);
		width_right *= randFloatRange(0.75, 0.9);
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
	normal.x = -(endCoo.y - startCoo.y);
	normal.y = endCoo.x - startCoo.x;
	normal.normalize();
	_grid.drawLine(startCoo, endCoo, normal, width, _branchChar);
	drawBranchChild(startCoo, layer, len, width, theta);
}

void	Tree::drawBranchChild(Vec2 startCoo, int layer, float len, float width,
	float theta) const
{
	int		sign = (0.5 - randIntRange(0, 1)) * 2;
	int		nbBranch = round(randNormal(3, 1/3));
	float	step = nbBranch == 0 ? 0 : len / static_cast<float>(nbBranch);
	float	newWidth = width * 0.5;
	float	newLen = len * 0.75;
	float	newTheta;
	float	addTheta;

	if (nbBranch == 0)
		drawBranch(getEndCoo(startCoo, len, theta),
			_numOfLayers, len, width, theta);
	for (int i = 0; i < nbBranch; i++)
	{
		addTheta = static_cast<float>(sign) * randNormal(0.4, 0.2);
		newTheta = theta + addTheta;
		if (fabs(newTheta) > 2 || fabs(newTheta) < 0.3)
			newTheta *= exp(-powf(newTheta / 2.0f, 4.0f));
		if (newLen < 1)
			drawBranch(getEndCoo(startCoo, (i + 1) * step, theta),
				_numOfLayers, newLen, newWidth, newTheta);
		else
			drawBranch(getEndCoo(startCoo, (i + 1) * step, theta),
				layer + 1, newLen, newWidth, newTheta);
		sign *= -1;
	}
}
