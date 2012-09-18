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
	File( const std::string& path , std::size_t filesize  );
	virtual ~File();

	virtual std::size_t size() const;
	virtual void *at( std::size_t position ) const;
	virtual bool open( Mode mode );
	virtual void close();
	virtual bool ok() const;
	virtual Mode getMode() const;
};

} // namespace mbuf
#endif // MBUFFILE_HPP_
