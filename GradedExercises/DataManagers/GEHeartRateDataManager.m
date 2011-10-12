//
//  GEHeartRateDataManager.m
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GEHeartRateDataManager.h"
#import "GEDataModel.h"

@implementation GEHeartRateDataManager
static GEHeartRateDataManager *gGEHeartRateDataManager = nil;

+(GEHeartRateDataManager *)sharedInstance {
    if (gGEHeartRateDataManager == nil) {
        gGEHeartRateDataManager = [[super allocWithZone:NULL] init];
    }
    return gGEHeartRateDataManager;
}

- (WFHeartrateConnection *)heartrateConnection
{
	WFHeartrateConnection* retVal = nil;
	if ( [self.sensorConnection isKindOfClass:[WFHeartrateConnection class]] )
	{
		retVal = (WFHeartrateConnection*)self.sensorConnection;
	}
	
	return retVal;
}

-(void) incomingHeartRateData {
    
    WFHeartrateData* hrData = [self.heartrateConnection getHeartrateData];
	WFHeartrateRawData* hrRawData = [self.heartrateConnection getHeartrateRawData];
	if ( hrData != nil )
	{
        [[GEDataModel sharedInstance] insertHeartRateData:hrData rawHeartRateData:hrRawData saveAfter:YES];
        [self incomingData:hrRawData.commonData];
        // update the signal efficiency.

        // update basic data.
        NSLog(@"computedHeartrateLabel %@\nbeatTimeLabel %@\nbeatCountLabel %@\npreviousBeatLabel %@", 
              [hrData formattedHeartrate:TRUE],
              [NSString stringWithFormat:@"%d", hrData.beatTime], 
              [NSString stringWithFormat:@"%d", hrRawData.beatCount], 
              [NSString stringWithFormat:@"%d", hrRawData.previousBeatTime]);
	}

}

-(void)updateData {
    [self incomingHeartRateData];
}
@end
