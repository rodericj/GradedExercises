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
#import <WFConnector/WFConnectorSettings.h>
#import "GEDataModel.h"
#import "GEAccessoryHardwareInterface.h"

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

- (void)testCreatePowerDataInCoreData
{

    //[[GEAccessoryHardwareInterface sharedInterface] hardwareConnectorHasData];
    WFConnectorSettings *settings = [[WFConnectorSettings alloc] init];
    settings.useMetricUnits = NO;
    settings.bikeWheelCircumference = 200;
    
    for (int i = 0; i<10; i++) {
        WFBikePowerData *bikePowerData = [[WFBikePowerData alloc] initWithTime:1.0];
        bikePowerData.sensorType = WF_BIKE_POWER_TYPE_WHEEL_TORQUE;
        bikePowerData.fpAccumulatedTorque = i*100;
        bikePowerData.ulAccumulatedTicks = i+20;
        bikePowerData.fpCalculatedCrankTicks = i;
        bikePowerData.ucInstCadence = 10;
        bikePowerData.ulAveragePower = 10+i;
        bikePowerData.ucEventCount = i;
        bikePowerData.timestamp = i*1000;
        bikePowerData.timestampOverflow = NO;
        
        [[GEDataModel sharedInstance] insertPowerData:bikePowerData 
                                             withType:kGEPowerDataType 
                                            saveAfter:YES];   
    
    }
    
    [settings release];
    
    STAssertTrue(TRUE, @"");
    
}

@end
