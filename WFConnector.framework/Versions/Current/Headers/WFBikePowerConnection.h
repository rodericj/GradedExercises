//
//  WFBikePowerConnection.h
//  WFConnector
//
//  Created by Michael Moore on 11/9/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorConnection.h>


@class WFBikePowerData;
@class WFBikePowerRawData;


/**
 * Represents a connection to an ANT+ Bike Power sensor.
 */
@interface WFBikePowerConnection : WFSensorConnection
{
}


@property (nonatomic, assign) BOOL autoCalibrate;


/**
 * Returns the latest data available from the sensor.
 *
 * @see WFSensorConnection::getData
 *
 * @return A WFBikePowerData instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFBikePowerData*)getBikePowerData;

/**
 * Returns the latest raw (unformatted) data available from the sensor.
 *
 * @see WFSensorConnection::getRawData
 *
 * @return A WFBikePowerRawData instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFBikePowerRawData*)getBikePowerRawData;

/**
 * Sends a calibration message to the Bike Power sensor with the calibration
 * data specified in the ::WFBikePowerCalibrationData_t structure.
 *
 * @param pstData A ::WFBikePowerCalibrationData_t structure containing the
 * calibration information to be sent to the sensor.
 *
 * @return <c>TRUE</c> if the calibration message was sent successfully,
 * otherwise <c>FALSE</c>.
 */
- (BOOL)setBikePowerCalibration:(WFBikePowerCalibrationData_t*)pstData;

/**
 * Sets the calibration offset value for the power meter sensor.
 *
 * The calibration offset value for power sensors is not persisted by the
 * Wahoo Fitness API.  The application should store any offset value returned
 * after a calibration is performed.  This value should be used to set the
 * calibration offset used for power calculations.  Use this method after
 * the power sensor has been connected to set the offset.
 *
 * @note When the sensor is connected or reset, the calibration offset is
 * reset.  This method should be invoked after the sensor is connected, and
 * after a reset operation (see WFHardwareConnector::resetAllSensorData).
 *
 * @param usOffset The calibration offset value.
 *
 * @return <c>TRUE</c> if the calibration offset was set, otherwise <c>FALSE</c>.
 */
- (BOOL)setBikePowerCalibrationOffset:(USHORT)usOffset;


@end
