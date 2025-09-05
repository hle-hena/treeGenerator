/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:00:04 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/05 12:09:05 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_HPP
# define GRID_HPP

# include <iostream>
# include "Vec2.hpp"

class	Grid
{
	private:
		void	drawLow(Vec2 start, Vec2 end,
			const std::string &charSet, char branch);
		void	drawHigh(Vec2 start, Vec2 end,
			const std::string &charSet, char branch);

		std::string	*_grid;

	public:
		Grid(void);
		Grid(const int initWidth, const int initHeight);
		Grid(const Grid &other);
		Grid &operator=(const Grid &other);
		~Grid(void);

		void	placeChar(Vec2 &pos, char toPrint, bool isBranch);
		void	drawLine(Vec2 start, Vec2 end,
			const std::string &charset);
		void	out(void) const;
		void	clear(void);

		int			width;
		int			height;
};

#endif