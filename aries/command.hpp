/*
 * command.hpp
 *
 *  Created on: 4.10.2012
 *      Author: akin
 */

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

namespace hydra {

class Command
{
public:
	virtual ~Command() {}
	virtual void preProcess() = 0;
	virtual void process() = 0;
	virtual void postProcess() = 0;
};

} // hydra

#endif // COMMAND_HPP_
