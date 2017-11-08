#include "profile_item_data.h"


item::UpgradeSlots item::ConvertUpgradeTypeToSlot(const UpgradeTypes r) {
	if (r < upgrade_types_none_ || r >= upgrade_types_count_)
		return item::upgrade_slots_inactive_;

	return UpgradeTypesToSlots[r];
}
