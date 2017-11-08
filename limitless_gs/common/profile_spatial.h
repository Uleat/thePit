#pragma once


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <list>


namespace spatial {

	typedef glm::vec2 pair_t;
	typedef glm::vec3 triple_t;
	typedef glm::vec4 quadruple_t;

	typedef triple_t dimension_data_t;			// x = Height, y = Width, z = Depth
	typedef quadruple_t distortion_data_t;		// x = Height_mod, y = Width_mod, z = Depth_mod, w = Size
	typedef triple_t orientation_data_t;		// x = X-axis, y = Y-axis, z = Z-axis
	typedef triple_t momentum_data_t;			// x = X-axis_delta, y = Y-axis_delta, z = Z-axis_delta
	typedef quadruple_t z_offset_data_t;		// x = Ground_offset, y = Hover_offset, z = Jump_offset, w = Flying_offset
	typedef triple_t coordinate_data_t;			// x = X, y = Y, z = Z
	typedef quadruple_t trajectory_data_t;		// x = H (horizontal), y = V (vertical), z = Heading (compass), w = Velocity (speed)

	typedef std::pair<coordinate_data_t, trajectory_data_t> ct_pair_data_t;
	typedef std::list<ct_pair_data_t> waypoint_list_t;

} // namespace spatial

#pragma pack(1)

namespace formats {

	struct SpatialOriginData {
		spatial::dimension_data_t DimensionData;
		spatial::distortion_data_t DistortionData;
		spatial::orientation_data_t OrientationData;
		spatial::momentum_data_t MomentumData;
		spatial::z_offset_data_t ZOffsetData;
		spatial::ct_pair_data_t CTPairData;		// static data for 'StaticObject' - dynamic data for 'MobileObject'
	};

	struct SpatialDynamicData {
		spatial::dimension_data_t DimensionData;
		spatial::distortion_data_t DistortionData;
		spatial::orientation_data_t OrientationData;
		spatial::momentum_data_t MomentumData;
		spatial::z_offset_data_t ZOffsetData;
		spatial::ct_pair_data_t LastCTPairData;
		spatial::ct_pair_data_t NextCTPairData;
		spatial::waypoint_list_t* LastWaypointList;
		spatial::waypoint_list_t* NextWaypointList;

		SpatialDynamicData();
		SpatialDynamicData(const SpatialDynamicData& r);
		~SpatialDynamicData();
	};

} // namespace formats

#pragma pack()

namespace spatial {

	// formats::SpatialOriginData

	inline const spatial::dimension_data_t& GetOriginDimensionData(const formats::SpatialOriginData& r) { return r.DimensionData; }
	inline spatial::dimension_data_t& GetOriginDimensionData(formats::SpatialOriginData& r) { return r.DimensionData; }
	inline float GetOriginHeight(const formats::SpatialOriginData& r) { return r.DimensionData.x; }
	inline float GetOriginHeight(const spatial::dimension_data_t& r) { return r.x; }
	inline float GetOriginWidth(const formats::SpatialOriginData& r) { return r.DimensionData.y; }
	inline float GetOriginWidth(const spatial::dimension_data_t& r) { return r.y; }
	inline float GetOriginDepth(const formats::SpatialOriginData& r) { return r.DimensionData.z; }
	inline float GetOriginDepth(const spatial::dimension_data_t& r) { return r.z; }

	inline const spatial::distortion_data_t& GetOriginDistortionData(const formats::SpatialOriginData& r) { return r.DistortionData; }
	inline spatial::distortion_data_t& GetOriginDistortionData(formats::SpatialOriginData& r) { return r.DistortionData; }
	inline float GetOriginHeightDistortion(const formats::SpatialOriginData& r) { return r.DistortionData.x; }
	inline float GetOriginHeightDistortion(const spatial::distortion_data_t& r) { return r.x; }
	inline float GetOriginWidthDistortion(const formats::SpatialOriginData& r) { return r.DistortionData.y; }
	inline float GetOriginWidthDistortion(const spatial::distortion_data_t& r) { return r.y; }
	inline float GetOriginDepthDistortion(const formats::SpatialOriginData& r) { return r.DistortionData.z; }
	inline float GetOriginDepthDistortion(const spatial::distortion_data_t& r) { return r.z; }
	inline float GetOriginSize(const formats::SpatialOriginData& r) { return r.DistortionData.w; }
	inline float GetOriginSize(const spatial::distortion_data_t& r) { return r.w; }

	inline const spatial::orientation_data_t& GetOriginOrientationData(const formats::SpatialOriginData& r) { return r.OrientationData; }
	inline spatial::orientation_data_t& GetOriginOrientationData(formats::SpatialOriginData& r) { return r.OrientationData; }
	inline float GetOriginYaw(const formats::SpatialOriginData& r) { return r.OrientationData.x; }
	inline float GetOriginYaw(const spatial::orientation_data_t& r) { return r.x; }
	inline float GetOriginPitch(const formats::SpatialOriginData& r) { return r.OrientationData.y; }
	inline float GetOriginPitch(const spatial::orientation_data_t& r) { return r.y; }
	inline float GetOriginRoll(const formats::SpatialOriginData& r) { return r.OrientationData.z; }
	inline float GetOriginRoll(const spatial::orientation_data_t& r) { return r.z; }

	inline const spatial::momentum_data_t& GetOriginMomentumData(const formats::SpatialOriginData& r) { return r.MomentumData; }
	inline spatial::momentum_data_t& GetOriginMomentumData(formats::SpatialOriginData& r) { return r.MomentumData; }
	inline float GetOriginYawDelta(const formats::SpatialOriginData& r) { return r.MomentumData.x; }
	inline float GetOriginYawDelta(const spatial::momentum_data_t& r) { return r.x; }
	inline float GetOriginPitchDelta(const formats::SpatialOriginData& r) { return r.MomentumData.y; }
	inline float GetOriginPitchDelta(const spatial::momentum_data_t& r) { return r.y; }
	inline float GetOriginRollDelta(const formats::SpatialOriginData& r) { return r.MomentumData.z; }
	inline float GetOriginRollDelta(const spatial::momentum_data_t& r) { return r.z; }

	inline const spatial::z_offset_data_t& GetOriginZOffsetData(const formats::SpatialOriginData& r) { return r.ZOffsetData; }
	inline spatial::z_offset_data_t& GetOriginZOffsetData(formats::SpatialOriginData& r) { return r.ZOffsetData; }
	inline float GetOriginGroundOffset(const formats::SpatialOriginData& r) { return r.ZOffsetData.x; }
	inline float GetOriginGroundOffset(const spatial::z_offset_data_t& r) { return r.x; }
	inline float GetOriginHoverOffset(const formats::SpatialOriginData& r) { return r.ZOffsetData.y; }
	inline float GetOriginHoverOffset(const spatial::z_offset_data_t& r) { return r.y; }
	inline float GetOriginJumpOffset(const formats::SpatialOriginData& r) { return r.ZOffsetData.z; }
	inline float GetOriginJumpOffset(const spatial::z_offset_data_t& r) { return r.z; }
	inline float GetOriginFlyingOffset(const formats::SpatialOriginData& r) { return r.ZOffsetData.w; }
	inline float GetOriginFlyingOffset(const spatial::z_offset_data_t& r) { return r.w; }

	inline const spatial::ct_pair_data_t& GetCTPairData(const formats::SpatialOriginData& r) { return r.CTPairData; }
	inline spatial::ct_pair_data_t& GetCTPairData(formats::SpatialOriginData& r) { return r.CTPairData; }

	inline const spatial::coordinate_data_t& GetCoordinateData(const formats::SpatialOriginData& r) { return r.CTPairData.first; }
	inline spatial::coordinate_data_t& GetCoordinateData(formats::SpatialOriginData& r) { return r.CTPairData.first; }
	inline const spatial::coordinate_data_t& GetCoordinateData(const spatial::ct_pair_data_t& r) { return r.first; }
	inline spatial::coordinate_data_t& GetCoordinateData(spatial::ct_pair_data_t& r) { return r.first; }
	inline float GetX(const formats::SpatialOriginData& r) { return r.CTPairData.first.x; }
	inline float GetX(const spatial::ct_pair_data_t& r) { return r.first.x; }
	inline float GetX(const spatial::coordinate_data_t& r) { return r.x; }
	inline float GetY(const formats::SpatialOriginData& r) { return r.CTPairData.first.y; }
	inline float GetY(const spatial::ct_pair_data_t& r) { return r.first.y; }
	inline float GetY(const spatial::coordinate_data_t& r) { return r.y; }
	inline float GetZ(const formats::SpatialOriginData& r) { return r.CTPairData.first.z; }
	inline float GetZ(const spatial::ct_pair_data_t& r) { return r.first.z; }
	inline float GetZ(const spatial::coordinate_data_t& r) { return r.z; }

	inline const spatial::trajectory_data_t& GetTrajectoryData(const formats::SpatialOriginData& r) { return r.CTPairData.second; }
	inline spatial::trajectory_data_t& GetTrajectoryData(formats::SpatialOriginData& r) { return r.CTPairData.second; }
	inline const spatial::trajectory_data_t& GetTrajectoryData(const spatial::ct_pair_data_t& r) { return r.second; }
	inline spatial::trajectory_data_t& GetTrajectoryData(spatial::ct_pair_data_t& r) { return r.second; }
	inline float GetH(const formats::SpatialOriginData& r) { return r.CTPairData.second.x; }
	inline float GetH(const spatial::ct_pair_data_t& r) { return r.second.x; }
	inline float GetH(const spatial::trajectory_data_t& r) { return r.x; }
	inline float GetV(const formats::SpatialOriginData& r) { return r.CTPairData.second.y; }
	inline float GetV(const spatial::ct_pair_data_t& r) { return r.second.y; }
	inline float GetV(const spatial::trajectory_data_t& r) { return r.y; }
	inline float GetHeading(const formats::SpatialOriginData& r) { return r.CTPairData.second.z; }
	inline float GetHeading(const spatial::ct_pair_data_t& r) { return r.second.z; }
	inline float GetHeading(const spatial::trajectory_data_t& r) { return r.z; }
	inline float GetVelocity(const formats::SpatialOriginData& r) { return r.CTPairData.second.w; }
	inline float GetVelocity(const spatial::ct_pair_data_t& r) { return r.second.w; }
	inline float GetVelocity(const spatial::trajectory_data_t& r) { return r.w; }

