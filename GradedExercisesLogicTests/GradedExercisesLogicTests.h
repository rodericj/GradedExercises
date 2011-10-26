//
//  GradedExercisesLogicTests.h
//  GradedExercisesLogicTests
//
//  Created by roderic campbell on 10/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <SenTestingKit/SenTestingKit.h>
//WF Imports
#import <WFConnector/WFHeartRateData.h>
#import <WFConnector/WFHeartRateRawData.h>

@interface GradedExercisesLogicTests : SenTestCase {
    WFHeartrateData *_hrData;
    WFHeartrateRawData *_rawHRData;
}

@end
