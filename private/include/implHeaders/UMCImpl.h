#ifndef UMCImpl_h__
#define UMCImpl_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/IUMC.h"
#include "UMCFwdDeclarations_I.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"
#include "implHeaders/NodeImpl.h"

#include <map>

namespace INT_UMC {

	using namespace NS_XMPCORE;

	class UMCImpl
		: public IUMC
		, public NodeImpl
		, public enable_shared_from_this< UMCImpl >
	{
	public:
		UMCImpl();
		UMCImpl( const spIXMPStructureNode & metadata );

		virtual spIVideoSource AddVideoSource();
		virtual spIVideoSource AddVideoSource( const std::string & buffer );

		virtual spIAudioSource AddAudioSource();
		virtual spIAudioSource AddAudioSource( const std::string & buffer );

		virtual spIVideoFrameSource AddVideoFrameSource( const spIVideoSource & videoSource );
		virtual spIVideoFrameSource AddVideoFrameSource( const std::string & buffer );

		virtual spIImageSource AddImageSource();
		virtual spIImageSource AddImageSource( const std::string & buffer );

		virtual spISource AddSource( const std::string & buffer );

		virtual spIOutput AddOutput();
		virtual spIOutput AddOutput( const std::string & buffer );

		virtual size_t SourceCount() const;
		virtual size_t VideoSourceCount() const;
		virtual size_t AudioSourceCount() const;
		virtual size_t VideoFrameSourceCount() const;
		virtual size_t ImageSourceCount() const;

		virtual SourceList GetAllSources();
		virtual cSourceList GetAllSources() const;

		virtual VideoSourceList GetAllVideoSources();
		virtual cVideoSourceList GetAllVideoSources() const;

		virtual AudioSourceList GetAllAudioSources();
		virtual cAudioSourceList GetAllAudioSources() const;

		virtual VideoFrameSourceList GetAllVideoFrameSources();
		virtual cVideoFrameSourceList GetAllVideoFrameSources() const;

		virtual ImageSourceList GetAllImageSources();
		virtual cImageSourceList GetAllImageSources() const;

		virtual spISource GetSource( const std::string & uniqueID );
		virtual spcISource GetSource( const std::string & uniqueID ) const;

		virtual spIVideoSource GetVideoSource( const std::string & uniqueID );
		virtual spcIVideoSource GetVideoSource( const std::string & uniqueID ) const;

		virtual spIAudioSource GetAudioSource( const std::string & uniqueID );
		virtual spcIAudioSource GetAudioSource( const std::string & uniqueID ) const;

		virtual spIVideoFrameSource GetVideoFrameSource( const std::string & uniqueID );
		virtual spcIVideoFrameSource GetVideoFrameSource( const std::string & uniqueID ) const;

		virtual spIImageSource GetImageSource( const std::string & uniqueID );
		virtual spcIImageSource GetImageSource( const std::string & uniqueID ) const;

		virtual size_t RemoveAllSources();
		virtual size_t RemoveAllVideoSources();
		virtual size_t RemoveAllAudioSources();
		virtual size_t RemoveAllVideoFramesSources();
		virtual size_t RemoveAllImageSources();

		virtual size_t RemoveSource( const std::string & uniqueID );
		virtual size_t RemoveVideoSource( const std::string & uniqueID );
		virtual size_t RemoveAudioSource( const std::string & uniqueID );
		virtual size_t RemoveVideoFrameSource( const std::string & uniqueID );
		virtual size_t RemoveImageSource( const std::string & uniqueID );

		virtual size_t OutputCount() const;

		virtual OutputList GetAllOutputs();
		virtual cOutputList GetAllOutputs() const;

		virtual spIOutput GetOutput( const std::string & uniqueID );
		virtual spcIOutput GetOutput( const std::string & uniqueID ) const;

		virtual size_t RemoveAllOutputs();

		virtual size_t RemoveOutput( const std::string & uniqueID );

		virtual std::string SerializeToBuffer() const;

		virtual eNodeTypes GetNodeType() const;

		virtual spcINode GetDecendantNode( const std::string & uniqueID ) const;
		virtual spINode GetDecendantNode( const std::string & uniqueID );

		virtual spcINode GetChildNode( const std::string & uniqueID ) const;
		virtual spINode GetChildNode( const std::string & uniqueID );

		virtual NodeList GetAllChildren();
		virtual cNodeList GetAllChildren() const;

		virtual NodeList GetAllDecendants();
		virtual cNodeList GetAllDecendants() const;

		virtual INT_UMC::pINodeI GetInternalNode();
		virtual INT_UMC::pcINodeI GetInternalNode() const;

		virtual void CleanUpOnRemovalFromDOM();
		virtual void SetUpOnAdditionToDOM();

		virtual void SyncInternalStuffToXMP() const;
		virtual void SyncXMPToInternalStuff();

		virtual spIXMPStructureNode GetXMPNode() const;

		virtual const std::string & GetUniqueID() const;

		virtual wpcINode GetParentNode() const;
		virtual wpINode GetParentNode();

		virtual size_t GetReferenceCount() const;

		virtual std::string Serialize() const;

		virtual spICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName );
		virtual spcICustomData GetCustomData( const std::string & customDataNameSpace, const std::string & customDataName ) const;

		virtual bool SetCustomData( const std::string & customDataNameSpace, const std::string & customDataName, const spICustomData & customData );

	protected:
		spIVideoSource AddVideoSource( const spIXMPStructureNode & node );
		spIAudioSource AddAudioSource( const spIXMPStructureNode & node );
		spIImageSource AddImageSource( const spIXMPStructureNode & node );
		spIVideoFrameSource AddVideoFrameSource( const spIXMPStructureNode & node );

		spIOutput AddOutput( const spIXMPStructureNode & node );

		virtual bool ValidateXMPNode() const;

		virtual pINode GetNode();

		virtual pcINode GetNode() const;

		typedef std::map< const std::string, spIVideoSource > VideoSourceMap;
		typedef std::map< const std::string, spIAudioSource > AudioSourceMap;
		typedef std::map< const std::string, spIVideoFrameSource > VideoFrameSourceMap;
		typedef std::map< const std::string, spIImageSource > ImageSourceMap;
		typedef std::map< const std::string, spIOutput > OutputMap;

		spIXMPArrayNode					mOutputs;
		spIXMPStructureNode				mSources;
		spIXMPArrayNode					mVideoSources;
		spIXMPArrayNode					mAudioSources;
		spIXMPArrayNode					mVideoFrameSources;
		spIXMPArrayNode					mImageSources;

		VideoSourceMap					mVideoSourceMap;
		AudioSourceMap					mAudioSourceMap;
		VideoFrameSourceMap				mVideoFrameSourceMap;
		ImageSourceMap					mImageSourceMap;
		OutputMap						mOutputMap;
	};
}

#endif  // UMCImpl_h__