	inline void SetOriginDimensionData(formats::SpatialOriginData& l, const spatial::dimension_data_t& r) { l.DimensionData = r; }
	inline void SetOriginHeight(formats::SpatialOriginData& l, const float r) { l.DimensionData.x = r; }
	inline void SetOriginHeight(spatial::dimension_data_t& l, const float r) { l.x = r; }
	inline void SetOriginWidth(formats::SpatialOriginData& l, const float r) { l.DimensionData.y = r; }
	inline void SetOriginWidth(spatial::dimension_data_t& l, const float r) { l.y = r; }
	inline void SetOriginDepth(formats::SpatialOriginData& l, const float r) { l.DimensionData.z = r; }
	inline void SetOriginDepth(spatial::dimension_data_t& l, const float r) { l.z = r; }

	inline void SetOriginDistortionData(formats::SpatialOriginData& l, const spatial::distortion_data_t& r) { l.DistortionData = r; }
	inline void SetOriginHeightDistortion(formats::SpatialOriginData& l, const float r) { l.DistortionData.x = r; }
	inline void SetOriginHeightDistortion(spatial::distortion_data_t& l, const float r) { l.x = r; }
	inline void SetOriginWidthDistortion(formats::SpatialOriginData& l, const float r) { l.DistortionData.y = r; }
	inline void SetOriginWidthDistortion(spatial::distortion_data_t& l, const float r) { l.y = r; }
	inline void SetOriginDepthDistortion(formats::SpatialOriginData& l, const float r) { l.DistortionData.z = r; }
	inline void SetOriginDepthDistortion(spatial::distortion_data_t& l, const float r) { l.z = r; }
	inline void SetOriginSize(formats::SpatialOriginData& l, const float r) { l.DistortionData.w = r; }
	inline void SetOriginSize(spatial::distortion_data_t& l, const float r) { l.w = r; }

	inline void SetOriginOrientationData(formats::SpatialOriginData& l, const spatial::orientation_data_t& r) { l.OrientationData = r; }
	inline void SetOriginYaw(formats::SpatialOriginData& l, const float r) { l.OrientationData.x = r; }
	inline void SetOriginYaw(spatial::orientation_data_t& l, const float r) { l.x = r; }
	inline void SetOriginPitch(formats::SpatialOriginData& l, const float r) { l.OrientationData.y = r; }
	inline void SetOriginPitch(spatial::orientation_data_t& l, const float r) { l.y = r; }
	inline void SetOriginRoll(formats::SpatialOriginData& l, const float r) { l.OrientationData.z = r; }
	inline void SetOriginRoll(spatial::orientation_data_t& l, const float r) { l.z = r; }

	inline void SetOriginMomentumData(formats::SpatialOriginData& l, const spatial::momentum_data_t& r) { l.MomentumData = r; }
	inline void SetOriginYawDelta(formats::SpatialOriginData& l, const float r) { l.MomentumData.x = r; }
	inline void SetOriginYawDelta(spatial::momentum_data_t& l, const float r) { l.x = r; }
	inline void SetOriginPitchDelta(formats::SpatialOriginData& l, const float r) { l.MomentumData.y = r; }
	inline void SetOriginPitchDelta(spatial::momentum_data_t& l, const float r) { l.y = r; }
	inline void SetOriginRollDelta(formats::SpatialOriginData& l, const float r) { l.MomentumData.z = r; }
	inline void SetOriginRollDelta(spatial::momentum_data_t& l, const float r) { l.z = r; }

	inline void SetOriginZOffsetData(formats::SpatialOriginData& l, const spatial::z_offset_data_t& r) { l.ZOffsetData = r; }
	inline void SetOriginGroundOffset(formats::SpatialOriginData& l, const float r) { l.ZOffsetData.x = r; }
	inline void SetOriginGroundOffset(spatial::z_offset_data_t& l, const float r) { l.x = r; }
	inline void SetOriginHoverOffset(formats::SpatialOriginData& l, const float r) { l.ZOffsetData.y = r; }
	inline void SetOriginHoverOffset(spatial::z_offset_data_t& l, const float r) { l.y = r; }
	inline void SetOriginJumpOffset(formats::SpatialOriginData& l, const float r) { l.ZOffsetData.z = r; }
	inline void SetOriginJumpOffset(spatial::z_offset_data_t& l, const float r) { l.z = r; }
	inline void SetOriginFlyingOffset(formats::SpatialOriginData& l, const float r) { l.ZOffsetData.w = r; }
	inline void SetOriginFlyingOffset(spatial::z_offset_data_t& l, const float r) { l.w = r; }

	inline void SetCTPairData(formats::SpatialOriginData& l, const spatial::ct_pair_data_t& r) { l.CTPairData = r; }

	inline void SetCoordinateData(formats::SpatialOriginData& l, const spatial::coordinate_data_t& r) { l.CTPairData.first = r; }
	inline void SetX(formats::SpatialOriginData& l, const float r) { l.CTPairData.first.x = r; }
	inline void SetX(spatial::ct_pair_data_t& l, const float r) { l.first.x = r; }
	inline void SetX(spatial::coordinate_data_t& l, const float r) { l.x = r; }
	inline void SetY(formats::SpatialOriginData& l, const float r) { l.CTPairData.first.y = r; }
	inline void SetY(spatial::ct_pair_data_t& l, const float r) { l.first.y = r; }
	inline void SetY(spatial::coordinate_data_t& l, const float r) { l.y = r; }
	inline void SetZ(formats::SpatialOriginData& l, const float r) { l.CTPairData.first.z = r; }
	inline void SetZ(spatial::ct_pair_data_t& l, const float r) { l.first.z = r; }
	inline void SetZ(spatial::coordinate_data_t& l, const float r) { l.z = r; }

	inline void SetTrajectoryData(formats::SpatialOriginData& l, const spatial::trajectory_data_t& r) { l.CTPairData.second = r; }
	inline void SetH(formats::SpatialOriginData& l, const float r) { l.CTPairData.second.x = r; }
	inline void SetH(spatial::ct_pair_data_t& l, const float r) { l.second.x = r; }
	inline void SetH(spatial::trajectory_data_t& l, const float r) { l.x = r; }
	inline void SetV(formats::SpatialOriginData& l, const float r) { l.CTPairData.second.y = r; }
	inline void SetV(spatial::ct_pair_data_t& l, const float r) { l.second.y = r; }
	inline void SetV(spatial::trajectory_data_t& l, const float r) { l.y = r; }
	inline void SetHeading(formats::SpatialOriginData& l, const float r) { l.CTPairData.second.z = r; }
	inline void SetHeading(spatial::ct_pair_data_t& l, const float r) { l.second.z = r; }
	inline void SetHeading(spatial::trajectory_data_t& l, const float r) { l.z = r; }
	inline void SetVelocity(formats::SpatialOriginData& l, const float r) { l.CTPairData.second.w = r; }
	inline void SetVelocity(spatial::ct_pair_data_t& l, const float r) { l.second.w = r; }
	inline void SetVelocity(spatial::trajectory_data_t& l, const float r) { l.w = r; }

	inline pair_t GetOriginHeightAndDistortion(const formats::SpatialOriginData& r) { return pair_t(r.DimensionData.x, r.DistortionData.x); }
	inline pair_t GetOriginHeightAndDistortion(const spatial::dimension_data_t& r1, const spatial::distortion_data_t& r2) { return pair_t(r1.x, r2.x); }

	inline pair_t GetOriginWidthAndDistortion(const formats::SpatialOriginData& r) { return pair_t(r.DimensionData.y, r.DistortionData.y); }
	inline pair_t GetOriginWidthAndDistortion(const spatial::dimension_data_t& r1, const spatial::distortion_data_t& r2) { return pair_t(r1.y, r2.y); }

	inline pair_t GetOriginDepthAndDistortion(const formats::SpatialOriginData& r) { return pair_t(r.DimensionData.z, r.DistortionData.z); }
	inline pair_t GetOriginDepthAndDistortion(const spatial::dimension_data_t& r1, const spatial::distortion_data_t& r2) { return pair_t(r1.z, r2.z); }

	inline pair_t GetOriginYawAndDelta(const formats::SpatialOriginData& r) { return pair_t(r.OrientationData.x, r.MomentumData.x); }
	inline pair_t GetOriginYawAndDelta(const spatial::orientation_data_t& r1, const spatial::momentum_data_t& r2) { return pair_t(r1.x, r2.x); }

	inline pair_t GetOriginPitchAndDelta(const formats::SpatialOriginData& r) { return pair_t(r.OrientationData.y, r.MomentumData.y); }
	inline pair_t GetOriginPitchAndDelta(const spatial::orientation_data_t& r1, const spatial::momentum_data_t& r2) { return pair_t(r1.y, r2.y); }

	inline pair_t GetOriginRollAndDelta(const formats::SpatialOriginData& r) { return pair_t(r.OrientationData.z, r.MomentumData.z); }
	inline pair_t GetOriginRollAndDelta(const spatial::orientation_data_t& r1, const spatial::momentum_data_t& r2) { return pair_t(r1.z, r2.z); }

	inline pair_t GetHV(const formats::SpatialOriginData& r) { return pair_t(r.CTPairData.second.x, r.CTPairData.second.y); }
	inline pair_t GetHV(const spatial::trajectory_data_t& r) { return pair_t(r.x, r.y); }

