//
//  GEDataModel.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFBikePowerData.h>
#import <WFConnector/WFHeartRateData.h>
#import <WFConnector/WFHeartRateRawData.h>
#import "GEPowerData.h"
#import "GEHeartRateData.h"
#import <CoreData/CoreData.h>

#define kGEPowerDataType            @"PowerData"
#define kGEHeartRateDataType        @"HeartRateData"

@class GEHeartRateData;

@interface GEDataModel : NSObject {

    NSPersistentStoreCoordinator        *_persistentStoreCoordinator;
    NSManagedObjectModel                *_managedObjectModel;
    NSManagedObjectContext              *_managedObjectContext;	
}

@property (nonatomic, retain, readonly) NSPersistentStoreCoordinator		*persistentStoreCoordinator;
@property (nonatomic, retain, readonly) NSManagedObjectModel				*managedObjectModel;
@property (nonatomic, retain, readonly) NSManagedObjectContext				*managedObjectContext;

-(GEHeartRateData *)insertHeartRateData:(WFHeartrateData *)heartRate rawHeartRateData:(WFHeartrateRawData *)rawHeartRateData saveAfter:(BOOL)saveAfter;
-(GEPowerData *)insertPowerData:(WFBikePowerData *)power saveAfter:(BOOL)saveAfter;
+ (GEDataModel*)sharedInstance;

@end
