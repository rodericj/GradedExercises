//
//  GradedExercisesLogicTests.m
//  GradedExercisesLogicTests
//
//  Created by roderic campbell on 10/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GradedExercisesLogicTests.h"
#import "GEDataModel.h"

//WF Imports
#import <WFConnector/WFHeartRateData.h>
#import <WFConnector/WFHeartRateRawData.h>

@implementation GradedExercisesLogicTests

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testAddRandomHeartRate
{
    WFHeartrateData *hrData = [[WFHeartrateData alloc] initWithTime:1];
    WFHeartrateRawData *rawHRData = [[WFHeartrateRawData alloc] initWithTime:1];;
    
    int computedHeartRate = 70;
    hrData.computedHeartrate = computedHeartRate;
    NSNumber *computedHeartRateNumber = [NSNumber numberWithInt:computedHeartRate];
    
    int beatTime = 10;
    hrData.beatTime = beatTime;
    NSNumber *beatTimeNumber = [NSNumber numberWithInt:beatTime];
    
    int accumBeatCount = 100;
    hrData.accumBeatCount = accumBeatCount;
    NSNumber *accumBeatCountNumber = [NSNumber numberWithInt:accumBeatCount];
    
    GEHeartRateData *coreDataHR = [[GEDataModel sharedInstance] insertHeartRateData:hrData rawHeartRateData:rawHRData saveAfter:NO];
    STAssertTrue([coreDataHR.computedHeartRate isEqualToNumber:computedHeartRateNumber], @"computed heart rate not set correctly");
    STAssertTrue([coreDataHR.beatTime isEqualToNumber:beatTimeNumber], @"beatTime not set correctly");
    STAssertTrue([coreDataHR.accumBeatCount isEqualToNumber:accumBeatCountNumber], @"accumBeatTime not set correctly");
}

@end
