/*
 * mbuffile.hpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#ifndef MBUFFILE_HPP_
#define MBUFFILE_HPP_

#include "mbufbuffer.hpp"
#include <string>

namespace mbuf
{

class File : public Buffer
{
private:
	std::string path;
	std::size_t filesize;
	int fd;
	void *data;
	Mode mode;
public:
	File( const std::string& path = "" , std::size_t filesize = 0 );
	virtual ~File();

	File& setFile( const std::string& path );
	File& setSize( std::size_t filesize );

	virtual std::size_t size() const;

	virtual void *retain( std::size_t position , std::size_t count );
	virtual void release( void *buffer );

	virtual bool open( Mode mode );
	virtual void close();
	virtual bool ok() const;
	virtual Mode getMode() const;
};

} // namespace mbuf
#endif // MBUFFILE_HPP_
