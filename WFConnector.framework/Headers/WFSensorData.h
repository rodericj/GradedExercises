//
//  WFSensorData.h
//  WFConnector
//
//  Created by Michael Moore on 11/9/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/hardware_connector_types.h>

@class WFConnectorSettings;


/**
 * This is the abstract base class for all types of ANT sensor data.
 */
@interface WFSensorData : NSObject
{
    NSTimeInterval lastDataTime;
}


/** <c>TRUE</c> if data is considered stale, otherwise <c>FALSE</c>. */
@property (nonatomic, readonly) BOOL isDataStale;

/** Gets the persistent settings for the Wahoo API. */
@property (nonatomic, readonly) WFConnectorSettings* settings;


- (id)initWithTime:(NSTimeInterval)dataTime;

@end
