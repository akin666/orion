/*
 * RenderSetting.hpp
 *
 *  Created on: 19.6.2012
 *      Author: akin
 */

#ifndef RENDERSETTING_HPP_
#define RENDERSETTING_HPP_

#include <orion>

namespace orion {

class RenderSetting {
public:
	RenderSetting();
	virtual ~RenderSetting();
};

typedef std::vector<RenderSetting> RenderSettingSet;

} // namespace orion
#endif // RENDERSETTING_HPP_
