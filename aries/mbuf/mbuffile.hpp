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
	int fd;
	int filesize;
	void *data;
public:
	File( const std::string& path , int filesize  );
	virtual ~File();

	virtual Size size() const;
	virtual void *at( Size position ) const;
	virtual void close();
	virtual bool ok();
};

} // namespace mbuf
#endif // MBUFFILE_HPP_
