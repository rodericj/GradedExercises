//
//  WFBikePowerPowerOnlyData.h
//  WFConnector
//
//  Created by Michael Moore on 11/9/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorData.h>


/**
 * Represents the data available from the Power-Only type ANT+ Bike Power sensor.
 *
 * ANT+ sensors send data in multiple packets.  The WFBikePowerPowerOnlyData
 * combines this data into a single entity.  The data represents the latest of
 * each data type sent from the sensor.
 */
@interface WFBikePowerPowerOnlyData : WFSensorData
{
	/** \cond InterfaceDocs */
	
	UCHAR  eventCount;
	UCHAR  instantCadence;
	USHORT accumulatedPower;
	USHORT instantPower;
	ULONG  averagePower;
	
	/** \endcond */
}


/**
 * Power event count, incremented each time the sensor takes a measurement.
 */
@property (nonatomic, assign) UCHAR  eventCount;
/**
 * Crank cadence (RPMs) – if available.  Otherwise: 0xFF indicates invalid.
 */
@property (nonatomic, assign) UCHAR  instantCadence;
/**
 * Accumulated power (1-watt resolution).
 */
@property (nonatomic, assign) USHORT accumulatedPower;
/**
 * Instantaneous power (1-watt resolution).
 */
@property (nonatomic, assign) USHORT instantPower;
/**
 * Buffered power measurement (1-watt resolution).
 */
@property (nonatomic, assign) ULONG  averagePower;

@end
