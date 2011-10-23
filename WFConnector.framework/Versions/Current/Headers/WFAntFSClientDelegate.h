//
//  WFAntFSClientDelegate.h
//  WFConnector
//
//  Created by Michael Moore on 12/14/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WFConnector/wf_antfs_types.h>


@class _WFAntFSClientBase;


/**
 * Provides the interface for callback methods used by the WFAntFSClientBase.
 */
@protocol WFAntFSClientDelegate <NSObject>

@required

/**
 * Invoked when the WFAntFSClientBase instance has been created.
 *
 * See the WFHardwareConnector::requestAntFSClient:toDelegate: method for
 * documentation regarding instantiating a WFAntFSClientBase.
 *
 * @note This method is REQUIRED for classes adopting the WFAntFSClientDelegate
 * protocol.
 *
 * @param fsClient The WFAntFSClientBase instance.
 * @param bSuccess <c>TRUE</c> if the instance was created, otherwise <c>FALSE</c>.
 */
- (void)antFSClient:(_WFAntFSClientBase*)fsClient instanceCreated:(BOOL)bSuccess;

@optional

/**
 * Invoked when the ANT FS Client has connected to a host.
 *
 * @param fsClient The WFAntFSClientBase instance.
 * @param bAuthenticated <c>TRUE</c> if the host has authenticated, otherwise <c>FALSE</c>.
 */
- (void)antFSClient:(_WFAntFSClientBase*)fsClient connectedDevice:(BOOL)bAuthenticated;

/**
 * Invoked when the ANT FS Client encounters an error.
 *
 * @param fsClient The WFAntFSClientBase instance.
 * @param error A ::WFAntFSClientError_t value indicating the type of error.
 */
- (void)antFSClient:(_WFAntFSClientBase*)fsClient encounteredError:(WFAntFSClientError_t)error;

/**
 * Invoked when the ANT FS Client receives a response from the ANT device.
 *
 * @param fsClient The WFAntFSClient instance.
 * @param responseCode An ::ANTFS_RESPONSE value indicating the type of response.
 */
- (void)antFSClient:(_WFAntFSClientBase*)fsClient receivedResponse:(ANTFS_RESPONSE)responseCode;

@end
