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
    
    //TODO I'm almost getting data here.
    WFHeartrateData* hrData = [self.heartrateConnection getHeartrateData];
	WFHeartrateRawData* hrRawData = [self.heartrateConnection getHeartrateRawData];
	if ( hrData != nil )
	{
        [[GEDataModel sharedInstance] insertHeartRateData:hrData rawHeartRateData:hrRawData saveAfter:YES];
        [self incomingData:hrRawData.commonData];
        // update the signal efficiency.
		        
        // unformatted value.
		// computedHeartrateLabel.text = [NSString stringWithFormat:@"%d", hrData.computedHeartrate];
        
        // update basic data.
        NSLog(@"computedHeartrateLabel %@", [hrData formattedHeartrate:TRUE]);
		NSLog(@"beatTimeLabel %@", [NSString stringWithFormat:@"%d", hrData.beatTime]);
		
        // update raw data.
		NSLog(@"beatCountLabel %@", [NSString stringWithFormat:@"%d", hrRawData.beatCount]);
		NSLog(@"previousBeatLabel %@", [NSString stringWithFormat:@"%d", hrRawData.previousBeatTime]);
        

	}
	else 
	{
		//[self resetDisplay];
	}
}

-(void)updateData {
    NSLog(@"incoming heart date data");
    [self incomingHeartRateData];
}
@end
