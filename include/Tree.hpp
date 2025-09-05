/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:39:57 by hle-hena          #+#    #+#             */
/*   Updated: 2025/09/05 17:29:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include "Leaves.hpp"
# include "Grid.hpp"
# include "Vec2.hpp"

class	Tree
{
	private:
		Tree(void);

		Vec2	getEndCoo(Vec2 start, float len, float theta) const;
		void	drawBranch(Vec2 startCoo, int layer, float len,
			float width, float theta) const;
		void	drawBranchChild(Vec2 startCoo, int layer, float len,
			float width, float theta) const;
		void	drawBox(const std::string soilSet, float width) const;

		Grid				&_grid;
		Vec2				&_root;
		const int			_initialLen;
		const int			_numOfLayers;
		const std::string	_branchChar;

	public:
		Tree(Grid &grid, Vec2 &root);
		Tree(Grid &grid, Vec2 &root, int initialLen, int numOfLayers);
		Tree(const Tree &other);
		Tree &operator=(const Tree &other);
		~Tree(void);

		void	draw(void) const;
};

#endif