#pragma once


#include "common_types.h"


namespace races {

	enum RaceTypes : race_t {
		race_types_none_ = RACE_T_MAX,
		RaceHuman = RACE_T_MIN,
		Race1,
		race_types_player_begin_ = RaceHuman,
		race_types_player_end_ = RaceHuman,
		race_types_nonplayer_begin_ = Race1,
		race_types_nonplayer_end_ = Race1,
		race_types_begin_ = RaceHuman,
		race_types_end_ = Race1,
		race_types_count_
	};

	inline bool IsRaceTypeBounded(const RaceTypes r) { return (r >= race_types_begin_ && r <= race_types_end_); }
	inline bool IsPlayerRace(const RaceTypes r) { return (r >= race_types_player_begin_ && r <= race_types_player_end_); }
	inline bool IsNonPlayerRace(const RaceTypes r) { return (r >= race_types_nonplayer_begin_ && r <= race_types_nonplayer_end_); }

	enum RaceBits : bitmask64_t {
		race_bits_none_ = BITMASK64_T_NONE,
		race_bits_all_ = BITMASK64_T_ALL
	};

} // namespace races

#pragma pack(1)

namespace formats {

	struct RaceData {
		races::RaceTypes RaceType;
		races::RaceTypes PseudoRaceType;
	};

} // namespace formats

#pragma pack()
