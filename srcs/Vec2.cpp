/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec2.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:59:37 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/05 11:14:04 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec2.hpp"

	/* ****************************************************************** */
/*                                                                            */
/*    Constructor and desctructor of the Vec2 class.                          */
/*                                                                            */
	/* ****************************************************************** */

Vec2::Vec2(void) :
	x(0),
	y(0)
{
}

Vec2::Vec2(float initX, float initY) :
	x(initX),
	y(initY)
{
}

Vec2::Vec2(const Vec2 &other) :
	x(other.x),
	y(other.y)
{
}

Vec2 &Vec2::operator=(const Vec2 &other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
	}
	return (*this);
}

Vec2::~Vec2(void)
{
}



	/* ****************************************************************** */
/*                                                                            */
/*    Methods of the Vec2 class.                                              */
/*                                                                            */
	/* ****************************************************************** */

void	Vec2::normalize(void)
{
	float	magnitude = std::sqrt(x * x + y * y);

	x /= magnitude;
	y /= magnitude;
}

Vec2	&Vec2::operator+=(const Vec2 &other)
{
	x += other.x;
	y += other.y;
	return (*this);
}

Vec2	&Vec2::operator-=(const Vec2 &other)
{
	x -= other.x;
	y -= other.y;
	return (*this);
}

Vec2	Vec2::operator*(const float &magnitude)
{
	Vec2	result(*this);

	result.x *= magnitude;
	result.y *= magnitude;
	return (result);
}



	/* ****************************************************************** */
/*                                                                            */
/*    Functions for random floats.                                            */
/*                                                                            */
	/* ****************************************************************** */

float	randFloat(void)
{
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}

float	randFloatRange(float min, float max)
{
	return (min + (max - min) * randFloat());
}

int	randInt(void)
{
	return (rand());
}

int	randIntRange(int min, int max)
{
	return (min + randInt() % (max - min + 1));
}

float	randNormal(double mean, double stdDeviation)
{
	static bool		hasSpare = false;
	static double	spare;
	double			u,v,s;

	if (hasSpare)
	{
		hasSpare = false;
		return (mean + stdDeviation * spare);
	}
	hasSpare = true;
	do
	{
		u = (static_cast<double>(rand()) / static_cast<double>(RAND_MAX))
			* 2.0f - 1.0f;
		v = (static_cast<double>(rand()) / static_cast<double>(RAND_MAX))
			* 2.0f - 1.0f;
		s = u * u + v * v;
	} while (s >= 1.0 || s == 0.0);
	s = sqrt(-2.0 * log(s) / s);
	spare = v * s;
	return (mean + stdDeviation * (u * s));
}
