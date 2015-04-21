#ifndef IShot_h__
#define IShot_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"

#include <string>
#include <vector>

namespace UMC {

	class IShot {

	public:
		typedef enum {
			kShotTypeClip			= 0,
			kShotTypeTransition		= 1,

			kShotTypeAll			= Max_UMC_Uns32 - 1,
			kShotTypeMaxValue		= Max_UMC_Uns32

		} eShotTypes;

		typedef std::vector< spIFrame > FrameList;
		typedef std::vector< spcIFrame > cFrameList;

		typedef std::vector< spIShotSource > ShotSourceList;
		typedef std::vector< spcIShotSource > cShotSourceList;

		virtual std::string GetUniqueID() const = 0;

		virtual eShotTypes GetType() const = 0;

		virtual void SetInCount( const EditUnitInCount & inCount ) = 0;
		virtual EditUnitInCount GetInCount() const = 0;

		virtual void SetDuration( const EditUnitDuration & duration ) = 0;
		virtual EditUnitDuration GetDuration() const = 0;

		virtual spIFrame AddFrame( const spISource & frameSource, const char * uniqueID,
			size_t lengthOfID = npos, const EditUnitInCount & sourceInCount = kEditUnitInCountFromBeginning,
			const EditUnitInCount shotInCount = kEditUnitInCountFromBeginning ) = 0;

		virtual spIShotSource AddShotSource( const spISource & shotSource,
			const EditUnitInCount & sourceInCount = kEditUnitInCountFromBeginning,
			const EditUnitDuration sourceDuration = kEditUnitDurationTillEnd,
			const EditUnitInCount shotInCount = 0 ) = 0;

		virtual size_t FrameCount() const = 0;
		virtual FrameList GetFrames() = 0;
		virtual cFrameList GetFrames() const = 0;
		virtual spIFrame GetFrame( const char * uniqueID, size_t length = npos ) = 0;

		virtual size_t ShotSourceCount() const = 0;
		virtual ShotSourceList GetShotSources() = 0;
		virtual cShotSourceList GetShotSources() const = 0;

		virtual spcITrack GetParent() const = 0;
		virtual spITrack GetParent() = 0;

		virtual ~IShot() = 0;

	private:

	};

	inline IShot::~IShot() {}

};

#endif  // IShot_h__