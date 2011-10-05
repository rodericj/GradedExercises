//
//  GEPowerData.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "GESensorData.h"


@interface GEPowerData : GESensorData

@property (nonatomic) int64_t accumulatedTorque;
@property (nonatomic) int64_t calculatedCrankTicks;
@property (nonatomic) int16_t sensorType;
@property (nonatomic) int64_t eventCount;
@property (nonatomic) int16_t instCadence;
@property (nonatomic) int64_t accumulatedTicks;
@property (nonatomic) int16_t averagePower;

@end
