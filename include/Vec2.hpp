/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec2.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:42:23 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/05 11:14:01 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHSTRUCT_HPP
# define MATHSTRUCT_HPP

# include <cmath>
# include <ctime>

class	Vec2
{
	private:
		Vec2(void);

	public:
		Vec2(float initX, float initY);
		Vec2(const Vec2 &other);
		Vec2 &operator=(const Vec2 &other);
		~Vec2(void);
		
		Vec2	&operator+=(const Vec2 &other);
		Vec2	&operator-=(const Vec2 &other);
		Vec2	operator*(const float &magnitude);

		void	normalize(void);

		float	x;
		float	y;
};

float	randFloat(void);
float	randFloatRange(float min, float max);
int		randInt(void);
int		randIntRange(int min, int max);
float	randNormal(double mean, double stdDeviation);

#endif