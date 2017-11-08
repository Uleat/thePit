#pragma once


#include "common_types.h"


namespace classes {

	enum ClassTypes : class_t {
		class_types_none_ = CLASS_T_MAX,
		ClassWarrior = CLASS_T_MIN,
		Class1,
		class_types_player_begin_ = ClassWarrior,
		class_types_player_end_ = ClassWarrior,
		class_types_nonplayer_begin_ = Class1,
		class_types_nonplayer_end_ = Class1,
		class_types_begin_ = ClassWarrior,
		class_types_end_ = Class1,
		class_types_count_
	};

	inline bool IsClassTypeBounded(const ClassTypes r) { return (r >= class_types_begin_ && r <= class_types_end_); }
	inline bool IsPlayerClass(const ClassTypes r) { return (r >= class_types_player_begin_ && r <= class_types_player_end_); }
	inline bool IsNonPlayerClass(const ClassTypes r) { return (r >= class_types_nonplayer_begin_ && r <= class_types_nonplayer_end_); }

	enum ClassBits : bitmask64_t {
		class_bits_none_ = BITMASK64_T_NONE,
		class_bits_all_ = BITMASK64_T_ALL
	};

} // namespace classes

#pragma pack(1)

namespace formats {

	struct ClassData {
		classes::ClassTypes ClassType;
		classes::ClassTypes PseudoClassType;
	};

} // namespace formats

#pragma pack()
