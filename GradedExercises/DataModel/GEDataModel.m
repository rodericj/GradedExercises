//
//  GEDataModel.m
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GEDataModel.h"

#define kGradedExercisesCoreDataBackupTempFile		@"GradedExercisesBackupTemp"
#define kGradedExercisesCoreDataBackupFile			@"GradedExercisesBackup"
#define kGradedExercisesCoreDataFile					@"GradedExercises"
#define kGradedExercisesCoreDataFileExtension			@"sqlite"

@implementation GEDataModel

static GEDataModel *gGEDataModel = nil;

/**
 Returns the managed object context for the application.
 If the context doesn't already exist, it is created and bound to the persistent store coordinator for the application.
 */
- (NSManagedObjectContext *)managedObjectContext {
	
	if (_managedObjectContext) {
		return _managedObjectContext;
	}
	
	NSPersistentStoreCoordinator *coordinator = self.persistentStoreCoordinator;
	if (coordinator != nil) {
		_managedObjectContext = [[NSManagedObjectContext alloc] init];
		[_managedObjectContext setPersistentStoreCoordinator:coordinator];
	}
	return _managedObjectContext;
}

/**
 Returns the managed object model for the application.
 If the model doesn't already exist, it is created by merging all of the models found in the application bundle.
 */
- (NSManagedObjectModel *)managedObjectModel {
	
	if (_managedObjectModel != nil) {
		return _managedObjectModel;
	}
    
    NSBundle * bundle = [NSBundle bundleForClass:[self class]];
    _managedObjectModel = [NSManagedObjectModel mergedModelFromBundles:[NSArray arrayWithObject:bundle]];
	return _managedObjectModel;
}

-(NSString*) applicationDocumentsDirectory
{
    return [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
}

/**
 Returns the persistent store coordinator for the application.
 If the coordinator doesn't already exist, it is created and the application's store added to it.
 */
- (NSPersistentStoreCoordinator *)persistentStoreCoordinator {
	
	if (_persistentStoreCoordinator) {
		return _persistentStoreCoordinator;
	}
    
    NSString *docDir = [self applicationDocumentsDirectory];
    NSString *path = [docDir
                      stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.%@",
                                                      kGradedExercisesCoreDataFile,
                                                      kGradedExercisesCoreDataFileExtension]];
	NSURL *storeUrl = [NSURL fileURLWithPath:path];
    
	NSError *addPersistentStoreError;
	_persistentStoreCoordinator = [[NSPersistentStoreCoordinator alloc] initWithManagedObjectModel: [self managedObjectModel]];
	if (![_persistentStoreCoordinator addPersistentStoreWithType:NSSQLiteStoreType configuration:nil URL:storeUrl options:nil error:&addPersistentStoreError]) {
        
		// We could not successfully add a new store to the coordinator. The most likely reason for this is that the schema of the current store and
		// the app are out of sync (this happens when a new version of the app tries to access a store that was created with a previous version of
		// the app.
        
		// During development, the schema of the data model will change frequently. Since we currently use the data model only to store either data
		// that is OK to wipe (during development), or to store data that is also available on the service, our current policy is, when we detect
		// schema incompatibilities, to back up the existing store, and then create a brand new one with the new schema.
        
		// In the future, we should use proper schema migration.
        NSLog(@"%d", [addPersistentStoreError code]);
		if ([addPersistentStoreError code] == NSPersistentStoreIncompatibleVersionHashError) {
			NSLog(@"Schema incompatibility, backing up current store.");
			// Schema version mismatch. Back up the current store, and create a new empty one.
            
			NSFileManager *fileManager = [NSFileManager defaultManager];
            
			NSURL *backupStoreUrl = [NSURL fileURLWithPath: [docDir
															 stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.%@",
																							 kGradedExercisesCoreDataBackupFile,
																							 kGradedExercisesCoreDataFileExtension]]];
            
			NSURL *tempBackupStoreUrl = [NSURL fileURLWithPath:[docDir
                                                                stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.%@",
                                                                                                kGradedExercisesCoreDataBackupTempFile,
                                                                                                kGradedExercisesCoreDataFileExtension]]];
            
			// Delete any lingering temporary backup store.
			NSString *tempBackupStorePath = [tempBackupStoreUrl path];
			if ([fileManager fileExistsAtPath:tempBackupStorePath]) {
				NSLog(@"Removing lingering temporary store backup at '%@'.", tempBackupStorePath);
				NSError *removeError;
				if (![fileManager removeItemAtURL:tempBackupStoreUrl error:&removeError]) {
					NSLog(@"FATAL: Could not remove lingering temporary store backup. Error code = %d (%@)", [removeError code], [removeError localizedDescription]);
					abort();
				}
			}
            
			// Move the current store to the temporary store backup.
			NSLog(@"Moving store to temporary store backup '%@'.", tempBackupStorePath);
			NSError	*moveError1;
			if (![fileManager moveItemAtURL:storeUrl toURL:tempBackupStoreUrl error:&moveError1]) {
				NSLog(@"FATAL: Could not move store to temporary store backup. Error code = %d (%@)", [moveError1 code], [moveError1 localizedDescription]);
				abort();
			}
            
			// Delete the store backup if one exists. One would not exist at first.
			NSString *backupStorePath = [backupStoreUrl path];
			if ([fileManager fileExistsAtPath:backupStorePath]) {
				NSLog(@"Removing store backup at '%@'.", backupStorePath);
				NSError *removeBackupError;
				if (![fileManager removeItemAtURL:backupStoreUrl error:&removeBackupError]) {
					NSLog(@"FATAL: Could not remove store backup. Error code = %d (%@)", [removeBackupError code], [removeBackupError localizedDescription]);
					abort();
				}
			}
            
			// Move the temporary store backup to the store backup.
			NSLog(@"Moving temporary store backup to store backup '%@'.", [backupStoreUrl path]);
			NSError	*moveError2;
			if (![fileManager moveItemAtURL:tempBackupStoreUrl toURL:backupStoreUrl error:&moveError2]) {
				NSLog(@"FATAL: Could not move temporary store backup to store backup. Error code = %d (%@)", [moveError2 code], [moveError2 localizedDescription]);
				abort();
			}
            
			NSLog(@"Previous store backed up, creating new empty store.");
			// The original store file was saved off, try again to add a store to the coordinator, this time that should create a new empty store.
			if ([_persistentStoreCoordinator addPersistentStoreWithType:NSSQLiteStoreType configuration:nil URL:storeUrl options:nil error:&addPersistentStoreError]) {
				NSLog(@"New empty store created.");
				// A fresh store was created, we're in good shape and ready to use it with Core Data.
                
			} else {
				// We could not even create a new empty store using the current schema, something is really wrong.
				NSLog(@"FATAL: Even after backing up the original store, a new empty store could not be added to the coordinator. Error code = %d (%@)", [addPersistentStoreError code], [addPersistentStoreError localizedDescription]);
				abort();
			}
		} else {
			NSLog(@"FATAL: Could not add a store to the coordinator. Error code = %d (%@)", [addPersistentStoreError code], [addPersistentStoreError localizedDescription]);
			abort();
		}
	}	
    
	return _persistentStoreCoordinator;
}

