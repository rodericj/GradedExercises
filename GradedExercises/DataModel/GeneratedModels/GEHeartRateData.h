//
//  GEHeartRateData.h
//  GradedExercises
//
//  Created by roderic campbell on 10/8/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "GESensorData.h"


@interface GEHeartRateData : GESensorData

@property (nonatomic, retain) NSNumber * accumBeatCount;
@property (nonatomic, retain) NSNumber * beatTime;
@property (nonatomic, retain) NSNumber * computedHeartRate;

@end
