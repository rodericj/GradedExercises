//
//  GEUser.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class GEWorkout;

@interface GEUser : NSManagedObject

@property (nonatomic, retain) NSString * firstName;
@property (nonatomic, retain) NSString * lastName;
@property (nonatomic, retain) NSSet *workouts;
@end

@interface GEUser (CoreDataGeneratedAccessors)

- (void)addWorkoutsObject:(GEWorkout *)value;
- (void)removeWorkoutsObject:(GEWorkout *)value;
- (void)addWorkouts:(NSSet *)values;
- (void)removeWorkouts:(NSSet *)values;
@end
