//
//  WFSensorConnectionDelegate.h
//  WFConnector
//
//  Created by Michael Moore on 1/4/11.
//  Copyright 2011 Wahoo Fitness. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WFConnector/hardware_connector_types.h>


@class WFSensorConnection;


/**
 * Provides the interface for callback methods used by the WFSensorConnection.
 */
@protocol WFSensorConnectionDelegate <NSObject>

@optional

/**
 * Invoked when the WFSensorConnection has changed connection state.
 *
 * @param connectionInfo The WFSensorConnection instance.
 
 * @param connState A ::WFSensorConnectionStatus_t value indicating the
 * current connection state.
 */
- (void)connection:(WFSensorConnection*)connectionInfo stateChanged:(WFSensorConnectionStatus_t)connState;

@end
