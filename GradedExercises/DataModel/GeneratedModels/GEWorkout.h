//
//  GEWorkout.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class GESensorData, GEUser;

@interface GEWorkout : NSManagedObject

@property (nonatomic, retain) GEUser *user;
@property (nonatomic, retain) NSSet *sensorData;
@end

@interface GEWorkout (CoreDataGeneratedAccessors)

- (void)addSensorDataObject:(GESensorData *)value;
- (void)removeSensorDataObject:(GESensorData *)value;
- (void)addSensorData:(NSSet *)values;
- (void)removeSensorData:(NSSet *)values;
@end
