/*
 * xml2jsonparser.hpp
 *
 *  Created on: 20.7.2012
 *      Author: akin
 */

#ifndef XML2JSONPARSER_HPP_
#define XML2JSONPARSER_HPP_

#include <json>
#include <rapidxml/rapidxml.hpp>

namespace xml2json
{

class Parser
{
public:
	Parser();
	virtual ~Parser();

	void convert( rapidxml::xml_node<>& source , Json::Value& target );
};

} // namespace xml2json 
#endif // XML2JSONPARSER_HPP_ 
