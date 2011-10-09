//
//  GEPowerData.h
//  GradedExercises
//
//  Created by roderic campbell on 10/8/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "GESensorData.h"


@interface GEPowerData : GESensorData

@property (nonatomic, retain) NSNumber * accumulatedTorque;
@property (nonatomic, retain) NSNumber * calculatedCrankTicks;
@property (nonatomic, retain) NSNumber * sensorType;
@property (nonatomic, retain) NSNumber * eventCount;
@property (nonatomic, retain) NSNumber * instCadence;
@property (nonatomic, retain) NSNumber * accumulatedTicks;
@property (nonatomic, retain) NSNumber * averagePower;

@end
