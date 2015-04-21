#ifndef FrameImpl_h__
#define FrameImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IFrame.h"
#include "UMCDefines_I.h"
#include <map>
#include "interfaces/ISource.h"

#include <string>

namespace INT_UMC {
	using namespace UMC;
	class FrameImpl
		: public IFrame
		, public enable_shared_from_this< FrameImpl >
	{
	public:
		FrameImpl( const std::string & uniqueID, const spISource & frameSource,
			const spIShot & parent, const EditUnitInCount & sourceInCount = kEditUnitInCountFromBeginning,
			const EditUnitInCount & shotInCount = kEditUnitInCountFromBeginning );

		virtual std::string GetUniqueID() const;

		virtual spcIShot GetParent() const;
		virtual spIShot GetParent();

		virtual spISource GetSource();
		virtual spcISource GetSource() const;

		virtual void SetSourceInCount( const EditUnitInCount & sourceInCount );
		virtual EditUnitInCount GetSourceInCount() const;

		virtual void SetShotInCount( const EditUnitInCount & shotInCount );
		virtual EditUnitInCount GetShotInCount() const;

	protected:
		weak_ptr< IShot >		mwpShot;
		weak_ptr< ISource >		mwpSource;
		EditUnitInCount			mSourceInCount;
		EditUnitInCount			mShotInCount;
		std::string				mUniqueID;
	};
}

#endif  // FrameImpl_h__