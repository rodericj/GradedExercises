//
//  GradedExercisesLogicTests.m
//  GradedExercisesLogicTests
//
//  Created by roderic campbell on 10/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GradedExercisesLogicTests.h"
#import "GEDataModel.h"

@implementation GradedExercisesLogicTests

- (void)setUp
{
    [super setUp];
    
    _hrData = [[WFHeartrateData alloc] initWithTime:1];
    _rawHRData = [[WFHeartrateRawData alloc] initWithTime:1];;}

- (void)tearDown
{
    // Tear-down code here.
    [_hrData release];
    [_rawHRData release];
    [super tearDown];
}

- (void)testInsertHeartRateData
{
    int computedHeartRate = 70;
    _hrData.computedHeartrate = computedHeartRate;
    NSNumber *computedHeartRateNumber = [NSNumber numberWithInt:computedHeartRate];
    
    int beatTime = 10;
    _hrData.beatTime = beatTime;
    NSNumber *beatTimeNumber = [NSNumber numberWithInt:beatTime];
    
    int accumBeatCount = 100;
    _hrData.accumBeatCount = accumBeatCount;
    NSNumber *accumBeatCountNumber = [NSNumber numberWithInt:accumBeatCount];
    
    GEHeartRateData *coreDataHR = [[GEDataModel sharedInstance] insertHeartRateData:_hrData rawHeartRateData:_rawHRData saveAfter:NO];
    STAssertTrue([coreDataHR.computedHeartRate isEqualToNumber:computedHeartRateNumber], @"computed heart rate not set correctly");
    STAssertTrue([coreDataHR.beatTime isEqualToNumber:beatTimeNumber], @"beatTime not set correctly");
    STAssertTrue([coreDataHR.accumBeatCount isEqualToNumber:accumBeatCountNumber], @"accumBeatTime not set correctly");
}

@end
