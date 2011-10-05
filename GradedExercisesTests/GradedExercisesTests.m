//
//  GradedExercisesTests.m
//  GradedExercisesTests
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GradedExercisesTests.h"
#import <WFConnector/WFBikePowerData.h>
#import <WFConnector/WFHardwareConnectorDelegate.h>
#import "GEDataModel.h"

@implementation GradedExercisesTests

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
- (void)testCreatePowerData
{
    id<WFHardwareConnectorDelegate> app_delegate = (id<WFHardwareConnectorDelegate>)[[UIApplication sharedApplication] delegate];

    WFBikePowerData *bikePowerData = [[WFBikePowerData alloc] initWithTime:1.0];

    [GEDataModel insertObject:bikePowerData 
                     withType:kGEPowerDataType 
                    saveAfter:NO];
    
    [app_delegate hardwareConnectorHasData];
    STAssertTrue(TRUE, @"");
}
//- (void)testExample
//{
//    STFail(@"Unit tests are not implemented yet in GradedExercisesTests");
//}

@end
