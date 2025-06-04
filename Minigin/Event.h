#pragma once
#include "Utils.h"

namespace dae
{

struct Event
{
	const unsigned int id;

	explicit Event(unsigned int eventId) : id{ eventId } {};
};

}