	inline pair_t GetHeadingVelocity(const formats::SpatialOriginData& r) { return pair_t(r.CTPairData.second.z, r.CTPairData.second.w); }
	inline pair_t GetHeadingVelocity(const spatial::ct_pair_data_t& r) { return pair_t(r.second.z, r.second.w); }
	inline pair_t GetHeadingVelocity(const spatial::trajectory_data_t& r) { return pair_t(r.z, r.w); }

	inline triple_t GetHVVelocity(const formats::SpatialOriginData& r) { return triple_t(r.CTPairData.second.x, r.CTPairData.second.y, r.CTPairData.second.w); }
	inline triple_t GetHVVelocity(const spatial::ct_pair_data_t& r) { return triple_t(r.second.x, r.second.y, r.second.w); }
	inline triple_t GetHVVelocity(const spatial::trajectory_data_t& r) { return triple_t(r.x, r.y, r.w); }

	// formats::SpatialDynamicData

	inline const spatial::dimension_data_t& GetDimensionData(const formats::SpatialDynamicData& r) { return r.DimensionData; }
	inline spatial::dimension_data_t& GetDimensionData(formats::SpatialDynamicData& r) { return r.DimensionData; }
	inline float GetHeight(const formats::SpatialDynamicData& r) { return r.DimensionData.x; }
	inline float GetHeight(const spatial::dimension_data_t& r) { return r.x; }
	inline float GetWidth(const formats::SpatialDynamicData& r) { return r.DimensionData.y; }
	inline float GetWidth(const spatial::dimension_data_t& r) { return r.y; }
	inline float GetDepth(const formats::SpatialDynamicData& r) { return r.DimensionData.z; }
	inline float GetDepth(const spatial::dimension_data_t& r) { return r.z; }

	inline const spatial::distortion_data_t& GetDistortionData(const formats::SpatialDynamicData& r) { return r.DistortionData; }
	inline spatial::distortion_data_t& GetDistortionData(formats::SpatialDynamicData& r) { return r.DistortionData; }
	inline float GetHeightDistortion(const formats::SpatialDynamicData& r) { return r.DistortionData.x; }
	inline float GetHeightDistortion(const spatial::distortion_data_t& r) { return r.x; }
	inline float GetWidthDistortion(const formats::SpatialDynamicData& r) { return r.DistortionData.y; }
	inline float GetWidthDistortion(const spatial::distortion_data_t& r) { return r.y; }
	inline float GetDepthDistortion(const formats::SpatialDynamicData& r) { return r.DistortionData.z; }
	inline float GetDepthDistortion(const spatial::distortion_data_t& r) { return r.z; }
	inline float GetSize(const formats::SpatialDynamicData& r) { return r.DistortionData.w; }
	inline float GetSize(const spatial::distortion_data_t& r) { return r.w; }

	inline const spatial::orientation_data_t& GetOrientationData(const formats::SpatialDynamicData& r) { return r.OrientationData; }
	inline spatial::orientation_data_t& GetOrientationData(formats::SpatialDynamicData& r) { return r.OrientationData; }
	inline float GetYaw(const formats::SpatialDynamicData& r) { return r.OrientationData.x; }
	inline float GetYaw(const spatial::orientation_data_t& r) { return r.x; }
	inline float GetPitch(const formats::SpatialDynamicData& r) { return r.OrientationData.y; }
	inline float GetPitch(const spatial::orientation_data_t& r) { return r.y; }
	inline float GetRoll(const formats::SpatialDynamicData& r) { return r.OrientationData.z; }
	inline float GetRoll(const spatial::orientation_data_t& r) { return r.z; }

	inline const spatial::momentum_data_t& GetMomentumData(const formats::SpatialDynamicData& r) { return r.MomentumData; }
	inline spatial::momentum_data_t& GetMomentumData(formats::SpatialDynamicData& r) { return r.MomentumData; }
	inline float GetYawDelta(const formats::SpatialDynamicData& r) { return r.MomentumData.x; }
	inline float GetYawDelta(const spatial::momentum_data_t& r) { return r.x; }
	inline float GetPitchDelta(const formats::SpatialDynamicData& r) { return r.MomentumData.y; }
	inline float GetPitchDelta(const spatial::momentum_data_t& r) { return r.y; }
	inline float GetRollDelta(const formats::SpatialDynamicData& r) { return r.MomentumData.z; }
	inline float GetRollDelta(const spatial::momentum_data_t& r) { return r.z; }

	inline const spatial::z_offset_data_t& GetZOffsetData(const formats::SpatialDynamicData& r) { return r.ZOffsetData; }
	inline spatial::z_offset_data_t& GetZOffsetData(formats::SpatialDynamicData& r) { return r.ZOffsetData; }
	inline float GetGroundOffset(const formats::SpatialDynamicData& r) { return r.ZOffsetData.x; }
	inline float GetGroundOffset(const spatial::z_offset_data_t& r) { return r.x; }
	inline float GetHoverOffset(const formats::SpatialDynamicData& r) { return r.ZOffsetData.y; }
	inline float GetHoverOffset(const spatial::z_offset_data_t& r) { return r.y; }
	inline float GetJumpOffset(const formats::SpatialDynamicData& r) { return r.ZOffsetData.z; }
	inline float GetJumpOffset(const spatial::z_offset_data_t& r) { return r.z; }
	inline float GetFlyingOffset(const formats::SpatialDynamicData& r) { return r.ZOffsetData.w; }
	inline float GetFlyingOffset(const spatial::z_offset_data_t& r) { return r.w; }

	inline const spatial::ct_pair_data_t& GetLastCTPairData(const formats::SpatialDynamicData& r) { return r.LastCTPairData; }
	inline spatial::ct_pair_data_t& GetLastCTPairData(formats::SpatialDynamicData& r) { return r.LastCTPairData; }

	inline const spatial::coordinate_data_t& GetLastCoordinateData(const formats::SpatialDynamicData& r) { return r.LastCTPairData.first; }
	inline spatial::coordinate_data_t& GetLastCoordinateData(formats::SpatialDynamicData& r) { return r.LastCTPairData.first; }
	inline float GetLastX(const formats::SpatialDynamicData& r) { return r.LastCTPairData.first.x; }
	inline float GetLastX(const spatial::ct_pair_data_t& r) { return r.first.x; }
	inline float GetLastX(const spatial::coordinate_data_t& r) { return r.x; }
	inline float GetLastY(const formats::SpatialDynamicData& r) { return r.LastCTPairData.first.y; }
	inline float GetLastY(const spatial::ct_pair_data_t& r) { return r.first.y; }
	inline float GetLastY(const spatial::coordinate_data_t& r) { return r.y; }
	inline float GetLastZ(const formats::SpatialDynamicData& r) { return r.LastCTPairData.first.z; }
	inline float GetLastZ(const spatial::ct_pair_data_t& r) { return r.first.z; }
	inline float GetLastZ(const spatial::coordinate_data_t& r) { return r.z; }

	inline const spatial::trajectory_data_t& GetLastTrajectoryData(const formats::SpatialDynamicData& r) { return r.LastCTPairData.second; }
	inline spatial::trajectory_data_t& GetLastTrajectoryData(formats::SpatialDynamicData& r) { return r.LastCTPairData.second; }
	inline float GetLastH(const formats::SpatialDynamicData& r) { return r.LastCTPairData.second.x; }
	inline float GetLastH(const spatial::ct_pair_data_t& r) { return r.second.x; }
	inline float GetLastH(const spatial::trajectory_data_t& r) { return r.x; }
	inline float GetLastV(const formats::SpatialDynamicData& r) { return r.LastCTPairData.second.y; }
	inline float GetLastV(const spatial::ct_pair_data_t& r) { return r.second.y; }
	inline float GetLastV(const spatial::trajectory_data_t& r) { return r.y; }
	inline float GetLastHeading(const formats::SpatialDynamicData& r) { return r.LastCTPairData.second.z; }
	inline float GetLastHeading(const spatial::ct_pair_data_t& r) { return r.second.z; }
	inline float GetLastHeading(const spatial::trajectory_data_t& r) { return r.z; }
	inline float GetLastVelocity(const formats::SpatialDynamicData& r) { return r.LastCTPairData.second.w; }
	inline float GetLastVelocity(const spatial::ct_pair_data_t& r) { return r.second.w; }
	inline float GetLastVelocity(const spatial::trajectory_data_t& r) { return r.w; }

	inline const spatial::ct_pair_data_t& GetNextCTPairData(const formats::SpatialDynamicData& r) { return r.NextCTPairData; }
	inline spatial::ct_pair_data_t& GetNextCTPairData(formats::SpatialDynamicData& r) { return r.NextCTPairData; }

	inline const spatial::coordinate_data_t& GetNextCoordinateData(const formats::SpatialDynamicData& r) { return r.NextCTPairData.first; }
	inline spatial::coordinate_data_t& GetNextCoordinateData(formats::SpatialDynamicData& r) { return r.NextCTPairData.first; }
	inline float GetNextX(const formats::SpatialDynamicData& r) { return r.NextCTPairData.first.x; }
	inline float GetNextX(const spatial::ct_pair_data_t& r) { return r.first.x; }
	inline float GetNextX(const spatial::coordinate_data_t& r) { return r.x; }
	inline float GetNextY(const formats::SpatialDynamicData& r) { return r.NextCTPairData.first.y; }
	inline float GetNextY(const spatial::ct_pair_data_t& r) { return r.first.y; }
	inline float GetNextY(const spatial::coordinate_data_t& r) { return r.y; }
	inline float GetNextZ(const formats::SpatialDynamicData& r) { return r.NextCTPairData.first.z; }
	inline float GetNextZ(const spatial::ct_pair_data_t& r) { return r.first.z; }
	inline float GetNextZ(const spatial::coordinate_data_t& r) { return r.z; }

