#ifndef DoviDisplay_h__
#define DoviDisplay_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ICustomData.h"
#include "interfaces/INode.h"

namespace DoVi {
	using namespace UMC;

	class Display
		: public UMC::ICustomData
	{
	public:
		Display();
		std::string getID();
		void setID( const std::string & id );
		std::string getName();
		void setName( const std::string & n );
		double getDiagonalSize();
		void setDiagonalSize( const double & dz );

		virtual void SetParentNode( const spINode & parentNode );

		virtual spcINode GetParentNode() const;
		virtual spINode GetParentNode();

		virtual const std::string & GetNameSpace() const;
		virtual const std::string & GetName() const;
		virtual ~Display();

		static const std::string & sGetNameSpace();
		static const std::string & sGetName();

	protected:
		std::string		_id;
		std::string		_name;
		double			_diagonalSize;
		spINode			_parent;
	};
}

#endif  // DoviDisplay_h__
