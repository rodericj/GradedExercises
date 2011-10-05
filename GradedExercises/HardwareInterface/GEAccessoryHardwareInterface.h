//
//  AccessoryHardwareInterface.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFHardwareConnectorDelegate.h>

@class WFHardwareConnector;
@class WFSensorConnection;

@interface GEAccessoryHardwareInterface : NSObject <WFHardwareConnectorDelegate> {
    WFHardwareConnector* hardwareConnector;

}

+(GEAccessoryHardwareInterface *)sharedInterface;
-(void)enableInterface;
@end
