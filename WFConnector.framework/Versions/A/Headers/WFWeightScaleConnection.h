//
//  WFWeightScaleConnection.h
//  WFConnector
//
//  Created by Michael Moore on 11/10/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorConnection.h>


@class WFWeightScaleData;


/**
 * Represents a connection to an ANT+ Weight Scale sensor.
 */
@interface WFWeightScaleConnection : WFSensorConnection
{
}


/**
 * Returns the latest data available from the sensor.
 *
 * @see WFSensorConnection::getData
 *
 * @return A WFWeightScaleData instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFWeightScaleData*)getWeightScaleData;

/**
 * Sends a user profile message to the Weight Scale sensor with the user
 * profile data specified in the ::WFWeightScaleUserProfile_t structure.
 *
 * @param pstData A ::WFWeightScaleUserProfile_t structure containing the
 * user profile information to be sent to the sensor.
 *
 * @return <c>TRUE</c> if the user profile message was sent successfully,
 * otherwise <c>FALSE</c>.
 */
- (BOOL)setWeightScaleUserProfile:(WFWeightScaleUserProfile_t*)pstData;

@end
