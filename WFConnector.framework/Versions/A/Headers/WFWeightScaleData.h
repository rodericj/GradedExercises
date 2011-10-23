//
//  WFWeightScaleData.h
//  WFConnector
//
//  Created by Michael Moore on 11/9/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorData.h>

@class WFCommonData;


#define WF_WEIGHT_SCALE_INVALID      -1.0
#define WF_WEIGHT_SCALE_COMPUTING    -2.0


/**
 * Represents the data available from the ANT+ Weight Scale sensor.
 *
 * ANT+ sensors send data in multiple packets.  The WFWeightScaleData
 * combines this data into a single entity.  The data represents the latest of
 * each data type sent from the sensor.
 */
@interface WFWeightScaleData : WFSensorData
{
	/** \cond InterfaceDocs */
	
	WFCommonData* commonData;
	WFWeightScaleUserProfile_t userProfile;
	USHORT userProfileId;
	float  bodyWeight;
	BOOL   hasDisplayExchangeProfile;
	BOOL   hasScaleExchangeProfile;
	BOOL   hasAntFS;
	BOOL   isUserProfileSelected;
	
	float hydrationPercent;
	float bodyFatPercent;
	
	float activeMetabolicRate;
	float basalMetabolicRate;
	
	float muscleMass;
	float boneMass;
	
	/** \endcond */
}


/**
 * Common sensor data, provides information about the sensor.
 */
@property (nonatomic, readonly) WFCommonData* commonData;
/** User profile data. */
@property (nonatomic, assign) WFWeightScaleUserProfile_t userProfile;
/** User profile ID number. */
@property (nonatomic, assign) USHORT userProfileId;
/**
 * Measured body weight (in kg).
 *
 * @note Two special values exist.  When the weight scale is computing the user's
 * weight, the value will be <c>WF_WEIGHT_SCALE_COMPUTING</c>.  If the weight
 * scale has not recorded a valid value, the value will be
 * <c>WF_WEIGHT_SCALE_INVALID</c>. Otherwise, the value is the weight in kilograms.
 */
@property (nonatomic, assign) float bodyWeight;
/** Is the display capable of exchanging user profile data. */
@property (nonatomic, assign) BOOL hasDisplayExchangeProfile;
/** Is the scale capable of exchanging user profile data. */
@property (nonatomic, assign) BOOL hasScaleExchangeProfile;
/** Is the scale capable of ANT FS data exchange. */
@property (nonatomic, assign) BOOL hasAntFS;
/** Has the user profile been selected. */
@property (nonatomic, assign) BOOL isUserProfileSelected;
/**
 * Advanced data - body hydration percentage.
 *
 * @note Two special values exist.  When the weight scale is computing the user's
 * measurements, the value will be <c>WF_WEIGHT_SCALE_COMPUTING</c>.  If the weight
 * scale has not recorded a valid value, the value will be
 * <c>WF_WEIGHT_SCALE_INVALID</c>. Otherwise, the value is the body hydration
 * percentage.
 */
@property (nonatomic, assign) float hydrationPercent;
/**
 * Advanced data - body fat percentage.
 *
 * @note Two special values exist.  When the weight scale is computing the user's
 * measurements, the value will be <c>WF_WEIGHT_SCALE_COMPUTING</c>.  If the weight
 * scale has not recorded a valid value, the value will be
 * <c>WF_WEIGHT_SCALE_INVALID</c>. Otherwise, the value is the body fat percentage.
 */
@property (nonatomic, assign) float bodyFatPercent;
/**
 * Advanced data - Active metabolic Rate.
 *
 * @note Two special values exist.  When the weight scale is computing the user's
 * measurements, the value will be <c>WF_WEIGHT_SCALE_COMPUTING</c>.  If the weight
 * scale has not recorded a valid value, the value will be
 * <c>WF_WEIGHT_SCALE_INVALID</c>. Otherwise, the value is the metabolic rate,
 * in kilocalories.
 */
@property (nonatomic, assign) float activeMetabolicRate;
/**
 * Advanced data - Basal Metabolic Rate.
 *
 * @note Two special values exist.  When the weight scale is computing the user's
 * measurements, the value will be <c>WF_WEIGHT_SCALE_COMPUTING</c>.  If the weight
 * scale has not recorded a valid value, the value will be
 * <c>WF_WEIGHT_SCALE_INVALID</c>. Otherwise, the value is the metabolic rate,
 * in kilocalories.
 */
@property (nonatomic, assign) float basalMetabolicRate;
/**
 * Advanced data - muscle mass (in kg).
 *
 * @note Two special values exist.  When the weight scale is computing the user's
 * measurements, the value will be <c>WF_WEIGHT_SCALE_COMPUTING</c>.  If the weight
 * scale has not recorded a valid value, the value will be
 * <c>WF_WEIGHT_SCALE_INVALID</c>. Otherwise, the value is the muscle mass, in kg.
 */
@property (nonatomic, assign) float muscleMass;
/**
 * Advanced data - bone mass (in kg).
 *
 * @note Two special values exist.  When the weight scale is computing the user's
 * measurements, the value will be <c>WF_WEIGHT_SCALE_COMPUTING</c>.  If the weight
 * scale has not recorded a valid value, the value will be
 * <c>WF_WEIGHT_SCALE_INVALID</c>. Otherwise, the value is the bone mass, in kg.
 */
@property (nonatomic, assign) float boneMass;


- (WFWeightScaleUserProfile_t*)userProfilePtr;

@end
