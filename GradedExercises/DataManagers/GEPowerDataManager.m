//
//  GEPowerDataManager.m
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GEPowerDataManager.h"

@implementation GEPowerDataManager

//--------------------------------------------------------------------------------
- (WFBikePowerConnection*)bikePowerConnection
{
	WFBikePowerConnection* retVal = nil;
	if ( [self.sensorConnection isKindOfClass:[WFBikePowerConnection class]] )
	{
		retVal = (WFBikePowerConnection*)self.sensorConnection;
	}
	
	return retVal;
}

-(void)incomingPowerData {
    NSLog(@"incoming power data");
    WFBikePowerData *bpData = [self.bikePowerConnection getBikePowerData];
    bpData.ulAveragePower = 100;
    WFBikePowerRawData *bpRawData = [self.bikePowerConnection getBikePowerRawData];
    if ( bpData != nil )
    {
        [self incomingData:bpRawData.commonData];
        
               // update the basic data.
        NSLog(@"%@",[NSString stringWithFormat:@"%d", bpData.ucEventCount]);
        //		eventCountLabel.text = [NSString stringWithFormat:@"%d", bpData.ucEventCount];
        
        //		instantCadenceLabel.text = [NSString stringWithFormat:@"%d", bpData.ucInstCadence];
        NSLog(@"%@",[NSString stringWithFormat:@"%d", bpData.ucInstCadence]);
        
        //		accumulatedTorqueLabel.text = [NSString stringWithFormat:@"%1.0f", bpData.fpAccumulatedTorque];
        NSLog(@"%@",[NSString stringWithFormat:@"%1.0f", bpData.fpAccumulatedTorque]);
        
        //        averagePowerLabel.text = [bpData formattedPower:FALSE];
        NSLog(@"%@",[bpData formattedPower:FALSE]);
        // using unformatted value.
        // averagePowerLabel.text = [NSString stringWithFormat:@"%d", bpData.ulAveragePower];
        //
        // only available for "power-only" meters.
        //instantPowerLabel.text = [NSString stringWithFormat:@"%d", bpRawData.powerOnlyData.instantPower];
        NSLog(@"%@", [NSString stringWithFormat:@"%d", bpRawData.powerOnlyData.instantPower]);
        
        // update the common data.
       // [super updateCommonData:bpRawData.commonData];
    }
    else
    {
        NSLog(@"Should probably notify the UI that we have no data");
        //[self resetDisplay];
    }
}

-(void)updateData {
    [self incomingPowerData];
}
@end
