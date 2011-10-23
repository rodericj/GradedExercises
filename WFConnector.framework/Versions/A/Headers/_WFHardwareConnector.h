/*
 *  _WFHardwareConnector_stub.h
 *  WFConnector
 *
 *  Created by Michael Moore on 5/25/10.
 *  Copyright 2010 Wahoo Fitness. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <WFConnector/WFHardwareConnectorDelegate.h>


@interface _WFHardwareConnector : NSObject
{
}


@property (nonatomic, assign) BOOL autoReset;
@property (nonatomic, retain) id <WFHardwareConnectorDelegate> delegate;

@end