	inline const spatial::trajectory_data_t& GetNextTrajectoryData(const formats::SpatialDynamicData& r) { return r.NextCTPairData.second; }
	inline spatial::trajectory_data_t& GetNextTrajectoryData(formats::SpatialDynamicData& r) { return r.NextCTPairData.second; }
	inline float GetNextH(const formats::SpatialDynamicData& r) { return r.NextCTPairData.second.x; }
	inline float GetNextH(const spatial::ct_pair_data_t& r) { return r.second.x; }
	inline float GetNextH(const spatial::trajectory_data_t& r) { return r.x; }
	inline float GetNextV(const formats::SpatialDynamicData& r) { return r.NextCTPairData.second.y; }
	inline float GetNextV(const spatial::ct_pair_data_t& r) { return r.second.y; }
	inline float GetNextV(const spatial::trajectory_data_t& r) { return r.y; }
	inline float GetNextHeading(const formats::SpatialDynamicData& r) { return r.NextCTPairData.second.z; }
	inline float GetNextHeading(const spatial::ct_pair_data_t& r) { return r.second.z; }
	inline float GetNextHeading(const spatial::trajectory_data_t& r) { return r.z; }
	inline float GetNextVelocity(const formats::SpatialDynamicData& r) { return r.NextCTPairData.second.w; }
	inline float GetNextVelocity(const spatial::ct_pair_data_t& r) { return r.second.w; }
	inline float GetNextVelocity(const spatial::trajectory_data_t& r) { return r.w; }
	
	inline void SetDimensionData(formats::SpatialDynamicData& l, const spatial::dimension_data_t& r) { l.DimensionData = r; }
	inline void SetHeight(formats::SpatialDynamicData& l, const float r) { l.DimensionData.x = r; }
	inline void SetHeight(spatial::dimension_data_t& l, const float r) { l.x = r; }
	inline void SetWidth(formats::SpatialDynamicData& l, const float r) { l.DimensionData.y = r; }
	inline void SetWidth(spatial::dimension_data_t& l, const float r) { l.y = r; }
	inline void SetDepth(formats::SpatialDynamicData& l, const float r) { l.DimensionData.z = r; }
	inline void SetDepth(spatial::dimension_data_t& l, const float r) { l.z = r; }

	inline void SetDistortionData(formats::SpatialDynamicData& l, const spatial::distortion_data_t& r) { l.DistortionData = r; }
	inline void SetHeightDistortion(formats::SpatialDynamicData& l, const float r) { l.DistortionData.x = r; }
	inline void SetHeightDistortion(spatial::distortion_data_t& l, const float r) { l.x = r; }
	inline void SetWidthDistortion(formats::SpatialDynamicData& l, const float r) { l.DistortionData.y = r; }
	inline void SetWidthDistortion(spatial::distortion_data_t& l, const float r) { l.y = r; }
	inline void SetDepthDistortion(formats::SpatialDynamicData& l, const float r) { l.DistortionData.z = r; }
	inline void SetDepthDistortion(spatial::distortion_data_t& l, const float r) { l.z = r; }
	inline void SetSize(formats::SpatialDynamicData& l, const float r) { l.DistortionData.w = r; }
	inline void SetSize(spatial::distortion_data_t& l, const float r) { l.w = r; }

	inline void SetOrientationData(formats::SpatialDynamicData& l, const spatial::orientation_data_t& r) { l.OrientationData = r; }
	inline void SetYaw(formats::SpatialDynamicData& l, const float r) { l.OrientationData.x = r; }
	inline void SetYaw(spatial::orientation_data_t& l, const float r) { l.x = r; }
	inline void SetPitch(formats::SpatialDynamicData& l, const float r) { l.OrientationData.y = r; }
	inline void SetPitch(spatial::orientation_data_t& l, const float r) { l.y = r; }
	inline void SetRoll(formats::SpatialDynamicData& l, const float r) { l.OrientationData.z = r; }
	inline void SetRoll(spatial::orientation_data_t& l, const float r) { l.z = r; }

	inline void SetMomentumData(formats::SpatialDynamicData& l, const spatial::momentum_data_t& r) { l.MomentumData = r; }
	inline void SetYawDelta(formats::SpatialDynamicData& l, const float r) { l.MomentumData.x = r; }
	inline void SetYawDelta(spatial::momentum_data_t& l, const float r) { l.x = r; }
	inline void SetPitchDelta(formats::SpatialDynamicData& l, const float r) { l.MomentumData.y = r; }
	inline void SetPitchDelta(spatial::momentum_data_t& l, const float r) { l.y = r; }
	inline void SetRollDelta(formats::SpatialDynamicData& l, const float r) { l.MomentumData.z = r; }
	inline void SetRollDelta(spatial::momentum_data_t& l, const float r) { l.z = r; }

	inline void SetZOffsetData(formats::SpatialDynamicData& l, const spatial::z_offset_data_t& r) { l.ZOffsetData = r; }
	inline void SetGroundOffset(formats::SpatialDynamicData& l, const float r) { l.ZOffsetData.x = r; }
	inline void SetGroundOffset(spatial::z_offset_data_t& l, const float r) { l.x = r; }
	inline void SetHoverOffset(formats::SpatialDynamicData& l, const float r) { l.ZOffsetData.y = r; }
	inline void SetHoverOffset(spatial::z_offset_data_t& l, const float r) { l.y = r; }
	inline void SetJumpOffset(formats::SpatialDynamicData& l, const float r) { l.ZOffsetData.z = r; }
	inline void SetJumpOffset(spatial::z_offset_data_t& l, const float r) { l.z = r; }
	inline void SetFlyingOffset(formats::SpatialDynamicData& l, const float r) { l.ZOffsetData.w = r; }
	inline void SetFlyingOffset(spatial::z_offset_data_t& l, const float r) { l.w = r; }

	inline void SetLastCTPairData(formats::SpatialDynamicData& l, const spatial::ct_pair_data_t& r) { l.LastCTPairData = r; }

	inline void SetLastCoordinateData(formats::SpatialDynamicData& l, const spatial::coordinate_data_t& r) { l.LastCTPairData.first = r; }
	inline void SetLastX(formats::SpatialDynamicData& l, const float r) { l.LastCTPairData.first.x = r; }
	inline void SetLastX(spatial::ct_pair_data_t& l, const float r) { l.first.x = r; }
	inline void SetLastX(spatial::coordinate_data_t& l, const float r) { l.x = r; }
	inline void SetLastY(formats::SpatialDynamicData& l, const float r) { l.LastCTPairData.first.y = r; }
	inline void SetLastY(spatial::ct_pair_data_t& l, const float r) { l.first.y = r; }
	inline void SetLastY(spatial::coordinate_data_t& l, const float r) { l.y = r; }
	inline void SetLastZ(formats::SpatialDynamicData& l, const float r) { l.LastCTPairData.first.z = r; }
	inline void SetLastZ(spatial::ct_pair_data_t& l, const float r) { l.first.z = r; }
	inline void SetLastZ(spatial::coordinate_data_t& l, const float r) { l.z = r; }

	inline void SetLastTrajectoryData(formats::SpatialDynamicData& l, const spatial::trajectory_data_t& r) { l.LastCTPairData.second = r; }
	inline void SetLastH(formats::SpatialDynamicData& l, const float r) { l.LastCTPairData.second.x = r; }
	inline void SetLastH(spatial::ct_pair_data_t& l, const float r) { l.second.x = r; }
	inline void SetLastH(spatial::trajectory_data_t& l, const float r) { l.x = r; }
	inline void SetLastV(formats::SpatialDynamicData& l, const float r) { l.LastCTPairData.second.y = r; }
	inline void SetLastV(spatial::ct_pair_data_t& l, const float r) { l.second.y = r; }
	inline void SetLastV(spatial::trajectory_data_t& l, const float r) { l.y = r; }
	inline void SetLastHeading(formats::SpatialDynamicData& l, const float r) { l.LastCTPairData.second.z = r; }
	inline void SetLastHeading(spatial::ct_pair_data_t& l, const float r) { l.second.z = r; }
	inline void SetLastHeading(spatial::trajectory_data_t& l, const float r) { l.z = r; }
	inline void SetLastVelocity(formats::SpatialDynamicData& l, const float r) { l.LastCTPairData.second.w = r; }
	inline void SetLastVelocity(spatial::ct_pair_data_t& l, const float r) { l.second.w = r; }
	inline void SetLastVelocity(spatial::trajectory_data_t& l, const float r) { l.w = r; }

	inline void SetNextCTPairData(formats::SpatialDynamicData& l, const spatial::ct_pair_data_t& r) { l.NextCTPairData = r; }

	inline void SetNextCoordinateData(formats::SpatialDynamicData& l, const spatial::coordinate_data_t& r) { l.NextCTPairData.first = r; }
	inline void SetNextX(formats::SpatialDynamicData& l, const float r) { l.NextCTPairData.first.x = r; }
	inline void SetNextX(spatial::ct_pair_data_t& l, const float r) { l.first.x = r; }
	inline void SetNextX(spatial::coordinate_data_t& l, const float r) { l.x = r; }
	inline void SetNextY(formats::SpatialDynamicData& l, const float r) { l.NextCTPairData.first.y = r; }
	inline void SetNextY(spatial::ct_pair_data_t& l, const float r) { l.first.y = r; }
	inline void SetNextY(spatial::coordinate_data_t& l, const float r) { l.y = r; }
	inline void SetNextZ(formats::SpatialDynamicData& l, const float r) { l.NextCTPairData.first.z = r; }
	inline void SetNextZ(spatial::ct_pair_data_t& l, const float r) { l.first.z = r; }
	inline void SetNextZ(spatial::coordinate_data_t& l, const float r) { l.z = r; }

