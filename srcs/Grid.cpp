/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:32:24 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/05 17:47:10 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Grid.hpp"

	/* ****************************************************************** */
/*                                                                            */
/*    Constructor and desctructor of the Grid class.                          */
/*                                                                            */
	/* ****************************************************************** */

Grid::Grid(void) :
	_grid(new std::string[100]),
	width(100),
	height(100)
{
	srand(static_cast<unsigned>(std::time(0)));
	for (int i = 0; i < height; i++)
		_grid[i] = std::string(width, ' ');
}

Grid::Grid(const int initWidth, const int initHeight) :
	_grid(new std::string[initHeight]),
	width(initWidth),
	height(initHeight)
{
	srand(static_cast<unsigned>(std::time(0)));
	for (int i = 0; i < height; i++)
		_grid[i] = std::string(width, ' ');
}

Grid::Grid(const Grid &other) :
	_grid(new std::string[other.height]),
	width(other.width),
	height(other.height)
{
	srand(static_cast<unsigned>(std::time(0)));
	for (int i = 0; i < height; i++)
		_grid[i] = std::string(other._grid[i]);
}

Grid &Grid::operator=(const Grid &other)
{
	if (this != &other)
	{
		srand(static_cast<unsigned>(std::time(0)));
		if (_grid)
			delete[] _grid;
		width = other.width;
		height = other.height;
		_grid = new std::string[other.height];
		for (int i = 0; i < height; i++)
			_grid[i] = std::string(other._grid[i]);
	}
	return (*this);
}

Grid::~Grid(void)
{
	delete[] _grid;
}



	/* ****************************************************************** */
/*                                                                            */
/*    Methods of the Grid class.                                              */
/*                                                                            */
	/* ****************************************************************** */

void	Grid::placeChar(Vec2 &pos, char toPrint, bool isBranch)
{
	static std::string	charSet("&%#@");

	if (pos.x < 0 || pos.x >= width - 1 || pos.y < 0 || pos.y >= height - 1)
		return ;
	if (isBranch)
	{
		if (charSet.find((_grid[static_cast<int>(round(pos.y))]
		[static_cast<int>(round(pos.x))])) != std::string::npos
			&& randIntRange(0, 3))
			return ;
	}
	_grid[static_cast<int>(round(pos.y))]
		[static_cast<int>(round(pos.x))] = toPrint;
}

float	lerp(float a, float b, float percent)
{
	return (a + (b - a) * percent);
}

void	Grid::placeWideChar(Vec2 &pos, Vec2 &normal, float width,
	const std::string &charSet, char branch)
{
	Vec2	start(pos);
	Vec2	end(pos);

	if (width <= 1.5)
	{
		int	rand = randIntRange(0, 10);
		placeChar(pos,
			charSet[randIntRange(0, charSet.size() - 1)] * (rand == 0)
			+ branch * (rand != 0), true);
		return ;
	}
	start -= normal * (width / 2);
	end += normal * (width / 2);
	start.x = round(start.x);
	start.y = round(start.y);
	end.x = round(end.x);
	end.y = round(end.y);
	if (fabs(end.y - start.y) < fabs(end.x - start.x))
	{
		if (start.x > end.x)
			drawLow(end, start, normal, -1, charSet, branch);
		else
			drawLow(start, end, normal, -1, charSet, branch);
	}
	else
	{
		if (start.y > end.y)
			drawHigh(end, start, normal, -1, charSet, branch);
		else
			drawHigh(start, end, normal, -1, charSet, branch);
	}
}

void	Grid::drawLow(Vec2 start, Vec2 end, Vec2 &normal, float width,
	const std::string &charSet, char branch)
{
	Vec2	pos(0, 0);
	int		dx = end.x - start.x;
	int		dy = end.y - start.y;
	int		yi = dy < 0 ? -1 : 1;
	int		error;
	int		y;

	dy = abs(dy);
	error = (2 * dy) - dx;
	y = start.y;
	for (int x = start.x; x <= end.x; x++)
	{
		pos.x = x;
		pos.y = y;
		placeWideChar(pos, normal,
			lerp(width, width * 0.75,
				static_cast<float>(x - start.x) / static_cast<float>(end.x - start.x)),
			charSet, branch);
		if (error > 0)
		{
			y += yi;
			error += 2 * (dy - dx);
		}
		else
			error += 2 * dy;
	}
}

void	Grid::drawHigh(Vec2 start, Vec2 end, Vec2 &normal, float width,
	const std::string &charSet, char branch)
{
	Vec2	pos(0, 0);
	int		dx = end.x - start.x;
	int		dy = end.y - start.y;
	int		xi = dx < 0 ? -1 : 1;
	int		error;
	int		x;

	dx = abs(dx);
	error = (2 * dx) - dy;
	x = start.x;
	for (int y = start.y; y <= end.y; y++)
	{
		pos.x = x;
		pos.y = y;
		placeWideChar(pos, normal,
			lerp(width, width * 0.75,
				static_cast<float>(y - start.y) / static_cast<float>(end.y - start.y)),
			charSet, branch);
		if (error > 0)
		{
			x += xi;
			error += 2 * (dx - dy);
		}
		else
			error += 2 * dx;
	}
}

void	Grid::drawDisc(Vec2 center, float radius,
	const std::string &charSet, char branch)
{
	int		r = (int)std::ceil(radius);
	int		r2 = r * r;
	Vec2	normal(0, 0);

	for (int y = -r; y <= r; y++)
	{
		for (int x = -r; x <= r; x++)
		{
			if (x * x + y * y <= r2)
			{
				Vec2 pos(center.x + x, center.y + y);
				placeWideChar(pos, normal, -1, charSet, branch);
			}
		}
	}
}

void	Grid::drawLine(Vec2 start, Vec2 end, Vec2 &normal, float width, const std::string &charSet)
{
	char	special_char;

	start.x = round(start.x);
	start.y = round(start.y);
	end.x = round(end.x);
	end.y = round(end.y);
	drawDisc(start, width / 2, charSet, '*');
	if (fabs(end.y - start.y) < fabs(end.x - start.x))
	{
		if (start.x > end.x)
			drawLow(end, start, normal, width, charSet, '\\');
		else
			drawLow(start, end, normal, width, charSet, '/');
	}
	else
	{
		special_char = '|';
		if (start.y > end.y)
			drawHigh(end, start, normal, width, charSet, special_char);
		else
			drawHigh(start, end, normal, width, charSet, special_char);
	}
}

void	Grid::out(void) const
{
	for (int i = 0; i < height; i++)
		std::cout << _grid[height - i - 1] << std::endl;
}

void	Grid::out(std::ofstream &out) const
{
	for (int i = 0; i < height; i++)
		out << _grid[height - i - 1] << std::endl;
}

void	Grid::clear(void)
{
	for (int i = 0; i < height; i++)
	{
		std::cout << "\001\033[1A\033[2K\r\002";
		_grid[i] = std::string(width, ' ');
	}
	std::cout << "\001\033[1A\033[2K\r\002";
}
