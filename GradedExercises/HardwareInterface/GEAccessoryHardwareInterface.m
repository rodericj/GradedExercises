//
//  AccessoryHardwareInterface.m
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GEAccessoryHardwareInterface.h"
#import <WFConnector/WFConnector.h>

@implementation GEAccessoryHardwareInterface

static GEAccessoryHardwareInterface *gGEAccessoryHardwareInterface = nil;

+(GEAccessoryHardwareInterface *)sharedInterface {
    if (gGEAccessoryHardwareInterface == nil) {
        gGEAccessoryHardwareInterface = [[super allocWithZone:NULL] init];
    }
    return gGEAccessoryHardwareInterface;
}
- (void)updateSensorStatus
{
	// configure the status fields for the heartrate sensor.
	NSArray* connections = [hardwareConnector getSensorConnections:WF_SENSORTYPE_HEARTRATE];
	WFSensorConnection* sensor = ([connections count]>0) ? (WFSensorConnection*)[connections objectAtIndex:0] : nil;
    if ( sensor )
    {
        BOOL conn = (sensor != nil && sensor.isConnected) ? TRUE : FALSE;
        USHORT devId = sensor.deviceNumber;
        NSLog(@"HR %d connected: %@", devId, conn ? @"Yes" : @"No");

    }
    
    // configure the status fields for the Bike Power sensor.
	connections = [hardwareConnector getSensorConnections:WF_SENSORTYPE_BIKE_POWER];
	sensor = ([connections count]>0) ? (WFSensorConnection*)[connections objectAtIndex:0] : nil;
    if ( sensor )
    {
        BOOL conn = (sensor != nil && sensor.isConnected) ? TRUE : FALSE;
        USHORT devId = sensor.deviceNumber;
        NSLog(@"power %d connected: %@", devId, conn ? @"Yes" : @"No");

    }
}


//--------------------------------------------------------------------------------
- (void)fisicaConnected
{
    NSLog(@"fisica is connected");
}

-(void)fisicaDisconnected {
    NSLog(@"fisica is disconnected");
}

-(void)enableInterface {
    // initialize the HW Connector status.
    hardwareConnector = [WFHardwareConnector sharedConnector];
    if ( hardwareConnector.isFisicaConnected )
    {
        [self fisicaConnected];
        [self updateSensorStatus];
    }
    else
    {
        [self fisicaDisconnected];
    }
    
    // configure the hardware connector.
    hardwareConnector.delegate = self;
	hardwareConnector.sampleRate = 0.5;  // sample rate 500 ms, or 2 Hz.
    
    // set HW Connector to call hasData only when new data is available.
    [hardwareConnector setSampleTimerDataCheck:TRUE];
    
    // initialize the settings fields.
    WFConnectorSettings* settings = hardwareConnector.settings;
    NSLog(@"staleDataTimeText %@", [NSString stringWithFormat:@"%1.1f", settings.staleDataTimeout]);
    NSLog(@"staleDataStringText %@", settings.staleDataString);
    NSLog(@"coastingTimeText %@", [NSString stringWithFormat:@"%1.1f", settings.bikeCoastingTimeout]);
    NSLog(@"wheelCircText %@", [NSString stringWithFormat:@"%1.0f", settings.bikeWheelCircumference * 100]);
    NSLog(@"metricSwitch %@", settings.useMetricUnits);
    
    // subscribe for the HW Connector notifications.
//    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(fisicaConnected) name:WF_NOTIFICATION_HW_CONNECTED object:nil];
//    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(fisicaDisconnected) name:WF_NOTIFICATION_HW_DISCONNECTED object:nil];
//    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateSensorStatus) name:WF_NOTIFICATION_SENSOR_CONNECTED object:nil];
//    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateSensorStatus) name:WF_NOTIFICATION_SENSOR_DISCONNECTED object:nil];
//    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateData) name:WF_NOTIFICATION_SENSOR_HAS_DATA object:nil];
    
    [self fisicaConnected];
}

#pragma mark -
#pragma mark HardwareConnectorDelegate Implementation

//--------------------------------------------------------------------------------
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector connectedSensor:(WFSensorConnection*)connectionInfo
{
    [[NSNotificationCenter defaultCenter] postNotificationName:WF_NOTIFICATION_SENSOR_CONNECTED object:nil];
}

//--------------------------------------------------------------------------------
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector disconnectedSensor:(WFSensorConnection*)connectionInfo
{
    [[NSNotificationCenter defaultCenter] postNotificationName:WF_NOTIFICATION_SENSOR_DISCONNECTED object:nil];
}

//--------------------------------------------------------------------------------
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector stateChanged:(WFHardwareConnectorState_t)currentState
{
	BOOL connected = (currentState & WF_HWCONN_STATE_ACTIVE) ? TRUE : FALSE;
	if (connected)
	{
        [[NSNotificationCenter defaultCenter] postNotificationName:WF_NOTIFICATION_HW_CONNECTED object:nil];
	}
	else
	{
        [[NSNotificationCenter defaultCenter] postNotificationName:WF_NOTIFICATION_HW_DISCONNECTED object:nil];
	}
}

//--------------------------------------------------------------------------------
- (void)hardwareConnectorHasData
{
    NSLog(@"Accessory Hardware Interface was told that we have new data");
    [[NSNotificationCenter defaultCenter] postNotificationName:WF_NOTIFICATION_SENSOR_HAS_DATA object:nil];
}

@end
