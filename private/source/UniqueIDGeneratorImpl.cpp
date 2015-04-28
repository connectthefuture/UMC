// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "implHeaders/UniqueIDGeneratorImpl.h"
#include <assert.h>
#include <cstdio>

namespace INT_UMC {

	UniqueIDGeneratorImpl::UniqueIDGeneratorImpl( const spcUniqueIDSet & uniqueIDSet )
		: mUniqueIDSet( uniqueIDSet )
		, mCurrentID( 1 ) { }

	std::string UniqueIDGeneratorImpl::GenerateUniqueID( INode::eNodeTypes nodeType ) {
		static char buffer[ 30 ] = "";
	#if UMC_UNIXBuild
		snprintf ( buffer, 30, "%d", mCurrentID );
	#elif UMC_WinBuild
		sprintf_s( buffer, 30, "%d", mCurrentID );
	#else
		#error "Missing implementation for the platform"
	#endif
		mCurrentID++;
		assert( mUniqueIDSet->find( buffer ) == mUniqueIDSet->end() );
		return std::string( buffer );
	}

	spIUniqueIDGenerator UniqueIDGeneratorImpl::CreateUniqueIDGenerator( const spcUniqueIDSet & uniqueIDSet ) {
		return std::make_shared< UniqueIDGeneratorImpl, const spcUniqueIDSet & >( uniqueIDSet );
	}

}
