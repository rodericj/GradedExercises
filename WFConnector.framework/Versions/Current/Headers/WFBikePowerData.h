//
//  WFBikePowerData.h
//  WFConnector
//
//  Created by Michael Moore on 11/9/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorData.h>


/**
 * Represents the most commonly used data available from the ANT+ Bike Power sensor.
 *
 * ANT+ sensors send data in multiple packets.  The WFBikePowerData combines the
 * most commonly used of this data into a single entity.  The data represents
 * the latest of each data type sent from the sensor.
 */
@interface WFBikePowerData : WFSensorData
{
	/** \cond InterfaceDocs */
	
	WFBikePowerType_t sensorType;
	float fpAccumulatedTorque;
	ULONG ulAccumulatedTicks;
	float fpCalculatedCrankTicks;
	UCHAR ucInstCadence;
	ULONG ulAveragePower;
	UCHAR ucEventCount;
	NSTimeInterval timestamp;
	BOOL timestampOverflow;
	
	/** \endcond */
}


/**
 * Indicates the type of the power meter.
 *
 * @note After the sensor connects, or is reset, it will take several
 * messages from the device before the sensor type can be determined.
 */
@property (nonatomic, assign) WFBikePowerType_t sensorType;
/**
 * The total accumulated torque in Nm.
 *
 * Accumulated torque is the sum of the average torque for each update period.
 * For example, in wheel-based power sensors, it is the sum of the average
 * torque for each wheel revolution.
 *
 * @note The accumulator is initialized when the sensor is first connected, and
 * reset via the WFHardwareConnector::resetAllSensorData method.
 */
@property (nonatomic, assign) float fpAccumulatedTorque;
/**
 * The total accumulated revolutions measured by the sensor.
 *
 * This source of this value depends on the sensor type.  The value will be
 * wheel revolutions for wheel-based sensors, and crank revolutions for
 * crank based sensors.
 */
@property (nonatomic, assign) ULONG ulAccumulatedTicks;
/**
 * The total calculated crank revolutions.
 *
 * This value is available only for certain types of wheel-based sensors.
 */
@property (nonatomic, assign) float fpCalculatedCrankTicks;
/**
 * The instantaneous crank cadence, in RPM.
 */
@property (nonatomic, assign) UCHAR ucInstCadence;
/**
 * The average power measured over the last revolution.
 *
 * The span of this value depends on the type of sensor (wheel revolution for
 * wheel-based sensors, and crank revolution for crank-based sensors).
 */
@property (nonatomic, assign) ULONG ulAveragePower;
/**
 * The event counter value.
 *
 * See the event counter value of the specific power meter type for more
 * about this value (WFBikePowerCTFData, WFBikePowerCrankTorqueData,
 * and WFBikePowerWheelTorqueData).
 */
@property (nonatomic, assign) UCHAR ucEventCount;
/**
 * The real-time timestamp for data from the sensor (as an offset from
 * the Cocoa reference date).
 *
 * Time values from the sensors are implemented as an offset in seconds
 * between the time when the sensor is turned on and the time when a
 * data sample is taken.  This value is typically a 16-bit unsigned
 * integer in units of 1/1024 second.  The rollover is then 64 seconds.
 *
 * A base real-time value is stored when the first sample from the
 * sensor is received.  The timestamp of each subsequent sample is the
 * base time value offset by the time value offset from the sensor.
 * If the time between samples is greater than the rollover time, the
 * base time value is set to the time the first sample after the delay
 * is received.
 */
@property (nonatomic, assign) NSTimeInterval timestamp;
/**
 * Indicates that the time between data samples from the sensor has
 * exceeded the rollover time (64 seconds).
 */
@property (nonatomic, assign) BOOL timestampOverflow;


/**
 * Returns the power as a string formatted for display.
 * 
 * @see WFConnectorSettings
 * 
 * @param showUnits If <c>TRUE</c> the units will be included in the string
 * returned.  Otherwise, the units are not included.
 * 
 * @return The formatted display string (power in watts).
 */
- (NSString*)formattedPower:(BOOL)showUnits;

@end
