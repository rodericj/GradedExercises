//
//  WFFitnessEquipmentData.h
//  WFConnector
//
//  Created by Michael Moore on 12/21/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorData.h>


/**
 * Represents the most commonly used data available from the ANT+ Fitness Equipment sensor.
 *
 * ANT+ sensors send data in multiple packets.  The WFFitnessEquipmentData combines the
 * most commonly used of this data into a single entity.  The data represents
 * the latest of each data type sent from the sensor.
 */
@interface WFFitnessEquipmentData : WFSensorData
{
	/** \cond InterfaceDocs */
	
	// general FE data.
	WFFitnessEquipmentType_t equipmentType;
	WFFitnessEquipmentState_t equipmentState;
	float accumTime;
	ULONG accumDistance;
	float instSpeed;
	UCHAR heartrate;
	UCHAR lapNumber;
	
	// equipment specific: treadmill.
	UCHAR treadmillCadence;
	float treadmillAccumNegVertDist;
	float treadmillAccumPosVertDist;
	
	// equipment specific: elliptical.
	float  ellipticalAccumPosVertDist;
	ULONG  ellipticalAccumStrides;
	UCHAR  ellipticalCadence;
	USHORT ellipticalInstPower;
	
	// equipment specific: bike.
	UCHAR  bikeCadence;
	USHORT bikeInstPower;
	
	// equipment specific: rower.
	ULONG  rowerAccumStrokes;
	UCHAR  rowerCadence;
	USHORT rowerInstPower;
	
	/** \endcond */
}


// general FE data.

/**
 * The type of the connected Fitness Equipment device.
 */
@property (nonatomic, assign) WFFitnessEquipmentType_t equipmentType;
/**
 * The current state of the connected Fitness Equipment device.
 */
@property (nonatomic, assign) WFFitnessEquipmentState_t equipmentState;
/**
 * The accumulated time since the workout was started, in seconds.
 */
@property (nonatomic, assign) float accumTime;
/**
 * The accumulated distance, in meters, since the workout was started.
 */
@property (nonatomic, assign) ULONG accumDistance;
/**
 * The instantaneous speed, in meters per second.
 */
@property (nonatomic, assign) float instSpeed;
/**
 * The instantaneous heart rate, in BPM.
 */
@property (nonatomic, assign) UCHAR heartrate;
/**
 * The current lap number.
 */
@property (nonatomic, assign) UCHAR lapNumber;

// equipment specific: treadmill.

/**
 * The instantaneous cadence, in strides per minute.
 */
@property (nonatomic, assign) UCHAR treadmillCadence;
/**
 * The total negative vertial distance traveled, in meters.
 */
@property (nonatomic, assign) float treadmillAccumNegVertDist;
/**
 * The total positive vertical distance traveled, in meters.
 */
@property (nonatomic, assign) float treadmillAccumPosVertDist;

// equipment specific: elliptical.

/**
 * The total positive vertical distance traveled, in meters.
 */
@property (nonatomic, assign) float  ellipticalAccumPosVertDist;
/**
 * The total number of strides taken.
 */
@property (nonatomic, assign) ULONG  ellipticalAccumStrides;
/**
 * The instantaneous cadence, in strides per minute.
 */
@property (nonatomic, assign) UCHAR  ellipticalCadence;
/**
 * The instantaneous power, in watts.
 */
@property (nonatomic, assign) USHORT ellipticalInstPower;

// equipment specific: bike.

/**
 * The instantaneous cadence, in RPMs.
 */
@property (nonatomic, assign) UCHAR  bikeCadence;
/**
 * The instantaneous power, in watts.
 */
@property (nonatomic, assign) USHORT bikeInstPower;

// equipment specific: rower.

/**
 * The total stroke count.
 */
@property (nonatomic, assign) ULONG  rowerAccumStrokes;
/**
 * The instantaneous cadence, in strokes per minute.
 */
@property (nonatomic, assign) UCHAR  rowerCadence;
/**
 * The instantaneous power, in watts.
 */
@property (nonatomic, assign) USHORT rowerInstPower;

@end
