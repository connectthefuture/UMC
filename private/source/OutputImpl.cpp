// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "implHeaders/OutputImpl.h"
#include "interfaces/IVideoTrack.h"
#include "interfaces/IAudioTrack.h"
#include "interfaces/IUniqueIDGenerator.h"
#include "interfaces/IUMC.h"

#include "utils/Utils.h"
#include "utils/UMCAndXMPMapping.h"

#include "XMPCore/Interfaces/IXMPStructureNode.h"

namespace INT_UMC {

	const std::string & OutputImpl::GetUniqueID() const {
		return NodeImpl::GetUniqueID();
	}

	spITrack OutputImpl::GetTrack( const std::string & uniqueID ) {
		spITrack track = GetVideoTrack( uniqueID );
		if ( track ) return track;
		track = GetAudioTrack( uniqueID );
		return track;
	}

	spcITrack OutputImpl::GetTrack( const std::string & uniqueID ) const {
		return const_cast< OutputImpl *>( this )->GetTrack( uniqueID );
	}

	IOutput::TrackList OutputImpl::GetAllTracks() {
		TrackList list;
		AppendToListFromMap< spITrack >( list, mVideoTrackMap );
		AppendToListFromMap< spITrack >( list, mAudioTrackMap );
		return list;
	}

	IOutput::cTrackList OutputImpl::GetAllTracks() const {
		cTrackList list;
		AppendToListFromMap< spcITrack >( list, mVideoTrackMap );
		AppendToListFromMap< spcITrack >( list, mAudioTrackMap );
		return list;
	}

	INode::eNodeTypes OutputImpl::GetNodeType() const {
		return kNodeTypeOutput;
	}

	spcINode OutputImpl::GetDecendantNode( const std::string & id ) const {
		return const_cast< OutputImpl * >( this )->GetDecendantNode( id );
	}

	spINode OutputImpl::GetDecendantNode( const std::string & id ) {
		auto node = GetChildNode( id );
		if ( node ) return node;
		node = GetDecendantFromMap( mVideoTrackMap, id );
		if ( node ) return node;
		node = GetDecendantFromMap( mAudioTrackMap, id );
		return node;
	}

	spcINode OutputImpl::GetChildNode( const std::string & id ) const {
		return const_cast< OutputImpl * >( this )->GetChildNode( id );
	}

	spINode OutputImpl::GetChildNode( const std::string & id ) {
		return GetTrack( id );
	}

	INode::NodeList OutputImpl::GetAllChildren() {
		NodeList list;
		AppendToListFromMap< spINode, VideoTrackMap >( list, mVideoTrackMap );
		AppendToListFromMap< spINode, AudioTrackMap >( list, mAudioTrackMap );
		return list;
	}

	INode::cNodeList OutputImpl::GetAllChildren() const {
		cNodeList list;
		AppendToListFromMap< spcINode, VideoTrackMap >( list, mVideoTrackMap );
		AppendToListFromMap< spcINode, AudioTrackMap >( list, mAudioTrackMap );
		return list;
	}

	INode::NodeList OutputImpl::GetAllDecendants() {
		NodeList list;
		AppendDecendantsFromMapToList< spINode >( list, mVideoTrackMap );
		AppendDecendantsFromMapToList< spINode >( list, mAudioTrackMap );
		return list;
	}

	INode::cNodeList OutputImpl::GetAllDecendants() const {
		cNodeList list;
		AppendDecendantsFromMapToList< spcINode >( list, mVideoTrackMap );
		AppendDecendantsFromMapToList< spcINode >( list, mAudioTrackMap );
		return list;
	}

	size_t OutputImpl::GetReferenceCount() const {
		return NodeImpl::GetReferenceCount();
	}

