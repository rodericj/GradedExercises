//
//  WFBikeSpeedCadenceConnection.h
//  WFConnector
//
//  Created by Michael Moore on 11/10/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorConnection.h>


@class WFBikeSpeedCadenceData;
@class WFBikeSpeedCadenceRawData;


/**
 * Represents a connection to an ANT+ combined Bike Speed and Cadence sensor.
 */
@interface WFBikeSpeedCadenceConnection : WFSensorConnection
{
}


/**
 * Returns the latest data available from the sensor.
 *
 * @see WFSensorConnection::getData
 *
 * @return A WFBikeSpeedCadenceData instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFBikeSpeedCadenceData*)getBikeSpeedCadenceData;

/**
 * Returns the latest raw (unformatted) data available from the sensor.
 *
 * @see WFSensorConnection::getRawData
 *
 * @return A WFBikeSpeedCadenceRawData instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFBikeSpeedCadenceRawData*)getBikeSpeedCadenceRawData;

@end
