//
//  GESensorCommonManager.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFConnector.h>

@interface GECommonSensorManager : NSObject <WFSensorConnectionDelegate>{
    WFHardwareConnector* hardwareConnector;
	WFSensorConnection* sensorConnection;
}

@property (retain, nonatomic) WFSensorConnection* sensorConnection;

-(void)incomingData:(WFCommonData *)common;

@end
