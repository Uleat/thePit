#pragma once


#include "actor_world.h"


namespace actors {

	class Static :
		public World {

	public:
		// inheritance checks
		inline virtual bool IsStatic() const { return true; }

		// spatial attributes
		inline virtual formats::SpatialOriginData& GetSpatialOriginData() { return formats::SpatialOriginData(); }

		inline virtual spatial::dimension_data_t& GetOriginDimensionData() { return spatial::dimension_data_t(); }
		inline virtual spatial::distortion_data_t& GetOriginDistortionData() { return spatial::distortion_data_t(); }
		inline virtual spatial::orientation_data_t& GetOriginOrientationData() { return spatial::orientation_data_t(); }
		inline virtual spatial::momentum_data_t& GetOriginMomentumData() { return spatial::momentum_data_t(); }
		inline virtual spatial::z_offset_data_t& GetOriginZOffsetData() { return spatial::z_offset_data_t(); }

		inline virtual spatial::ct_pair_data_t& GetCTPairData() { return spatial::ct_pair_data_t(); }

		inline virtual spatial::coordinate_data_t& GetCoordinateData() { return spatial::coordinate_data_t(); }
		inline virtual spatial::trajectory_data_t& GetTrajectoryData() { return spatial::trajectory_data_t(); }

		inline virtual void SetSpatialOriginData(const formats::SpatialOriginData& r) { return; }

		inline virtual void SetOriginDimensionData(const spatial::dimension_data_t& r) { return; }
		inline virtual void SetOriginHeight(const float r) { return; }
		inline virtual void SetOriginWidth(const float r) { return; }
		inline virtual void SetOriginDepth(const float r) { return; }

		inline virtual void SetOriginDistortionData(const spatial::distortion_data_t& r) { return; }
		inline virtual void SetOriginHeightDistortion(const float r) { return; }
		inline virtual void SetOriginWidthDistortion(const float r) { return; }
		inline virtual void SetOriginDepthDistortion(const float r) { return; }
		inline virtual void SetOriginSize(const float r) { return; }

		inline virtual void SetOriginOrientationData(const spatial::orientation_data_t& r) { return; }
		inline virtual void SetOriginYaw(const float r) { return; }
		inline virtual void SetOriginPitch(const float r) { return; }
		inline virtual void SetOriginRoll(const float r) { return; }

		inline virtual void SetOriginMomentumData(const spatial::momentum_data_t& r) { return; }
		inline virtual void SetOriginYawDelta(const float r) { return; }
		inline virtual void SetOriginPitchDelta(const float r) { return; }
		inline virtual void SetOriginRollDelta(const float r) { return; }

		inline virtual void SetOriginZOffsetData(const spatial::z_offset_data_t& r) { return; }
		inline virtual void SetOriginGroundOffset(const float r) { return; }
		inline virtual void SetOriginHoverOffset(const float r) { return; }
		inline virtual void SetOriginJumpOffset(const float r) { return; }
		inline virtual void SetOriginFlyingOffset(const float r) { return; }

		inline virtual void SetCTPairData(const spatial::ct_pair_data_t& r) { return; }

		inline virtual void SetCoordinateData(const spatial::coordinate_data_t& r) { return; }
		inline virtual void SetX(const float r) { return; }
		inline virtual void SetY(const float r) { return; }
		inline virtual void SetZ(const float r) { return; }

		inline virtual void SetTrajectoryData(const spatial::trajectory_data_t& r) { return; }
		inline virtual void SetH(const float r) { return; }
		inline virtual void SetV(const float r) { return; }
		inline virtual void SetHeading(const float r) { return; }
		inline virtual void SetVelocity(const float r) { return; }

	protected:

	private:

	};

} // namespace actors
