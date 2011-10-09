//
//  GESensorData.h
//  GradedExercises
//
//  Created by roderic campbell on 10/8/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class GEWorkout;

@interface GESensorData : NSManagedObject

@property (nonatomic, retain) NSNumber * time;
@property (nonatomic, retain) NSNumber * isDataStale;
@property (nonatomic, retain) NSNumber * settings;
@property (nonatomic, retain) NSDate * timestamp;
@property (nonatomic, retain) NSSet *workout;
@end

@interface GESensorData (CoreDataGeneratedAccessors)

- (void)addWorkoutObject:(GEWorkout *)value;
- (void)removeWorkoutObject:(GEWorkout *)value;
- (void)addWorkout:(NSSet *)values;
- (void)removeWorkout:(NSSet *)values;
@end
