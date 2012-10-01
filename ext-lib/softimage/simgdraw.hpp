/*
 * simgdraw.hpp
 *
 *  Created on: 30.9.2012
 *      Author: akin
 */

#ifndef SIMGDRAW_HPP_
#define SIMGDRAW_HPP_

#include <glm/glm>
#include <stdtypes>
#include <colortypes>
#include <mbuf/mbufbuffer.hpp>
#include <geometry/rectangle>

namespace simg
{

class Draw
{
private:
	glm::ivec2& resolution;
	Color::Type mode;
	mbuf::Iterator iterator;
public:
	Draw( const glm::ivec2& resolution , Color::Type mode , mbuf::Iterator& iterator );
	~Draw();

	void draw( const glm::ivec2& position , const glm::ivec2& res , mbuf::Iterator iterator );
};

} // namespace simg
#endif // SIMGDRAW_HPP_
