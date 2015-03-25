#ifndef TrackImpl_h__
#define TrackImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ITrack.h"
#include "UMCDefines_I.h"
#include "interfaces/IShot.h"

#include <string>
#include <map>

namespace INT_UMC {
	using namespace UMC;
	class TrackImpl
		: public ITrack
		, public enable_shared_from_this< TrackImpl >
	{
	public:
		TrackImpl( const std::string & uniqueID, const spIOutput & parent );

		virtual std::string GetUniqueID() const;

		virtual spIShot AddClipShot( const char * uniqueID, size_t length );
		virtual spIShot AddTransitionShot( const char * uniqueID, size_t length );

		virtual void SetName( const char * outputName, size_t length );
		virtual std::string GetName() const;

		virtual void SetEditRate( const EditRate & editRate );
		virtual EditRate GetEditRate() const;

		virtual size_t ShotCount() const;
		virtual ShotList GetShots();
		virtual cShotList GetShots() const;

		virtual spcIOutput GetParent() const;
		virtual spIOutput GetParent();

	protected:
		spIShot AddShot( const char * uniqueID, size_t length, IShot::eShotTypes type );

		typedef std::map< const std::string, spIShot > ShotMap;

		std::string				mUniqueID;
		std::string				mName;
		EditRate				mEditRate;
		weak_ptr< IOutput >		mwpOutput;
		ShotMap					mShotMap;
	};
}

#endif  // TrackImpl_h__
