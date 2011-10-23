/*
 *  WFAntFileManagerDelegate.h
 *  WFConnector
 *
 *  Created by Michael Moore on 6/4/10.
 *  Copyright 2010 Wahoo Fitness. All rights reserved.
 *
 */

#import <WFConnector/wf_antfs_types.h>

@class _WFAntFileManager;
@class WFAntFSDirectory;


/**
 * The WFAntFileManagerDelegate protocol declares the interface that
 * WFAntFileManager delegates must implement.
 *
 * The WFAntFileManagerDelegate protocol should be adopted in classes where
 * ANT FS data is processed.  It is common to adopt this protocol in the same
 * class where the WFAntFileManager instance is created, but this is not
 * strictly necessary.  Status updates and request responses will be delivered
 * to the delegate.
 */
@protocol WFAntFileManagerDelegate <NSObject>

@required

/**
 * Alerts the delegate that the WFAntFileManager has finished a download.
 *
 * @param antFileManager The delegating WFAntFileManager instance.
 *
 * @param bSuccess <c>TRUE</c> if the download was successful, otherwise
 * <c>FALSE</c>.
 *
 * @param filePath The path to the downloaded FIT file.
 */
- (void)antFileManager:(_WFAntFileManager*)antFileManager downloadFinished:(BOOL)bSuccess filePath:(NSString*)filePath;

/**
 * Alerts the delegate that the WFAntFileManager has finished a download.
 *
 * @param antFileManager The delegating WFAntFileManager instance.
 *
 * @param bSuccess <c>TRUE</c> if the download was successful, otherwise
 * <c>FALSE</c>.
 */
- (void)antFileManager:(_WFAntFileManager*)antFileManager instanceCreated:(BOOL)bSuccess;

/**
 * Alerts the delegate that the device passkey has been updated.
 *
 * This method gives the delegate an opportunity to store the device passkey
 * after a pairing operation.  The passkey should be stored and used in
 * future authentication requests.  This avoids the need to pair every time
 * the device is connected.
 *
 * @param antFileManager The delegating WFAntFileManager instance.
 *
 * @param pucPasskey A pointer to the buffer where the updated passkey is
 * located.
 *
 * @param ucLength The length of the passkey, in bytes.
 */
- (void)antFileManager:(_WFAntFileManager*)antFileManager updatePasskey:(UCHAR*)pucPasskey length:(UCHAR)ucLength;

@optional

/**
 * Alerts the delegate that the WFAntFileManager instance received a response
 * to a request for directory information.
 *
 * @param antFileManager The delegating WFAntFileManager instance.
 *
 * @param directoryInfo A WFAntFSDirectory instance containing the directory
 * information for the device.
 */
- (void)antFileManager:(_WFAntFileManager*)antFileManager receivedDirectoryInfo:(WFAntFSDirectory*)directoryInfo;

/**
 * Alerts the delegate that the WFAntFileManager instance received a response
 * from the device.
 *
 * @param antFileManager The delegating WFAntFileManager instance.
 *
 * @param responseCode The ::ANTFS_RESPONSE response code sent from the device.
 */
- (void)antFileManager:(_WFAntFileManager*)antFileManager receivedResponse:(ANTFS_RESPONSE)responseCode;

/**
 * Alerts the delegate of file download progress.
 *
 * @param antFileManager The delegating WFAntFileManager instance.
 *
 * @param bytesReceived The total number of bytes that have been received.
 */
- (void)antFileManager:(_WFAntFileManager*)antFileManager downloadProgress:(ULONG)bytesReceived;

- (void)antFileManager:(_WFAntFileManager*)antFileManager parseFITProgress:(float)progress;

@end