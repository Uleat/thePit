#pragma once


#include "actor_mobile.h"
#include "../common/profile_skills.h"
#include "../common/profile_stats.h"


namespace actors {

	class Combatant :
		public Mobile,
		public profiles::SkillAttributes,
		public profiles::StatAttributes {

	public:
		// inheritance checks
		inline virtual bool IsCombatant() const { return true; }

	protected:

	private:

	};

} // namespace actors
