// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/ShotImpl.h"
#include "implHeaders/FrameImpl.h"
#include "implHeaders/ShotSourceImpl.h"
#include "utils/Utils.h"

namespace INT_UMC {

	const std::string & ShotImpl::GetUniqueID() const {
		return mNode->GetUniqueID();
	}

	IShot::eShotTypes ShotImpl::GetType() const {
		return IShot::kShotTypeAll;
	}

	void ShotImpl::SetInCount( const EditUnitInCount & inCount ) {
		mInCount = inCount;
	}

	EditUnitInCount ShotImpl::GetInCount() const {
		return mInCount;
	}

	void ShotImpl::SetDuration( const EditUnitDuration & duration ) {
		mDuration = duration;
	}

	EditUnitDuration ShotImpl::GetDuration() const {
		return mDuration;
	}

	spIFrame ShotImpl::AddFrame( const spISource & source )
	{
		spIFrame frame = CreateFrame( GetUniqueIDAndReferenceTracker(), GetUniqueIDGenerator(), source );
		AddElementToMap( mFrameMap, frame, shared_from_this() );
		return frame;
	}

	size_t ShotImpl::FrameCount() const {
		return mFrameMap.size();
	}

	IShot::FrameList ShotImpl::GetFrames() {
		return CreateListFromMap< spIFrame >( mFrameMap );
	}

	IShot::cFrameList ShotImpl::GetFrames() const {
		return CreateListFromMap< spcIFrame >( mFrameMap );
	}

	spIShotSource ShotImpl::AddShotSource( const spISource & source )
	{
		spIShotSource shotSource = CreateShotSource( GetUniqueIDAndReferenceTracker(), GetUniqueIDGenerator(), source );
		AddElementToMap( mShotSourceMap, shotSource, shared_from_this() );
		return shotSource;
	}

	size_t ShotImpl::ShotSourceCount() const {
		return mShotSourceMap.size();
	}

	IShot::ShotSourceList ShotImpl::GetShotSources() {
		return CreateListFromMap< spIShotSource >( mShotSourceMap );
	}

	IShot::cShotSourceList ShotImpl::GetShotSources() const {
		return CreateListFromMap< spcIShotSource >( mShotSourceMap );
	}

	spIShotSource ShotImpl::GetShotSource( const std::string & uniqueID ) {
		return GetElementFromMap< spIShotSource >( mShotSourceMap, uniqueID );
	}

	spcIShotSource ShotImpl::GetShotSource( const std::string & uniqueID ) const {
		return const_cast< ShotImpl *>( this )->GetShotSource( uniqueID );
	}

	wpcINode ShotImpl::GetParentNode() const {
		return mNode->GetParentNode();
	}

	wpINode ShotImpl::GetParentNode() {
		return mNode->GetParentNode();
	}

	INode::eNodeTypes ShotImpl::GetNodeType() const {
		return kNodeTypeOutput;
	}

	spcINode ShotImpl::GetDecendantNode( const std::string & id ) const {
		return const_cast< ShotImpl * >( this )->GetDecendantNode( id );
	}

	spINode ShotImpl::GetDecendantNode( const std::string & id ) {
		auto node = GetChildNode( id );
		if ( node ) return node;
		node = GetDecendantFromMap( mShotSourceMap, id );
		return node;
	}

	spcINode ShotImpl::GetChildNode( const std::string & id ) const {
		return const_cast< ShotImpl * >( this )->GetChildNode( id );
	}

	spINode ShotImpl::GetChildNode( const std::string & id ) {
		return GetShotSource( id );
	}

	INode::NodeList ShotImpl::GetAllChildren() {
		NodeList list;
		AppendToListFromMap< spINode, ShotSourceMap >( list, mShotSourceMap );
		return list;
	}

	INode::cNodeList ShotImpl::GetAllChildren() const {
		cNodeList list;
		AppendToListFromMap< spcINode, ShotSourceMap >( list, mShotSourceMap );
		return list;
	}

	INode::NodeList ShotImpl::GetAllDecendants() {
		NodeList list;
		AppendDecendantsFromMapToList< spINode >( list, mShotSourceMap );
		return list;
	}

	INode::cNodeList ShotImpl::GetAllDecendants() const {
		cNodeList list;
		AppendDecendantsFromMapToList< spcINode >( list, mShotSourceMap );
		return list;
	}

	size_t ShotImpl::GetReferenceCount() const {
		return mNode->GetReferenceCount();
	}

	spICustomData ShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData ShotImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return mNode->GetCustomData( customDataNameSpace, customDataName );
	}

	bool ShotImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return mNode->SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pINodeI ShotImpl::GetInternalNode() {
		return this;
	}

	pcINodeI ShotImpl::GetInternalNode() const {
		return this;
	}

	void ShotImpl::SetExtensionNode( const spIXMPStructureNode & structureNode ) {
		mNode->GetInternalNode()->SetExtensionNode( structureNode );
	}

	NS_XMPCORE::spIXMPStructureNode ShotImpl::GetExtensionNode(bool create /*= false */) const {
		return mNode->GetInternalNode()->GetExtensionNode( create );
	}

	NS_XMPCORE::spIXMPStructureNode ShotImpl::GetMergedExtensionNode() const {
		return mNode->GetInternalNode()->GetMergedExtensionNode();
	}

	spIUniqueIDAndReferenceTracker ShotImpl::GetUniqueIDAndReferenceTracker() {
		return mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker();
	}

	spcIUniqueIDAndReferenceTracker ShotImpl::GetUniqueIDAndReferenceTracker() const {
		return mNode->GetInternalNode()->GetUniqueIDAndReferenceTracker();
	}

	spIUniqueIDGenerator ShotImpl::GetUniqueIDGenerator() {
		return mNode->GetInternalNode()->GetUniqueIDGenerator();
	}

	spcIUniqueIDGenerator ShotImpl::GetUniqueIDGenerator() const {
		return mNode->GetInternalNode()->GetUniqueIDGenerator();
	}

	void ShotImpl::RemoveFromDOM() {
		ClearMap( mShotSourceMap );
		mNode->GetInternalNode()->RemoveFromDOM();
	}

	void ShotImpl::AddToDOM( const spINode & parent ) {
		mNode->GetInternalNode()->AddToDOM( parent );
	}

	ShotImpl::ShotImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: mNode( CreateNode( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeOutput ) )
		, mInCount( kEditUnitInCountFromBeginning )
		, mDuration( kEditUnitDurationTillEnd )
		, mFrameMap()
		, mShotSourceMap() { }

	spIShot CreateShot( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
	{
		return std::make_shared< ShotImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
	}

}

