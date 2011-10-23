//
//  WFHardwareConnector+AntFS.h
//  WFConnector
//
//  Created by Michael Moore on 6/23/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFHardwareConnector.h>
#import <WFConnector/WFAntFileManagerDelegate.h>
#import <WFConnector/WFAntFSClientDelegate.h>


@class WFAntFileManager;
@class WFAntFSClientBase;


@interface WFHardwareConnector (AntFS)

/**
 * Releases resources used by the specified WFAntFileManager.
 *
 * @note The WFAntFileManager requires resources which are allocated
 * and maintained by the Wahoo Fitness API.  Instances should be
 * created via the WFHardwareConnector::requestAntFileManager:toDelegate:
 * method, and released via this method.  Please do not invoke the
 * NSObject::release directly on the WFAntFileManager instance.  Doing
 * so will not properly release all resources used by the API during the
 * life of the WFAntFileManager instance.
 * <br /><br />
 * It is best not to retain the WFAntFileManger instance, but rather to
 * use assignment when passing a reference.  If retain must be used, take care
 * to use the corresponding release to ensure that the retain count returns
 * to one, and not below before invoking this method.
 *
 * @param fileManager  The WFAntFileManager instance to be released.
 *
 * @return <c>TRUE</c> if resources were released successfully, otherwise
 * <c>FALSE</c>.
 */
- (BOOL)releaseAntFileManager:(WFAntFileManager*)fileManager;

/**
 * Releases resources used by the specified WFAntFSClientBase.
 *
 * @note The WFAntFSClientBase requires resources which are allocated
 * and maintained by the Wahoo Fitness API.  Instances should be
 * created via the WFHardwareConnector::requestAntFSClient:toDelegate:
 * method, and released via this method.  Please do not invoke the
 * NSObject::release directly on the WFAntFSClientBase instance.  Doing
 * so will not properly release all resources used by the API during the
 * life of the WFAntFSClientBase instance.
 * <br /><br />
 * It is best not to retain the WFAntFSClientBase instance, but rather to
 * use assignment when passing a reference.  If retain must be used, take care
 * to use the corresponding release to ensure that the retain count returns
 * to one, and not below before invoking this method.
 *
 * @param fsClient  The WFAntFSClientBase instance to be released.
 *
 * @return <c>TRUE</c> if resources were released successfully, otherwise
 * <c>FALSE</c>.
 */
- (BOOL)releaseAntFSClient:(WFAntFSClientBase*)fsClient;

/**
 * Requests that a WFAntFileManager instance be created and initialized.
 *
 * @note The ANT file manager requires resources which are allocated and
 * maintained by the Wahoo Fitness API.  Please be sure to invoke the
 * WFHardwareConnector::releaseAntFileManager: method to release resources
 * when the instance is no longer needed.
 *
 * @param deviceType The type of device for which the ANT file manager is to
 * be created.  ANT FS profiles are different among device types, the specific
 * type of ANT File manager created will be the type which is able to process
 * files for the specified device type.
 *
 * @param theDelegate The delegate which will be alerted when the ANT file
 * manager instance is ready.  The ANT file manager creation is an asynchronous
 * operation.  This method will return immediately, and the delegate method
 * will be invoked when the operation is complete.
 *
 * @return <c>TRUE</c> if the ANT file manager creation operation is started
 * successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)requestAntFileManager:(WFAntFSDeviceType)deviceType toDelegate:(id<WFAntFileManagerDelegate>)theDelegate;

/**
 * Requests that a WFAntFSClientBase instance be created and initialized.
 *
 * @note The WFAntFSClientBase requires resources which are allocated and
 * maintained by the Wahoo Fitness API.  Please be sure to invoke the
 * WFHardwareConnector::releaseAntFSClient: method to release resources
 * when the instance is no longer needed.
 *
 * @param deviceType The type of device for which the WFAntFSClientBase is to
 * be created.  ANT FS profiles are different among device types, the specific
 * type of WFAntFSClientBase created will be the type which is able to process
 * data for the specified device type.
 *
 * @param theDelegate The delegate which will be alerted when the WFAntFSClientBase
 * instance is ready.  The WFAntFSClientBase creation is an asynchronous
 * operation.  This method will return immediately, and the delegate method
 * will be invoked when the operation is complete.
 *
 * @return <c>TRUE</c> if the WFAntFSClientBase creation operation is started
 * successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)requestAntFSClient:(WFAntFSDeviceType)deviceType toDelegate:(id<WFAntFSClientDelegate>)theDelegate;

@end
