#pragma once
#include "IPanel.hpp"
#include "ISurface.hpp"
//interfaces class to keep it tidy.
class cInterfaces
{
public:
	ISurface* Surface;
	IPanel* Panel;
	void Start();
};