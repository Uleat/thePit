#pragma once


#include "common_types.h"


namespace stats {

	enum StatTypes : uword_t {
		stat_types_none_ = UWORD_T_MAX,
		// vitals
		StatHealth = UWORD_T_MIN,
		StatStamina,
		StatPsi,
		// primary attributes
		StatStrength,
		StatDexterity,
		StatAgility,
		StatWisdom,
		StatIntelligence,
		StatConstitution,
		StatCharisma,
		// secondary attributes
		StatReflex,
		StatFortitude,
		StatWill,
		StatConcentration,
		StatPersuasion,
		// resists
		StatHeat,
		StatCold,
		StatPoison,
		StatDisease,
		StatPsionic,
		StatEnergy,
		stat_types_begin_ = StatHealth,
		stat_types_end_ = StatEnergy,
		stat_types_count_
	};

	inline bool IsStatTypeBound(StatTypes r) { return (r >= stat_types_begin_ && r <= stat_types_end_); }

} // namespace stats

#pragma pack(1)

namespace formats {

	struct StatDataArray : CommonUseArray<stat_value_t, stats::stat_types_count_> { };

	struct StatData {
		formats::StatDataArray base_stat_data_;
	};

} // namespace formats

#pragma pack()

namespace stats {

} // namespace stats

namespace profiles {

	struct StatAttributes {

	};

} // namespace profiles
