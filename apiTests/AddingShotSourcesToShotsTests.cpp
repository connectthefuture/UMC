// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"

class AddingShotSourcesToShotsTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( AddingShotSourcesToShotsTests );
	CPPUNIT_TEST( CountOfShotSources );
	CPPUNIT_TEST( ShotSourcesContent );
	CPPUNIT_TEST_SUITE_END();


protected:
	void CountOfShotSources();
	void ShotSourcesContent();

public:
	virtual void setUp();
	virtual void tearDown();

};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingShotSourcesToShotsTests );

#include "interfaces/IUMC.h"
#include "interfaces/IOutput.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/ITrack.h"
#include "interfaces/IVideoTrack.h"
#include "interfaces/IAudioTrack.h"
#include "interfaces/IShot.h"
#include "interfaces/IShotSource.h"
#include "interfaces/IClipShot.h"
#include "interfaces/ITransitionShot.h"
#include "interfaces/IFrame.h"

static UMC::spIUMC CreateDefaultUMC() {
	using namespace UMC;

	spIUMC sp = IUMC::CreateEmptyUMC();
	auto output1 = sp->AddOutput();
	auto source1 = sp->AddVideoSource();
	source1->SetClipName( "source 1" );
	auto videoTrack1 = output1->AddVideoTrack();

	auto clipShot1 = videoTrack1->AddClipShot();
	clipShot1->SetInCount( 10 );
	clipShot1->SetDuration( 15 );

	auto shotSource = clipShot1->AddShotSource( source1 );

	return sp;
}

void AddingShotSourcesToShotsTests::CountOfShotSources() {
	std::cout<< "********** AddingShotSourcesToShotsTests::CountOfShotSources **********"<<"\n";
	using namespace UMC;

	auto sp = CreateDefaultUMC();

}


void AddingShotSourcesToShotsTests::ShotSourcesContent() {
	std::cout<< "********** AddingShotSourcesToShotsTests::ShotSourcesContent **********"<<"\n";
	using namespace UMC;

	auto sp = CreateDefaultUMC();

	auto outputs = sp->GetAllOutputs();
	auto tracks = outputs[0]->GetAllTracks();
	auto shots = tracks[0]->GetAllShots();
	auto shotSources = shots[0]->GetShotSources();
	auto source = shotSources[0]->GetSource();

	CPPUNIT_ASSERT_EQUAL( source->GetClipName(), std::string( "source 1" ) );
	CPPUNIT_ASSERT_EQUAL( source->GetType(), ISource::kSourceTypeVideo );

	auto vsource = dynamic_pointer_cast< const IVideoSource >( source );
	
	CPPUNIT_ASSERT_EQUAL( vsource->GetVideoEditRate(), EditRate( 1 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetAudioEditRate(), EditRate( 48000 ) );
	CPPUNIT_ASSERT_EQUAL( vsource->GetInCount(), ( EditUnitInCount ) kEditUnitInCountFromBeginning );
	CPPUNIT_ASSERT_EQUAL( vsource->GetDuration(), ( EditUnitDuration ) kEditUnitDurationTillEnd );
	CPPUNIT_ASSERT_EQUAL( vsource->GetTimeCode(), TimeCode( FrameRate( 1 ) ) );

	auto rdfRep = sp->SerializeToBuffer();
	std::cout<<" ******* AddingDoViDisplayCustomDataToUMC::Test *****\n";
	std::cout<<rdfRep<<"\n\n\n\n\n";
}


void AddingShotSourcesToShotsTests::setUp() {
	UMC_Initialize();
}

void AddingShotSourcesToShotsTests::tearDown() {
	UMC_Terminate();
}


