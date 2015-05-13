// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "DoViDisplay.h"

namespace DoVi {

	void Display::SetParentNode( const spINode & parentNode ) {
		_parent = parentNode;
	}

	spcINode Display::GetParentNode() const {
		return _parent;
	}

	spINode Display::GetParentNode() {
		return _parent;
	}

	const std::string & Display::GetNameSpace() const {
		return sGetNameSpace();
	}

	const std::string & Display::GetName() const {
		return sGetName();
	}

	std::string Display::getID() {
		return _id;
	}

	void Display::setID( const std::string & id ) {
		_id = id;
	}

	std::string Display::getName() {
		return _name;
	}

	void Display::setName( const std::string & n ) {
		_name = n;
	}

	double Display::getDiagonalSize() {
		return _diagonalSize;
	}

	void Display::setDiagonalSize( const double & dz ) {
		_diagonalSize = dz;
	}

	Display::Display()
		: _diagonalSize( 32.0 ) { }

	Display::~Display() {

	}

	const std::string & Display::sGetNameSpace() {
		static std::string nameSpace( "www.dolby.com/1.0/" );
		return nameSpace;
	}

	const std::string & Display::sGetName() {
		static std::string name( "display" );
		return name;
	}

}