	spICustomData OutputImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) {
		return NodeImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	spcICustomData OutputImpl::GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const {
		return NodeImpl::GetCustomData( customDataNameSpace, customDataName );
	}

	bool OutputImpl::SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData ) {
		return NodeImpl::SetCustomData( customDataNameSpace, customDataName, customData );
	}

	pINodeI OutputImpl::GetInternalNode() {
		return this;
	}

	pcINodeI OutputImpl::GetInternalNode() const {
		return this;
	}

	void OutputImpl::CleanUpOnRemovalFromDOM() {
		ClearMap( mVideoTrackMap, mVideoTracks );
		ClearMap( mAudioTrackMap, mAudioTracks );
	}

	void OutputImpl::SetUpOnAdditionToDOM() { }

	void OutputImpl::SyncInternalStuffToXMP() const {
		AddOrUpdateDataToXMPDOM( mTitle, kTitlePair, mXMPStructureNode );
		AddOrUpdateDataToXMPDOM( mName, kNamePair, mXMPStructureNode );
		AddOrUpdateDataToXMPDOM( mCanvasAspectRatio, kCanvasAspectRatioPair, mXMPStructureNode );
		AddOrUpdateDataToXMPDOM( mImageAspectRatio, kImageAspectRatioPair, mXMPStructureNode );
		AddOrUpdateDataToXMPDOM( mVideoEditRate, kVideoEditRatePair, mXMPStructureNode );
		AddOrUpdateDataToXMPDOM( mAudioEditRate, kAudioEditRatePair, mXMPStructureNode );

		CallSyncUMCToXMPOnMapElements( mVideoTrackMap );
		CallSyncUMCToXMPOnMapElements( mAudioTrackMap );
	}

	void OutputImpl::SyncXMPToInternalStuff() {
		mTracks = TryToGetStructNode( mXMPStructureNode, kTracksPair );
		if ( mTracks ) {
			mVideoTracks = TryToGetArrayNode( mTracks, kVideoTracksPair );
			mAudioTracks = TryToGetArrayNode( mTracks, kAudioTracksPair );
		}

		UpdateDataFromXMPDOM( mTitle, kTitlePair, mXMPStructureNode, kEmptyString );
		UpdateDataFromXMPDOM( mName, kNamePair, mXMPStructureNode, kEmptyString );
		UpdateDataFromXMPDOM( mCanvasAspectRatio, kCanvasAspectRatioPair, mXMPStructureNode, &stou64rt );
		UpdateDataFromXMPDOM( mImageAspectRatio, kImageAspectRatioPair, mXMPStructureNode, &stou64rt );
		UpdateDataFromXMPDOM( mVideoEditRate, kVideoEditRatePair, mXMPStructureNode, &stou64rt );
		UpdateDataFromXMPDOM( mAudioEditRate, kAudioEditRatePair, mXMPStructureNode, &stou64rt );

		PopulateMapFromXMPArrayNode( this, &OutputImpl::AddVideoTrack, mVideoTracks );
		PopulateMapFromXMPArrayNode( this, &OutputImpl::AddAudioTrack, mAudioTracks );
	}

	NS_XMPCORE::spIXMPStructureNode OutputImpl::GetXMPNode() const {
		return mXMPStructureNode;
	}

	UMC::spITrack OutputImpl::AddTrack( const std::string & buffer ) {
		spIXMPStructureNode parentNode = ParseRDF( buffer );
		const NamespacePropertyNamePair * pairs[ 2 ] = { &kVideoTracksPair, &kAudioSourcesPair };
		size_t matchedIndex =  GetMatchingIndexForActualNode( parentNode, &pairs[ 0 ], ( size_t ) 2 );

		switch ( matchedIndex ) {
		case 0:
			return AddVideoTrack( parentNode );
		case 1:
			return AddAudioTrack( parentNode );
		default:
			THROW_PARSING_ERROR;
		}
		return spITrack();
	}

	spIVideoTrack OutputImpl::AddVideoTrack() {
		spIVideoTrack track = CreateVideoTrack( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator );
		CreateEquivalentXMPNodes( mXMPStructureNode, mVideoTracks, kVideoTracksPair, mTracks, kTracksPair );
		AddElementToMap( mVideoTrackMap, track, shared_from_this(), mVideoTracks );
		return track;
	}

	UMC::spIVideoTrack OutputImpl::AddVideoTrack( const std::string & buffer ) {
		spIXMPStructureNode node = ParseRDF( buffer );
		return AddVideoTrack( node );
	}

	UMC::spIVideoTrack OutputImpl::AddVideoTrack( const spIXMPStructureNode & node ) {
		auto actualNode = TryToGetActualNode( node, kVideoTracksPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIVideoTrack track = CreateVideoTrack( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, actualNode );
		CreateEquivalentXMPNodes( mXMPStructureNode, mVideoTracks, kVideoTracksPair, mTracks, kTracksPair );
		AddElementToMap( mVideoTrackMap, track, shared_from_this(), mVideoTracks );
		track->GetInternalNode()->SyncXMPToUMC();
		return track;
	}

	bool OutputImpl::ValidateXMPNode() const {
		return true;
	}

	std::string OutputImpl::Serialize() const {
		return NodeImpl::SerializeXMP();
	}

	UMC::pINode OutputImpl::GetNode() {
		return this;
	}

	UMC::pcINode OutputImpl::GetNode() const {
		return this;
	}

	spIAudioTrack OutputImpl::AddAudioTrack() {
		spIAudioTrack track = CreateAudioTrack( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator );
		CreateEquivalentXMPNodes( mXMPStructureNode, mAudioTracks, kAudioTracksPair, mTracks, kTracksPair );
		AddElementToMap( mAudioTrackMap, track, shared_from_this(), mAudioTracks );
		return track;
	}

	UMC::spIAudioTrack OutputImpl::AddAudioTrack( const std::string & buffer ) {
		spIXMPStructureNode node = ParseRDF( buffer );
		return AddAudioTrack( node );
	}

	UMC::spIAudioTrack OutputImpl::AddAudioTrack( const spIXMPStructureNode & node ) {
		auto actualNode = TryToGetActualNode( node, kAudioTracksPair );
		if ( !actualNode ) THROW_PARSING_ERROR;
		spIAudioTrack track = CreateAudioTrack( mspUniqueIDAndReferenceTracker, mspUniqueIDGenerator, actualNode );
		CreateEquivalentXMPNodes( mXMPStructureNode, mAudioTracks, kAudioTracksPair, mTracks, kTracksPair );
		AddElementToMap( mAudioTrackMap, track, shared_from_this(), mAudioTracks );
		track->GetInternalNode()->SyncXMPToUMC();
		return track;
	}

	void OutputImpl::SetName( const std::string & name ) {
		mName = name;
	}

	std::string OutputImpl::GetName() const {
		return mName;
	}

	void OutputImpl::SetTitle( const std::string & title ) {
		mTitle = title;
	}

	std::string OutputImpl::GetTitle() const {
		return mTitle;
	}

	void OutputImpl::SetCanvasAspectRatio( const AspectRatio & canvasAspectRatio ) {
		mCanvasAspectRatio = canvasAspectRatio;
	}

	AspectRatio OutputImpl::GetCanvasAspectRatio() const {
		return mCanvasAspectRatio;
	}

	void OutputImpl::SetImageAspectRatio( const AspectRatio & imageAspectRatio ) {
		mImageAspectRatio = imageAspectRatio;
	}

	AspectRatio OutputImpl::GetImageAspectRatio() const {
		return mImageAspectRatio;
	}

	void OutputImpl::SetVideoEditRate( const EditRate & videoEditRate ) {
		mVideoEditRate = videoEditRate;
	}

	EditRate OutputImpl::GetVideoEditRate() const {
		return mVideoEditRate;
	}

	void OutputImpl::SetAudioEditRate( const EditRate & audioEditRate ) {
		mAudioEditRate = audioEditRate;
	}

	EditRate OutputImpl::GetAudioEditRate() const {
		return mAudioEditRate;
	}

	spcIAudioTrack OutputImpl::GetAudioTrack( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIAudioTrack >( mAudioTrackMap, uniqueID );
	}

	spIAudioTrack OutputImpl::GetAudioTrack( const std::string & uniqueID ) {
		return GetElementFromMap< spIAudioTrack >( mAudioTrackMap, uniqueID );
	}

	size_t OutputImpl::RemoveAllTracks() {
		bool safeToClear( false );
		safeToClear = SafeToClearMap( mVideoTrackMap );
		if ( safeToClear ) SafeToClearMap( mAudioTrackMap ); else return 0;
		if ( safeToClear ) {
			size_t expectedCount = TrackCount();
			size_t count( 0 );
			count += ClearMap( mVideoTrackMap, mVideoTracks );
			count += ClearMap( mAudioTrackMap, mAudioTracks );
			assert( expectedCount == count );
			return count;
		}
		return 0;
	}

	size_t OutputImpl::RemoveAllVideoTracks() {
		if ( SafeToClearMap( mVideoTrackMap ) ) {
			return ClearMap( mVideoTrackMap, mVideoTracks );
		}
		return 0;
	}

	size_t OutputImpl::RemoveAllAudioTracks() {
		if ( SafeToClearMap( mAudioTrackMap ) ) {
			return ClearMap( mAudioTrackMap, mAudioTracks );
		}
		return 0;
	}

	size_t OutputImpl::RemoveTrack( const std::string & uniqueID ) {
		size_t count = RemoveVideoTrack( uniqueID );
		if ( count > 0 ) return count;
		count = RemoveAudioTrack( uniqueID );
		return count;
	}

	size_t OutputImpl::RemoveVideoTrack( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mVideoTrackMap, uniqueID, mVideoTracks );
	}

	size_t OutputImpl::RemoveAudioTrack( const std::string & uniqueID ) {
		return TryAndRemoveElementFromMap( mAudioTrackMap, uniqueID, mAudioTracks );
	}

	wpcINode OutputImpl::GetParentNode() const  {
		return NodeImpl::GetParentNode();
	}

	wpINode OutputImpl::GetParentNode() {
		return NodeImpl::GetParentNode();
	}

	size_t OutputImpl::TrackCount() const {
		return mVideoTrackMap.size() + mAudioTrackMap.size();
	}

	size_t OutputImpl::VideoTrackCount() const {
		return mVideoTrackMap.size();
	}

	size_t OutputImpl::AudioTrackCount() const {
		return mAudioTrackMap.size();
	}

	IOutput::VideoTrackList OutputImpl::GetAllVideoTracks() {
		return CreateListFromMap< spIVideoTrack >( mVideoTrackMap );
	}

	IOutput::cVideoTrackList OutputImpl::GetAllVideoTracks() const {
		return CreateListFromMap< spcIVideoTrack >( mVideoTrackMap );
	}

	spcIVideoTrack OutputImpl::GetVideoTrack( const std::string & uniqueID ) const {
		return GetElementFromMap< spcIVideoTrack >( mVideoTrackMap, uniqueID );
	}

	spIVideoTrack OutputImpl::GetVideoTrack( const std::string & uniqueID ) {
		return GetElementFromMap< spIVideoTrack >( mVideoTrackMap, uniqueID );
	}

	IOutput::AudioTrackList OutputImpl::GetAllAudioTracks() {
		return CreateListFromMap< spIAudioTrack >( mAudioTrackMap );
	}

	IOutput::cAudioTrackList OutputImpl::GetAllAudioTracks() const {
		return CreateListFromMap< spcIAudioTrack >( mAudioTrackMap );
	}

	OutputImpl::OutputImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & xmpStructureNode )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeOutput, xmpStructureNode )
		, mCanvasAspectRatio( 1 )
		, mImageAspectRatio( 1 )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 1 ) { }


	OutputImpl::OutputImpl( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator )
		: NodeImpl( uniqueIDAndReferenceTracker, uniqueIDGenerator, INode::kNodeTypeOutput, kOutputsPair )
		, mCanvasAspectRatio( 1 )
		, mImageAspectRatio( 1 )
		, mVideoEditRate( 1 )
		, mAudioEditRate( 1 ) { }

	spIOutput CreateOutput( const spIUniqueIDAndReferenceTracker & uniqueIDAndReferenceTracker,
		const spIUniqueIDGenerator & uniqueIDGenerator, const spIXMPStructureNode & node )
	{
		if ( node ) {
			return std::make_shared< OutputImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator, node );
		} else {
			return std::make_shared< OutputImpl >( uniqueIDAndReferenceTracker, uniqueIDGenerator );
		}
	}
}