	inline void SetNextTrajectoryData(formats::SpatialDynamicData& l, const spatial::trajectory_data_t& r) { l.NextCTPairData.second = r; }
	inline void SetNextH(formats::SpatialDynamicData& l, const float r) { l.NextCTPairData.second.x = r; }
	inline void SetNextH(spatial::ct_pair_data_t& l, const float r) { l.second.x = r; }
	inline void SetNextH(spatial::trajectory_data_t& l, const float r) { l.x = r; }
	inline void SetNextV(formats::SpatialDynamicData& l, const float r) { l.NextCTPairData.second.y = r; }
	inline void SetNextV(spatial::ct_pair_data_t& l, const float r) { l.second.y = r; }
	inline void SetNextV(spatial::trajectory_data_t& l, const float r) { l.y = r; }
	inline void SetNextHeading(formats::SpatialDynamicData& l, const float r) { l.NextCTPairData.second.z = r; }
	inline void SetNextHeading(spatial::ct_pair_data_t& l, const float r) { l.second.z = r; }
	inline void SetNextHeading(spatial::trajectory_data_t& l, const float r) { l.z = r; }
	inline void SetNextVelocity(formats::SpatialDynamicData& l, const float r) { l.NextCTPairData.second.w = r; }
	inline void SetNextVelocity(spatial::ct_pair_data_t& l, const float r) { l.second.w = r; }
	inline void SetNextVelocity(spatial::trajectory_data_t& l, const float r) { l.w = r; }

	inline pair_t GetHeightAndDistortion(const formats::SpatialDynamicData& r) { return pair_t(r.DimensionData.x, r.DistortionData.x); }
	inline pair_t GetHeightAndDistortion(const spatial::dimension_data_t& r1, const spatial::distortion_data_t& r2) { return pair_t(r1.x, r2.x); }

	inline pair_t GetWidthAndDistortion(const formats::SpatialDynamicData& r) { return pair_t(r.DimensionData.y, r.DistortionData.y); }
	inline pair_t GetWidthAndDistortion(const spatial::dimension_data_t& r1, const spatial::distortion_data_t& r2) { return pair_t(r1.y, r2.y); }

	inline pair_t GetDepthAndDistortion(const formats::SpatialDynamicData& r) { return pair_t(r.DimensionData.z, r.DistortionData.z); }
	inline pair_t GetDepthAndDistortion(const spatial::dimension_data_t& r1, const spatial::distortion_data_t& r2) { return pair_t(r1.z, r2.z); }

	inline pair_t GetYawAndDelta(const formats::SpatialDynamicData& r) { return pair_t(r.OrientationData.x, r.MomentumData.x); }
	inline pair_t GetYawAndDelta(const spatial::orientation_data_t& r1, const spatial::momentum_data_t& r2) { return pair_t(r1.x, r2.x); }

	inline pair_t GetPitchAndDelta(const formats::SpatialDynamicData& r) { return pair_t(r.OrientationData.y, r.MomentumData.y); }
	inline pair_t GetPitchAndDelta(const spatial::orientation_data_t& r1, const spatial::momentum_data_t& r2) { return pair_t(r1.y, r2.y); }

	inline pair_t GetRollAndDelta(const formats::SpatialDynamicData& r) { return pair_t(r.OrientationData.z, r.MomentumData.z); }
	inline pair_t GetRollAndDelta(const spatial::orientation_data_t& r1, const spatial::momentum_data_t& r2) { return pair_t(r1.z, r2.z); }

	inline pair_t GetLastHV(const formats::SpatialDynamicData& r) { return pair_t(r.LastCTPairData.second.x, r.LastCTPairData.second.y); }
	inline pair_t GetLastHV(const spatial::ct_pair_data_t& r) { return pair_t(r.second.x, r.second.y); }
	inline pair_t GetLastHV(const spatial::trajectory_data_t& r) { return pair_t(r.x, r.y); }

	inline pair_t GetLastHeadingVelocity(const formats::SpatialDynamicData& r) { return pair_t(r.LastCTPairData.second.z, r.LastCTPairData.second.w); }
	inline pair_t GetLastHeadingVelocity(const spatial::ct_pair_data_t& r) { return pair_t(r.second.z, r.second.w); }
	inline pair_t GetLastHeadingVelocity(const spatial::trajectory_data_t& r) { return pair_t(r.z, r.w); }

	inline triple_t GetLastHVVelocity(const formats::SpatialDynamicData& r) { return triple_t(r.LastCTPairData.second.x, r.LastCTPairData.second.y, r.LastCTPairData.second.w); }
	inline triple_t GetLastHVVelocity(const spatial::ct_pair_data_t& r) { return triple_t(r.second.x, r.second.y, r.second.w); }
	inline triple_t GetLastHVVelocity(const spatial::trajectory_data_t& r) { return triple_t(r.x, r.y, r.w); }

	inline pair_t GetNextHV(const formats::SpatialDynamicData& r) { return pair_t(r.NextCTPairData.second.x, r.NextCTPairData.second.y); }
	inline pair_t GetNextHV(const spatial::ct_pair_data_t& r) { return pair_t(r.second.x, r.second.y); }
	inline pair_t GetNextHV(const spatial::trajectory_data_t& r) { return pair_t(r.x, r.y); }

	inline pair_t GetNextHeadingVelocity(const formats::SpatialDynamicData& r) { return pair_t(r.NextCTPairData.second.z, r.NextCTPairData.second.w); }
	inline pair_t GetNextHeadingVelocity(const spatial::ct_pair_data_t& r) { return pair_t(r.second.z, r.second.w); }
	inline pair_t GetNextHeadingVelocity(const spatial::trajectory_data_t& r) { return pair_t(r.z, r.w); }

	inline triple_t GetNextHVVelocity(const formats::SpatialDynamicData& r) { return triple_t(r.NextCTPairData.second.x, r.NextCTPairData.second.y, r.NextCTPairData.second.w); }
	inline triple_t GetNextHVVelocity(const spatial::ct_pair_data_t& r) { return triple_t(r.second.x, r.second.y, r.second.w); }
	inline triple_t GetNextHVVelocity(const spatial::trajectory_data_t& r) { return triple_t(r.x, r.y, r.w); }

} // namespace spatial

namespace profiles {

	struct SpatialOriginAttributes {
		SpatialOriginAttributes() { }
		SpatialOriginAttributes(const SpatialOriginAttributes& r) : spatial_origin_data_(r.spatial_origin_data_) { }
		SpatialOriginAttributes(const formats::SpatialOriginData& r) : spatial_origin_data_(r) { }
		virtual ~SpatialOriginAttributes() { }

		inline const formats::SpatialOriginData& GetSpatialOriginData() const { return spatial_origin_data_; }
		inline virtual formats::SpatialOriginData& GetSpatialOriginData() { return spatial_origin_data_; }
		
		inline const spatial::dimension_data_t& GetOriginDimensionData() const { return spatial_origin_data_.DimensionData; }
		inline virtual spatial::dimension_data_t& GetOriginDimensionData() { return spatial_origin_data_.DimensionData; }
		inline float GetOriginHeight() const { return spatial_origin_data_.DimensionData.x; }
		inline float GetOriginWidth() const { return spatial_origin_data_.DimensionData.y; }
		inline float GetOriginDepth() const { return spatial_origin_data_.DimensionData.z; }

		inline const spatial::distortion_data_t& GetOriginDistortionData() const { return spatial_origin_data_.DistortionData; }
		inline virtual spatial::distortion_data_t& GetOriginDistortionData() { return spatial_origin_data_.DistortionData; }
		inline float GetOriginHeightDistortion() const { return spatial_origin_data_.DistortionData.x; }
		inline float GetOriginWidthDistortion() const { return spatial_origin_data_.DistortionData.y; }
		inline float GetOriginDepthDistortion() const { return spatial_origin_data_.DistortionData.z; }
		inline float GetOriginSize() const { return spatial_origin_data_.DistortionData.w; }

		inline const spatial::orientation_data_t& GetOriginOrientationData() const { return spatial_origin_data_.OrientationData; }
		inline virtual spatial::orientation_data_t& GetOriginOrientationData() { return spatial_origin_data_.OrientationData; }
		inline float GetOriginYaw() const { return spatial_origin_data_.OrientationData.x; }
		inline float GetOriginPitch() const { return spatial_origin_data_.OrientationData.y; }
		inline float GetOriginRoll() const { return spatial_origin_data_.OrientationData.z; }

		inline const spatial::momentum_data_t& GetOriginMomentumData() const { return spatial_origin_data_.MomentumData; }
		inline virtual spatial::momentum_data_t& GetOriginMomentumData() { return spatial_origin_data_.MomentumData; }
		inline float GetOriginYawDelta() const { return spatial_origin_data_.MomentumData.x; }
		inline float GetOriginPitchDelta() const { return spatial_origin_data_.MomentumData.y; }
		inline float GetOriginRollDelta() const { return spatial_origin_data_.MomentumData.z; }

		inline const spatial::z_offset_data_t& GetOriginZOffsetData() const { return spatial_origin_data_.ZOffsetData; }
		inline virtual spatial::z_offset_data_t& GetOriginZOffsetData() { return spatial_origin_data_.ZOffsetData; }
		inline float GetOriginGroundOffset() const { return spatial_origin_data_.ZOffsetData.x; }
		inline float GetOriginHoverOffset() const { return spatial_origin_data_.ZOffsetData.y; }
		inline float GetOriginJumpOffset() const { return spatial_origin_data_.ZOffsetData.z; }
		inline float GetOriginFlyingOffset() const { return spatial_origin_data_.ZOffsetData.w; }

		inline const spatial::ct_pair_data_t& GetCTPairData() const { return spatial_origin_data_.CTPairData; }
		inline virtual spatial::ct_pair_data_t& GetCTPairData() { return spatial_origin_data_.CTPairData; }

		inline const spatial::coordinate_data_t& GetCoordinateData() const { return spatial_origin_data_.CTPairData.first; }
		inline virtual spatial::coordinate_data_t& GetCoordinateData() { return spatial_origin_data_.CTPairData.first; }
		inline float GetX() const { return spatial_origin_data_.CTPairData.first.x; }
		inline float GetY() const { return spatial_origin_data_.CTPairData.first.y; }
		inline float GetZ() const { return spatial_origin_data_.CTPairData.first.z; }

