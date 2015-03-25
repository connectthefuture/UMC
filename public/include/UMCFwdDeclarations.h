#ifndef UMCFwdDeclarations_h__
#define UMCFwdDeclarations_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "UMCDefines.h"
#include "baseTypes/SmartPointers.h"

namespace UMC {

	// ISource
	class ISource;
	typedef ISource *								pISource;
	typedef const ISource *							pcISource;
	typedef shared_ptr< ISource >					spISource;
	typedef shared_ptr< const ISource >				spcISource;

	// IUMC
	class IUMC;
	typedef IUMC *									pIUMC;
	typedef const IUMC *							pcIUMC;
	typedef shared_ptr< IUMC >						spIUMC;
	typedef shared_ptr< const IUMC >				spcIUMC;

	// IOutput
	class IOutput;
	typedef IOutput *								pIOutput;
	typedef const IOutput *							pcIOutput;
	typedef shared_ptr< IOutput >					spIOutput;
	typedef shared_ptr< const IOutput >				spcIOutput;

	// ITrack
	class ITrack;
	typedef ITrack *								pITrack;
	typedef const ITrack *							pcITrack;
	typedef shared_ptr< ITrack >					spITrack;
	typedef shared_ptr< const ITrack >				spcITrack;

	// IShot
	class IShot;
	typedef IShot *									pIShot;
	typedef const IShot *							pcIShot;
	typedef shared_ptr< IShot >						spIShot;
	typedef shared_ptr< const IShot >				spcIShot;

	// IFrame
	class IFrame;
	typedef IFrame *								pIFrame;
	typedef const IFrame *							pcIFrame;
	typedef shared_ptr< IFrame >					spIFrame;
	typedef shared_ptr< const IFrame >				spcIFrame;

	// IShotSource
	class IShotSource;	
	typedef IShotSource *							pIShotSource;
	typedef const IShotSource *						pcIShotSource;
	typedef shared_ptr< IShotSource >				spIShotSource;
	typedef shared_ptr< const IShotSource >			spcIShotSource;

};

#endif  // UMCFwdDeclarations_h__