#pragma mark -
#pragma mark Singleton

+ (GEDataModel*)sharedInstance {
	if (gGEDataModel == nil) {
		gGEDataModel = [[super allocWithZone:NULL] init];
	}
	return gGEDataModel;
}

-(GEHeartRateData *)insertHeartRateData:(WFHeartrateData *)heartRate rawHeartRateData:(id)rawHeartRateData saveAfter:(BOOL)saveAfter {
    GEHeartRateData *newHRData = [NSEntityDescription insertNewObjectForEntityForName:kGEHeartRateDataType 
                                                              inManagedObjectContext:self.managedObjectContext];
    newHRData.accumBeatCount        = [NSNumber numberWithInt:heartRate.accumBeatCount];
    newHRData.beatTime              = [NSNumber numberWithInt:heartRate.beatTime];
    newHRData.computedHeartRate     = [NSNumber numberWithInt:heartRate.computedHeartrate];
    newHRData.timestamp             = [NSDate dateWithTimeIntervalSince1970:(int)heartRate.timestamp];
    NSLog(@"new heart rate is %@", newHRData);
    if (saveAfter) {
        [self.managedObjectContext save:nil];
    }
    return newHRData;
}

-(GEPowerData *)insertPowerData:(WFBikePowerData *)power saveAfter:(BOOL)saveAfter {
    GEPowerData *newPowerData = [NSEntityDescription insertNewObjectForEntityForName:kGEPowerDataType 
                                                              inManagedObjectContext:self.managedObjectContext];
//    newPowerData.calculatedCrankTicks   = power.fpCalculatedCrankTicks;
//    newPowerData.accumulatedTorque      = power.fpAccumulatedTorque;
//    newPowerData.calculatedCrankTicks   = power.fpCalculatedCrankTicks;
//    newPowerData.calculatedCrankTicks   = power.fpCalculatedCrankTicks;
//    newPowerData.calculatedCrankTicks   = power.fpCalculatedCrankTicks;

    if (saveAfter) {
        [self.managedObjectContext save:nil];
    }
    return newPowerData;
}

@end