		inline const spatial::trajectory_data_t& GetTrajectoryData() const { return spatial_origin_data_.CTPairData.second; }
		inline virtual spatial::trajectory_data_t& GetTrajectoryData() { return spatial_origin_data_.CTPairData.second; }
		inline float GetH() const { return spatial_origin_data_.CTPairData.second.x; }
		inline float GetV() const { return spatial_origin_data_.CTPairData.second.y; }
		inline float GetHeading() const { return spatial_origin_data_.CTPairData.second.z; }
		inline float GetVelocity() const { return spatial_origin_data_.CTPairData.second.w; }

		inline spatial::pair_t GetOriginHeightAndDistortion() const { return spatial::pair_t(spatial_origin_data_.DimensionData.x, spatial_origin_data_.DistortionData.x); }
		inline spatial::pair_t GetOriginWidthAndDistortion() const { return spatial::pair_t(spatial_origin_data_.DimensionData.y, spatial_origin_data_.DistortionData.y); }
		inline spatial::pair_t GetOriginDepthAndDistortion() const { return spatial::pair_t(spatial_origin_data_.DimensionData.z, spatial_origin_data_.DistortionData.z); }

		inline spatial::pair_t GetOriginYawAndDelta() const { return spatial::pair_t(spatial_origin_data_.OrientationData.x, spatial_origin_data_.MomentumData.x); }
		inline spatial::pair_t GetOriginPitchAndDelta() const { return spatial::pair_t(spatial_origin_data_.OrientationData.y, spatial_origin_data_.MomentumData.y); }
		inline spatial::pair_t GetOriginRollAndDelta() const { return spatial::pair_t(spatial_origin_data_.OrientationData.z, spatial_origin_data_.MomentumData.z); }
		
		inline spatial::pair_t GetHV() const { return spatial::pair_t(spatial_origin_data_.CTPairData.second.x, spatial_origin_data_.CTPairData.second.y); }
		inline spatial::pair_t GetHeadingVelocity() const { return spatial::pair_t(spatial_origin_data_.CTPairData.second.z, spatial_origin_data_.CTPairData.second.w); }
		inline spatial::triple_t GetHVVelocity() const { return spatial::triple_t(spatial_origin_data_.CTPairData.second.x, spatial_origin_data_.CTPairData.second.y, spatial_origin_data_.CTPairData.second.w); }
		
		inline virtual void SetSpatialOriginData(const formats::SpatialOriginData& r) { spatial_origin_data_ = r; }
		
		inline virtual void SetOriginDimensionData(const spatial::dimension_data_t& r) { spatial_origin_data_.DimensionData = r; }
		inline virtual void SetOriginHeight(const float r) { spatial_origin_data_.DimensionData.x = r; }
		inline virtual void SetOriginWidth(const float r) { spatial_origin_data_.DimensionData.y = r; }
		inline virtual void SetOriginDepth(const float r) { spatial_origin_data_.DimensionData.z = r; }

		inline virtual void SetOriginDistortionData(const spatial::distortion_data_t& r) { spatial_origin_data_.DistortionData = r; }
		inline virtual void SetOriginHeightDistortion(const float r) { spatial_origin_data_.DistortionData.x = r; }
		inline virtual void SetOriginWidthDistortion(const float r) { spatial_origin_data_.DistortionData.y = r; }
		inline virtual void SetOriginDepthDistortion(const float r) { spatial_origin_data_.DistortionData.z = r; }
		inline virtual void SetOriginSize(const float r) { spatial_origin_data_.DistortionData.w = r; }

		inline virtual void SetOriginOrientationData(const spatial::orientation_data_t& r) { spatial_origin_data_.OrientationData = r; }
		inline virtual void SetOriginYaw(const float r) { spatial_origin_data_.OrientationData.x = r; }
		inline virtual void SetOriginPitch(const float r) { spatial_origin_data_.OrientationData.y = r; }
		inline virtual void SetOriginRoll(const float r) { spatial_origin_data_.OrientationData.z = r; }

		inline virtual void SetOriginMomentumData(const spatial::momentum_data_t& r) { spatial_origin_data_.MomentumData = r; }
		inline virtual void SetOriginYawDelta(const float r) { spatial_origin_data_.MomentumData.x = r; }
		inline virtual void SetOriginPitchDelta(const float r) { spatial_origin_data_.MomentumData.y = r; }
		inline virtual void SetOriginRollDelta(const float r) { spatial_origin_data_.MomentumData.z = r; }

		inline virtual void SetOriginZOffsetData(const spatial::z_offset_data_t& r) { spatial_origin_data_.ZOffsetData = r; }
		inline virtual void SetOriginGroundOffset(const float r) { spatial_origin_data_.ZOffsetData.x = r; }
		inline virtual void SetOriginHoverOffset(const float r) { spatial_origin_data_.ZOffsetData.y = r; }
		inline virtual void SetOriginJumpOffset(const float r) { spatial_origin_data_.ZOffsetData.z = r; }
		inline virtual void SetOriginFlyingOffset(const float r) { spatial_origin_data_.ZOffsetData.w = r; }

		inline virtual void SetCTPairData(const spatial::ct_pair_data_t& r) { spatial_origin_data_.CTPairData = r; }

		inline virtual void SetCoordinateData(const spatial::coordinate_data_t& r) { spatial_origin_data_.CTPairData.first = r; }
		inline virtual void SetX(const float r) { spatial_origin_data_.CTPairData.first.x = r; }
		inline virtual void SetY(const float r) { spatial_origin_data_.CTPairData.first.y = r; }
		inline virtual void SetZ(const float r) { spatial_origin_data_.CTPairData.first.z = r; }

		inline virtual void SetTrajectoryData(const spatial::trajectory_data_t& r) { spatial_origin_data_.CTPairData.second = r; }
		inline virtual void SetH(const float r) { spatial_origin_data_.CTPairData.second.x = r; }
		inline virtual void SetV(const float r) { spatial_origin_data_.CTPairData.second.y = r; }
		inline virtual void SetHeading(const float r) { spatial_origin_data_.CTPairData.second.z = r; }
		inline virtual void SetVelocity(const float r) { spatial_origin_data_.CTPairData.second.w = r; }
		
	protected:

		inline void ForceSpatialOriginData(const formats::SpatialOriginData& r) { spatial_origin_data_ = r; }
		
		inline void ForceOriginDimensionData(const spatial::dimension_data_t& r) { spatial_origin_data_.DimensionData = r; }
		inline void ForceOriginHeight(const float r) { spatial_origin_data_.DimensionData.x = r; }
		inline void ForceOriginWidth(const float r) { spatial_origin_data_.DimensionData.y = r; }
		inline void ForceOriginDepth(const float r) { spatial_origin_data_.DimensionData.z = r; }

		inline void ForceOriginDistortionData(const spatial::distortion_data_t& r) { spatial_origin_data_.DistortionData = r; }
		inline void ForceOriginHeightDistortion(const float r) { spatial_origin_data_.DistortionData.x = r; }
		inline void ForceOriginWidthDistortion(const float r) { spatial_origin_data_.DistortionData.y = r; }
		inline void ForceOriginDepthDistortion(const float r) { spatial_origin_data_.DistortionData.z = r; }
		inline void ForceOriginSize(const float r) { spatial_origin_data_.DistortionData.w = r; }

		inline void ForceOriginOrientationData(const spatial::orientation_data_t& r) { spatial_origin_data_.OrientationData = r; }
		inline void ForceOriginYaw(const float r) { spatial_origin_data_.OrientationData.x = r; }
		inline void ForceOriginPitch(const float r) { spatial_origin_data_.OrientationData.y = r; }
		inline void ForceOriginRoll(const float r) { spatial_origin_data_.OrientationData.z = r; }

		inline void ForceOriginMomentumData(const spatial::momentum_data_t& r) { spatial_origin_data_.MomentumData = r; }
		inline void ForceOriginYawDelta(const float r) { spatial_origin_data_.MomentumData.x = r; }
		inline void ForceOriginPitchDelta(const float r) { spatial_origin_data_.MomentumData.y = r; }
		inline void ForceOriginRollDelta(const float r) { spatial_origin_data_.MomentumData.z = r; }

		inline void ForceOriginZOffsetData(const spatial::z_offset_data_t& r) { spatial_origin_data_.ZOffsetData = r; }
		inline void ForceOriginGroundOffset(const float r) { spatial_origin_data_.ZOffsetData.x = r; }
		inline void ForceOriginHoverOffset(const float r) { spatial_origin_data_.ZOffsetData.y = r; }
		inline void ForceOriginJumpOffset(const float r) { spatial_origin_data_.ZOffsetData.z = r; }
		inline void ForceOriginFlyingOffset(const float r) { spatial_origin_data_.ZOffsetData.w = r; }

		inline void ForceCTPairData(const spatial::ct_pair_data_t& r) { spatial_origin_data_.CTPairData = r; }

		inline void ForceCoordinateData(const spatial::coordinate_data_t& r) { spatial_origin_data_.CTPairData.first = r; }
		inline void ForceX(const float r) { spatial_origin_data_.CTPairData.first.x = r; }
		inline void ForceY(const float r) { spatial_origin_data_.CTPairData.first.y = r; }
		inline void ForceZ(const float r) { spatial_origin_data_.CTPairData.first.z = r; }

		inline void ForceTrajectoryData(const spatial::trajectory_data_t& r) { spatial_origin_data_.CTPairData.second = r; }
		inline void ForceH(const float r) { spatial_origin_data_.CTPairData.second.x = r; }
		inline void ForceV(const float r) { spatial_origin_data_.CTPairData.second.y = r; }
		inline void ForceHeading(const float r) { spatial_origin_data_.CTPairData.second.z = r; }
		inline void ForceVelocity(const float r) { spatial_origin_data_.CTPairData.second.w = r; }

		formats::SpatialOriginData spatial_origin_data_;
	};

