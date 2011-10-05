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
    NSLog(@"generic data");
    
    // update the signal efficiency.
    int deviceId = self.sensorConnection.deviceNumber;
    NSLog(@"device is %d", deviceId);
    float signal = [self.sensorConnection signalEfficiency];
    if (signal == -1) {
        NSLog( @"n/a");
    }
    else {
        NSLog(@"%@",[NSString stringWithFormat:@"%0.0f%%", (signal*100)]);
    }
    
    if ( commonData )
    {
        NSLog(@"operatingTimeLabel %@", [NSString stringWithFormat:@"%d", commonData.operatingTime]);
        NSLog(@"manufacturerIdLabel %@", [NSString stringWithFormat:@"%d", commonData.manufacturerId]);
        NSLog(@"serialNumberLabel %@", [NSString stringWithFormat:@"%d", commonData.serialNumber]);
        NSLog(@"hardwareVersionLabel %@", [NSString stringWithFormat:@"%d", commonData.hardwareVersion]);
        NSLog(@"softwareVersionLabel %@", [NSString stringWithFormat:@"%d", commonData.softwareVersion]);
        NSLog(@"modelNumberLabel %@", [NSString stringWithFormat:@"%d", commonData.modelNumber]);
        NSLog(@"battVoltageLabel %@", (commonData.batteryVoltage == WF_COMMON_BATTERY_INVALID) ? @"n/a" : [NSString stringWithFormat:@"%1.1f v", commonData.batteryVoltage]);
        
        NSString* battStatus = @"n/a";
        switch (commonData.batteryStatus)
        {
            case WF_BATTERY_STATUS_NEW:
                battStatus = @"NEW";
                break;
            case WF_BATTERY_STATUS_GOOD:
                battStatus = @"GOOD";
                break;
            case WF_BATTERY_STATUS_OK:
                battStatus = @"OK";
                break;
            case WF_BATTERY_STATUS_LOW:
                battStatus = @"LOW";
                break;
            case WF_BATTERY_STATUS_CRITICAL:
                battStatus = @"CRIT";
                break;
            case WF_BATTERY_STATUS_NOT_AVAILABLE:
            default:
                battStatus = @"n/a";
                break;
        }
        NSLog(@"battStatusLabel%@", battStatus);
    }
    else
    {
        NSLog(@"operatingTimeLabel %@", @"n/a");
        NSLog(@"manufacturerIdLabel.text %@", @"n/a");
        NSLog(@"serialNumberLabel.text %@", @"n/a");
        NSLog(@"hardwareVersionLabel.text %@", @"n/a");
        NSLog(@"softwareVersionLabel.text %@", @"n/a");
        NSLog(@"modelNumberLabel.text %@", @"n/a");
        NSLog(@"battStatusLabel.text %@", @"n/a");
        NSLog(@"battVoltageLabel.text %@", @"n/a");
    }
}

#pragma mark - notifications


-(void)fisicaDisconnected {
    
}

-(void)fisicaConnected {
    
}


@end
