//
//  GEHeartRateData.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface GEHeartRateData : NSManagedObject

@property (nonatomic) int16_t accumBeatCount;
@property (nonatomic) NSTimeInterval beatTime;
@property (nonatomic) int16_t computedHeartRate;

@end