	struct SpatialDynamicAttributes {
		SpatialDynamicAttributes() { }
		SpatialDynamicAttributes(const SpatialDynamicAttributes& r) : spatial_dynamic_data_(r.spatial_dynamic_data_) { }
		SpatialDynamicAttributes(const formats::SpatialDynamicData& r) : spatial_dynamic_data_(r) { }
		virtual ~SpatialDynamicAttributes() { }

		inline const formats::SpatialDynamicData& GetSpatialDynamicData() const { return spatial_dynamic_data_; }
		inline virtual formats::SpatialDynamicData& GetSpatialDynamicData() { return spatial_dynamic_data_; }

		inline const spatial::dimension_data_t& GetDimensionData() const { return spatial_dynamic_data_.DimensionData; }
		inline virtual spatial::dimension_data_t& GetDimensionData() { return spatial_dynamic_data_.DimensionData; }
		inline float GetHeight() const { return spatial_dynamic_data_.DimensionData.x; }
		inline float GetWidth() const { return spatial_dynamic_data_.DimensionData.y; }
		inline float GetDepth() const { return spatial_dynamic_data_.DimensionData.z; }

		inline const spatial::distortion_data_t& GetDistortionData() const { return spatial_dynamic_data_.DistortionData; }
		inline virtual spatial::distortion_data_t& GetDistortionData() { return spatial_dynamic_data_.DistortionData; }
		inline float GetHeightDistortion() const { return spatial_dynamic_data_.DistortionData.x; }
		inline float GetWidthDistortion() const { return spatial_dynamic_data_.DistortionData.y; }
		inline float GetDepthDistortion() const { return spatial_dynamic_data_.DistortionData.z; }
		inline float GetSize() const { return spatial_dynamic_data_.DistortionData.w; }

		inline const spatial::orientation_data_t& GetOrientationData() const { return spatial_dynamic_data_.OrientationData; }
		inline virtual spatial::orientation_data_t& GetOrientationData() { return spatial_dynamic_data_.OrientationData; }
		inline float GetYaw() const { return spatial_dynamic_data_.OrientationData.x; }
		inline float GetPitch() const { return spatial_dynamic_data_.OrientationData.y; }
		inline float GetRoll() const { return spatial_dynamic_data_.OrientationData.z; }

		inline const spatial::momentum_data_t& GetMomentumData() const { return spatial_dynamic_data_.MomentumData; }
		inline virtual spatial::momentum_data_t& GetMomentumData() { return spatial_dynamic_data_.MomentumData; }
		inline float GetYawDelta() const { return spatial_dynamic_data_.MomentumData.x; }
		inline float GetPitchDelta() const { return spatial_dynamic_data_.MomentumData.y; }
		inline float GetRollDelta() const { return spatial_dynamic_data_.MomentumData.z; }

		inline const spatial::z_offset_data_t& GetZOffsetData() const { return spatial_dynamic_data_.ZOffsetData; }
		inline virtual spatial::z_offset_data_t& GetZOffsetData() { return spatial_dynamic_data_.ZOffsetData; }
		inline float GetGroundOffset() const { return spatial_dynamic_data_.ZOffsetData.x; }
		inline float GetHoverOffset() const { return spatial_dynamic_data_.ZOffsetData.y; }
		inline float GetJumpOffset() const { return spatial_dynamic_data_.ZOffsetData.z; }
		inline float GetFlyingOffset() const { return spatial_dynamic_data_.ZOffsetData.w; }

		inline const spatial::ct_pair_data_t& GetLastCTPairData() const { return spatial_dynamic_data_.LastCTPairData; }
		inline virtual spatial::ct_pair_data_t& GetLastCTPairData() { return spatial_dynamic_data_.LastCTPairData; }

		inline const spatial::coordinate_data_t& GetLastCoordinateData() const { return spatial_dynamic_data_.LastCTPairData.first; }
		inline virtual spatial::coordinate_data_t& GetLastCoordinateData() { return spatial_dynamic_data_.LastCTPairData.first; }
		inline float GetLastX() const { return spatial_dynamic_data_.LastCTPairData.first.x; }
		inline float GetLastY() const { return spatial_dynamic_data_.LastCTPairData.first.y; }
		inline float GetLastZ() const { return spatial_dynamic_data_.LastCTPairData.first.z; }

		inline const spatial::trajectory_data_t& GetLastTrajectoryData() const { return spatial_dynamic_data_.LastCTPairData.second; }
		inline virtual spatial::trajectory_data_t& GetLastTrajectoryData() { return spatial_dynamic_data_.LastCTPairData.second; }
		inline float GetLastH() const { return spatial_dynamic_data_.LastCTPairData.second.x; }
		inline float GetLastV() const { return spatial_dynamic_data_.LastCTPairData.second.y; }
		inline float GetLastHeading() const { return spatial_dynamic_data_.LastCTPairData.second.z; }
		inline float GetLastVelocity() const { return spatial_dynamic_data_.LastCTPairData.second.w; }

		inline const spatial::ct_pair_data_t& GetNextCTPairData() const { return spatial_dynamic_data_.NextCTPairData; }
		inline virtual spatial::ct_pair_data_t& GetNextCTPairData() { return spatial_dynamic_data_.NextCTPairData; }

		inline const spatial::coordinate_data_t& GetNextCoordinateData() const { return spatial_dynamic_data_.NextCTPairData.first; }
		inline virtual spatial::coordinate_data_t& GetNextCoordinateData() { return spatial_dynamic_data_.NextCTPairData.first; }
		inline float GetNextX() const { return spatial_dynamic_data_.NextCTPairData.first.x; }
		inline float GetNextY() const { return spatial_dynamic_data_.NextCTPairData.first.y; }
		inline float GetNextZ() const { return spatial_dynamic_data_.NextCTPairData.first.z; }

		inline const spatial::trajectory_data_t& GetNextTrajectoryData() const { return spatial_dynamic_data_.NextCTPairData.second; }
		inline virtual spatial::trajectory_data_t& GetNextTrajectoryData() { return spatial_dynamic_data_.NextCTPairData.second; }
		inline float GetNextH() const { return spatial_dynamic_data_.NextCTPairData.second.x; }
		inline float GetNextV() const { return spatial_dynamic_data_.NextCTPairData.second.y; }
		inline float GetNextHeading() const { return spatial_dynamic_data_.NextCTPairData.second.z; }
		inline float GetNextVelocity() const { return spatial_dynamic_data_.NextCTPairData.second.w; }
		
		inline const spatial::waypoint_list_t* GetLastWaypointList() const { return spatial_dynamic_data_.LastWaypointList; }
		virtual spatial::waypoint_list_t& GetLastWaypointList();

		inline const spatial::waypoint_list_t* GetNextWaypointList() const { return spatial_dynamic_data_.NextWaypointList; }
		virtual spatial::waypoint_list_t& GetNextWaypointList();

		inline spatial::pair_t GetHeightAndDistortion() const { return spatial::pair_t(spatial_dynamic_data_.DimensionData.x, spatial_dynamic_data_.DistortionData.x); }
		inline spatial::pair_t GetWidthAndDistortion() const { return spatial::pair_t(spatial_dynamic_data_.DimensionData.y, spatial_dynamic_data_.DistortionData.y); }
		inline spatial::pair_t GetDepthAndDistortion() const { return spatial::pair_t(spatial_dynamic_data_.DimensionData.z, spatial_dynamic_data_.DistortionData.z); }
		
		inline spatial::pair_t GetYawAndDelta() const { return spatial::pair_t(spatial_dynamic_data_.OrientationData.x, spatial_dynamic_data_.MomentumData.x); }
		inline spatial::pair_t GetPitchAndDelta() const { return spatial::pair_t(spatial_dynamic_data_.OrientationData.y, spatial_dynamic_data_.MomentumData.y); }
		inline spatial::pair_t GetRollAndDelta() const { return spatial::pair_t(spatial_dynamic_data_.OrientationData.z, spatial_dynamic_data_.MomentumData.z); }
		
		inline spatial::pair_t GetLastHV() const { return spatial::pair_t(spatial_dynamic_data_.LastCTPairData.second.x, spatial_dynamic_data_.LastCTPairData.second.y); }
		inline spatial::pair_t GetLastHeadingVelocity() const { return spatial::pair_t(spatial_dynamic_data_.LastCTPairData.second.z, spatial_dynamic_data_.LastCTPairData.second.w); }
		inline spatial::triple_t GetLastHVVelocity() const { return spatial::triple_t(spatial_dynamic_data_.LastCTPairData.second.x, spatial_dynamic_data_.LastCTPairData.second.y, spatial_dynamic_data_.LastCTPairData.second.w); }
		
		inline spatial::pair_t GetNextHV() const { return spatial::pair_t(spatial_dynamic_data_.NextCTPairData.second.x, spatial_dynamic_data_.NextCTPairData.second.y); }
		inline spatial::pair_t GetNextHeadingVelocity() const { return spatial::pair_t(spatial_dynamic_data_.NextCTPairData.second.z, spatial_dynamic_data_.NextCTPairData.second.w); }
		inline spatial::triple_t GetNextHVVelocity() const { return spatial::triple_t(spatial_dynamic_data_.NextCTPairData.second.x, spatial_dynamic_data_.NextCTPairData.second.y, spatial_dynamic_data_.NextCTPairData.second.w); }
		
		inline virtual void SetSpatialData(const formats::SpatialDynamicData& r) { spatial_dynamic_data_ = r; }

		inline virtual void SetDimensionData(const spatial::dimension_data_t& r) { spatial_dynamic_data_.DimensionData = r; }
		inline virtual void SetHeight(const float r) { spatial_dynamic_data_.DimensionData.x = r; }
		inline virtual void SetWidth(const float r) { spatial_dynamic_data_.DimensionData.y = r; }
		inline virtual void SetDepth(const float r) { spatial_dynamic_data_.DimensionData.z = r; }

