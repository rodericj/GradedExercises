//
//  GECommonSensorManager.m
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GECommonSensorManager.h"

@implementation GECommonSensorManager
    
@synthesize sensorConnection;

-(id)init {
    self = [super init];
    if (self) {
        // register for HW connector notifications.
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(fisicaConnected) name:WF_NOTIFICATION_HW_CONNECTED object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(fisicaDisconnected) name:WF_NOTIFICATION_HW_DISCONNECTED object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateData) name:WF_NOTIFICATION_SENSOR_HAS_DATA object:nil];
    }
    return self;
}
    
-(void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

-(void)incomingData:(WFCommonData *)commonData {
    if ( commonData )
    {
        NSLog(@"deviceId %d\noperatingTime %@\nmanufacturerId %@\nserialNumber %@\nHWVersion %@\nSWVersion %@\nmodelNumber %@\nbattVoltage %@", 
              self.sensorConnection.deviceNumber,
              [NSString stringWithFormat:@"%d", commonData.operatingTime],
              [NSString stringWithFormat:@"%d", commonData.manufacturerId],
              [NSString stringWithFormat:@"%d", commonData.serialNumber],
              [NSString stringWithFormat:@"%d", commonData.hardwareVersion],
              [NSString stringWithFormat:@"%d", commonData.softwareVersion],
              [NSString stringWithFormat:@"%d", commonData.modelNumber],
              (commonData.batteryVoltage == WF_COMMON_BATTERY_INVALID) ? @"n/a" : [NSString stringWithFormat:@"%1.1f v", commonData.batteryVoltage]);
    }
}

#pragma mark - notifications


-(void)fisicaDisconnected {
    
}

-(void)fisicaConnected {
    
}


@end
