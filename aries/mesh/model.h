/*
 * model.h
 *
 *  Created on: 9.9.2012
 *      Author: akin
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <orion>

namespace orion {
namespace mesh {

class Model
{
private:
	struct Vertex {
		glm::vec3 position;
		glm::vec2 coordinate;
	};

	std::vector<Vertex> vertexes;
	std::vector<uint16> indexes;
public:
	Model();
	virtual ~Model();
};

} // namespace mesh
} // namespace orion

#endif // MODEL_H_