		inline virtual void SetDistortionData(const spatial::distortion_data_t& r) { spatial_dynamic_data_.DistortionData = r; }
		inline virtual void SetHeightDistortion(const float r) { spatial_dynamic_data_.DistortionData.x = r; }
		inline virtual void SetWidthDistortion(const float r) { spatial_dynamic_data_.DistortionData.y = r; }
		inline virtual void SetDepthDistortion(const float r) { spatial_dynamic_data_.DistortionData.z = r; }
		inline virtual void SetSize(const float r) { spatial_dynamic_data_.DistortionData.w = r; }

		inline virtual void SetOrientationData(const spatial::orientation_data_t& r) { spatial_dynamic_data_.OrientationData = r; }
		inline virtual void SetYaw(const float r) { spatial_dynamic_data_.OrientationData.x = r; }
		inline virtual void SetPitch(const float r) { spatial_dynamic_data_.OrientationData.y = r; }
		inline virtual void SetRoll(const float r) { spatial_dynamic_data_.OrientationData.z = r; }

		inline virtual void SetMomentumData(const spatial::momentum_data_t& r) { spatial_dynamic_data_.MomentumData = r; }
		inline virtual void SetYawDelta(const float r) { spatial_dynamic_data_.MomentumData.x = r; }
		inline virtual void SetPitchDelta(const float r) { spatial_dynamic_data_.MomentumData.y = r; }
		inline virtual void SetRollDelta(const float r) { spatial_dynamic_data_.MomentumData.z = r; }

		inline virtual void SetZOffsetData(const spatial::z_offset_data_t& r) { spatial_dynamic_data_.ZOffsetData = r; }
		inline virtual void SetGroundOffset(const float r) { spatial_dynamic_data_.ZOffsetData.x = r; }
		inline virtual void SetHoverOffset(const float r) { spatial_dynamic_data_.ZOffsetData.y = r; }
		inline virtual void SetJumpOffset(const float r) { spatial_dynamic_data_.ZOffsetData.z = r; }
		inline virtual void SetFlyingOffset(const float r) { spatial_dynamic_data_.ZOffsetData.w = r; }

		inline virtual void SetLastCTPairData(const spatial::ct_pair_data_t& r) { spatial_dynamic_data_.LastCTPairData = r; }

		inline virtual void SetLastCoordinateData(const spatial::coordinate_data_t& r) { spatial_dynamic_data_.LastCTPairData.first = r; }
		inline virtual void SetLastX(const float r) { spatial_dynamic_data_.LastCTPairData.first.x = r; }
		inline virtual void SetLastY(const float r) { spatial_dynamic_data_.LastCTPairData.first.y = r; }
		inline virtual void SetLastZ(const float r) { spatial_dynamic_data_.LastCTPairData.first.z = r; }

		inline virtual void SetLastTrajectoryData(const spatial::trajectory_data_t& r) { spatial_dynamic_data_.LastCTPairData.second = r; }
		inline virtual void SetLastH(const float r) { spatial_dynamic_data_.LastCTPairData.second.x = r; }
		inline virtual void SetLastV(const float r) { spatial_dynamic_data_.LastCTPairData.second.y = r; }
		inline virtual void SetLastHeading(const float r) { spatial_dynamic_data_.LastCTPairData.second.z = r; }
		inline virtual void SetLastVelocity(const float r) { spatial_dynamic_data_.LastCTPairData.second.w = r; }

		inline virtual void SetNextCTPairData(const spatial::ct_pair_data_t& r) { spatial_dynamic_data_.NextCTPairData = r; }

		inline virtual void SetNextCoordinateData(const spatial::coordinate_data_t& r) { spatial_dynamic_data_.NextCTPairData.first = r; }
		inline virtual void SetNextX(const float r) { spatial_dynamic_data_.NextCTPairData.first.x = r; }
		inline virtual void SetNextY(const float r) { spatial_dynamic_data_.NextCTPairData.first.y = r; }
		inline virtual void SetNextZ(const float r) { spatial_dynamic_data_.NextCTPairData.first.z = r; }
		
		inline virtual void SetNextTrajectoryData(const spatial::trajectory_data_t& r) { spatial_dynamic_data_.NextCTPairData.second = r; }
		inline virtual void SetNextH(const float r) { spatial_dynamic_data_.NextCTPairData.second.x = r; }
		inline virtual void SetNextV(const float r) { spatial_dynamic_data_.NextCTPairData.second.y = r; }
		inline virtual void SetNextHeading(const float r) { spatial_dynamic_data_.NextCTPairData.second.z = r; }
		inline virtual void SetNextVelocity(const float r) { spatial_dynamic_data_.NextCTPairData.second.w = r; }

		virtual void SetLastWaypointList(const spatial::waypoint_list_t& r);

		virtual void SetNextWaypointList(const spatial::waypoint_list_t& r);

	protected:

		inline void ForceSpatialData(const formats::SpatialDynamicData& r) { spatial_dynamic_data_ = r; }

		inline void ForceDimensionData(const spatial::dimension_data_t& r) { spatial_dynamic_data_.DimensionData = r; }
		inline void ForceHeight(const float r) { spatial_dynamic_data_.DimensionData.x = r; }
		inline void ForceWidth(const float r) { spatial_dynamic_data_.DimensionData.y = r; }
		inline void ForceDepth(const float r) { spatial_dynamic_data_.DimensionData.z = r; }

		inline void ForceDistortionData(const spatial::distortion_data_t& r) { spatial_dynamic_data_.DistortionData = r; }
		inline void ForceHeightDistortion(const float r) { spatial_dynamic_data_.DistortionData.x = r; }
		inline void ForceWidthDistortion(const float r) { spatial_dynamic_data_.DistortionData.y = r; }
		inline void ForceDepthDistortion(const float r) { spatial_dynamic_data_.DistortionData.z = r; }
		inline void ForceSize(const float r) { spatial_dynamic_data_.DistortionData.w = r; }

		inline void ForceOrientationData(const spatial::orientation_data_t& r) { spatial_dynamic_data_.OrientationData = r; }
		inline void ForceYaw(const float r) { spatial_dynamic_data_.OrientationData.x = r; }
		inline void ForcePitch(const float r) { spatial_dynamic_data_.OrientationData.y = r; }
		inline void ForceRoll(const float r) { spatial_dynamic_data_.OrientationData.z = r; }

		inline void ForceMomentumData(const spatial::momentum_data_t& r) { spatial_dynamic_data_.MomentumData = r; }
		inline void ForceYawDelta(const float r) { spatial_dynamic_data_.MomentumData.x = r; }
		inline void ForcePitchDelta(const float r) { spatial_dynamic_data_.MomentumData.y = r; }
		inline void ForceRollDelta(const float r) { spatial_dynamic_data_.MomentumData.z = r; }

		inline void ForceZOffsetData(const spatial::z_offset_data_t& r) { spatial_dynamic_data_.ZOffsetData = r; }
		inline void ForceGroundOffset(const float r) { spatial_dynamic_data_.ZOffsetData.x = r; }
		inline void ForceHoverOffset(const float r) { spatial_dynamic_data_.ZOffsetData.y = r; }
		inline void ForceJumpOffset(const float r) { spatial_dynamic_data_.ZOffsetData.z = r; }
		inline void ForceFlyingOffset(const float r) { spatial_dynamic_data_.ZOffsetData.w = r; }

		inline void ForceLastCTPairData(const spatial::ct_pair_data_t& r) { spatial_dynamic_data_.LastCTPairData = r; }

		inline void ForceLastCoordinateData(const spatial::coordinate_data_t& r) { spatial_dynamic_data_.LastCTPairData.first = r; }
		inline void ForceLastX(const float r) { spatial_dynamic_data_.LastCTPairData.first.x = r; }
		inline void ForceLastY(const float r) { spatial_dynamic_data_.LastCTPairData.first.y = r; }
		inline void ForceLastZ(const float r) { spatial_dynamic_data_.LastCTPairData.first.z = r; }

		inline void ForceLastTrajectoryData(const spatial::trajectory_data_t& r) { spatial_dynamic_data_.LastCTPairData.second = r; }
		inline void ForceLastH(const float r) { spatial_dynamic_data_.LastCTPairData.second.x = r; }
		inline void ForceLastV(const float r) { spatial_dynamic_data_.LastCTPairData.second.y = r; }
		inline void ForceLastHeading(const float r) { spatial_dynamic_data_.LastCTPairData.second.z = r; }
		inline void ForceLastVelocity(const float r) { spatial_dynamic_data_.LastCTPairData.second.w = r; }

		inline void ForceNextCTPairData(const spatial::ct_pair_data_t& r) { spatial_dynamic_data_.NextCTPairData = r; }

		inline void ForceNextCoordinateData(const spatial::coordinate_data_t& r) { spatial_dynamic_data_.NextCTPairData.first = r; }
		inline void ForceNextX(const float r) { spatial_dynamic_data_.NextCTPairData.first.x = r; }
		inline void ForceNextY(const float r) { spatial_dynamic_data_.NextCTPairData.first.y = r; }
		inline void ForceNextZ(const float r) { spatial_dynamic_data_.NextCTPairData.first.z = r; }

		inline void ForceNextTrajectoryData(const spatial::trajectory_data_t& r) { spatial_dynamic_data_.NextCTPairData.second = r; }
		inline void ForceNextH(const float r) { spatial_dynamic_data_.NextCTPairData.second.x = r; }
		inline void ForceNextV(const float r) { spatial_dynamic_data_.NextCTPairData.second.y = r; }
		inline void ForceNextHeading(const float r) { spatial_dynamic_data_.NextCTPairData.second.z = r; }
		inline void ForceNextVelocity(const float r) { spatial_dynamic_data_.NextCTPairData.second.w = r; }

		void ForceLastWaypointList(const spatial::waypoint_list_t& r);

		void ForceNextWaypointList(const spatial::waypoint_list_t& r);

		formats::SpatialDynamicData spatial_dynamic_data_;
	};

} // namespace profiles
