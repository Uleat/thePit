#pragma once


#include "common_types.h"


namespace skills {

	enum SkillTypes {
		SkillNone = 0,
		// primary skills
		SkillMelee,
		SkillRanged,
		// secondary skills
		// tertiary skills
		skill_types_count_
	};

	inline bool IsValidSkillType(SkillTypes skill_type) { return (skill_type > SkillNone && skill_type < skill_types_count_); }
	inline SkillTypes ValidateSkillType(SkillTypes skill_type) { return ((skill_type > SkillNone && skill_type < skill_types_count_) ? skill_type : SkillNone); }

	const SkillTypes SkillParent[skill_types_count_] = {
		SkillNone, // SkillNone = ..
		SkillNone, // SkillMelee = ..
		SkillNone // SkillRanged = ..
	};

} // namespace skills

#pragma pack(1)

namespace formats {

	struct SkillDataArray : CommonUseArray<skill_t, skills::skill_types_count_> { };

	struct SkillData {
		SkillDataArray base_skill_data_;
		SkillDataArray advancement_skill_data_;
		SkillDataArray equipment_skill_data_;
		SkillDataArray bonus_skill_data_;
		SkillDataArray skill_data_limits;
	};

} // namespace formats

#pragma pack()

//namespace skills {
//
//} // namespace skills

namespace profiles {

	struct SkillAttributes {
		SkillAttributes() { }
		SkillAttributes(const SkillAttributes& copy) : skill_data_(copy.skill_data_) { }
		SkillAttributes(const formats::SkillData& copy) : skill_data_(copy) { }
		SkillAttributes(
			const formats::SkillDataArray& copy_base_skill_data,
			const formats::SkillDataArray& copy_advancement_skill_data,
			const formats::SkillDataArray& copy_equipment_skill_data,
			const formats::SkillDataArray& copy_bonus_skill_data,
			const formats::SkillDataArray& copy_skill_data_limits
		) {
			skill_data_.base_skill_data_ = copy_base_skill_data;
			skill_data_.advancement_skill_data_ = copy_advancement_skill_data;
			skill_data_.equipment_skill_data_ = copy_equipment_skill_data;
			skill_data_.bonus_skill_data_ = copy_bonus_skill_data;
			skill_data_.skill_data_limits = copy_skill_data_limits;
		}
		virtual ~SkillAttributes() { }

		inline const formats::SkillData& GetSkillData() const { return skill_data_; }
		
		inline const formats::SkillDataArray& GetBaseSkillData() const { return skill_data_.base_skill_data_; }
		inline const formats::SkillDataArray& GetAdvancementSkillData() const { return skill_data_.advancement_skill_data_; }
		inline const formats::SkillDataArray& GetBonusSkillData() const { return skill_data_.bonus_skill_data_; }

		inline skill_t GetBaseSkillValue(skills::SkillTypes skill_type) const {
			
		}
		inline skill_t GetAdvancementSkillValue(skills::SkillTypes skill_type) const {

		}
		inline skill_t GetBonusSkillValue(skills::SkillTypes skill_type) const {

		}

	protected:

		formats::SkillData skill_data_;

	private:

	};

} // namespace profiles
