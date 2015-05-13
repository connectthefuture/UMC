#ifndef ICustomData_h__
#define ICustomData_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "UMCFwdDeclarations.h"

namespace UMC {

	class ICustomData {
	
	public:
		virtual void SetParentNode( const spINode & parentNode ) = 0;

		virtual spcINode GetParentNode() const = 0;
		virtual spINode GetParentNode() = 0;
	};
}

#endif  // ICustomData_h__