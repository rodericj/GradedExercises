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
        NSLog(@"event count %@\n inst cadence %@\naccumulated Torque %@\nformattedPower %@\ninstantPower %@",
              [NSString stringWithFormat:@"%d", bpData.ucEventCount],
              [NSString stringWithFormat:@"%d", bpData.ucInstCadence],
              [NSString stringWithFormat:@"%1.0f", bpData.fpAccumulatedTorque],
              [bpData formattedPower:FALSE],
              [NSString stringWithFormat:@"%d", bpRawData.powerOnlyData.instantPower]);
        
        // update the common data.
       // [super updateCommonData:bpRawData.commonData];
    }
    else
    {
        NSLog(@"Should probably notify the UI that we have no data");
    }
}

-(void)updateData {
    [self incomingPowerData];
}
@end
