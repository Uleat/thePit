#pragma once


#include "../common/profile_spatial.h"


namespace managers {

	class Actor;

} // namespace managers

namespace actors {

	class World :
		public profiles::SpatialOriginAttributes {

		friend class managers::Actor;

	public:

		// inheritance checks
		inline bool IsWorld() const { return true; }

		inline virtual bool IsCombatant() const { return false; }
		inline virtual bool IsMobile() const { return false; }
		inline virtual bool IsStatic() const { return false; }


		uint32_t GetActorID() { return actor_id_; }
		time_t GetCreationTimestamp() { return creation_timestamp_; }

		// processing
		virtual bool Process() { return false; }
		virtual bool Save() { return true; }

	protected:

		void ForceActorID(uint32_t new_actor_id) { actor_id_ = new_actor_id; }
		void ForceCreationTimestamp(time_t new_creation_timestamp) { creation_timestamp_ = new_creation_timestamp; }

	private:

		uint32_t actor_id_;
		time_t creation_timestamp_;
	};

} // namespace actors
