#pragma once


#include "actor_world.h"


namespace actors {

	class Mobile :
		public World,
		public profiles::SpatialDynamicAttributes {

	public:
		// inheritance checks
		inline virtual bool IsMobile() const { return true; }

	protected:

	private:

	};

} // namespace actors
