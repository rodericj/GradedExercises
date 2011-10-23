//
//  WFSensorConnection.h
//  WFConnector
//
//  Created by Michael Moore on 10/20/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <WFConnector/_WFSensorConnection.h>
#import <WFConnector/WFSensorConnectionDelegate.h>


/**
 * Represents the connection for an ANT sensor.
 *
 * The WFSensorConnection is the entry point for dealing with an ANT sensor.
 * Once the instance is obtained (via WFHardwareConnector::requestSensorConnection:),
 * it can be used to determine connection state, disconnect, or retrieve data.
 *
 * The pairing procedure is as follows:
 * <ol>
 * <li>Create a new WFConnectionParams instance</li>
 * <li>Specify the WFConnectionParams::sensorType but do not specify any
 * devices.  This will specify a wildcard search.</li>
 * <li>Invoke the WFHardwareConnector::requestSensorConnection: method.</li>
 * <li>The WFSensorConnectionDelegate::connection:stateChanged: method will be
 * invoked when the connection is established.</li>
 * <li>Confirm that the WFSensorConnection::isConnected property is <c>TRUE</c>.</li>
 * <li>Store the WFSensorConnection::deviceNumber and
 * WFSensorConnection::transmissionType values for future connections to this
 * sensor.</li>
 * </ol>
 */
@interface WFSensorConnection : _WFSensorConnection
{
	/** \cond InterfaceDocs */

	id<WFSensorConnectionDelegate> delegate;
	
	/** \endcond */
}


/**
 * Specifies the WFSensorConnectionDelegate instance which will handle callback
 * methods for this WFSensorConnection.
 */
@property (nonatomic, retain) id<WFSensorConnectionDelegate> delegate;

/**
 * Gets the ANT sensor type for this WFSensorConnection.
 */
@property (nonatomic, readonly) WFSensorType_t sensorType;

/**
 * <c>TRUE</c> if the sensor is currently connected, otherwise <c>FALSE</c>.
 */
@property (nonatomic, readonly) BOOL isConnected;

/**
 * Gets a boolean value indicating whether this WFSensorConnection instance
 * is valid.
 *
 * The WFSensorConnection is invalidated (cannot be used for communication with
 * the sensor) when the sensor is disconnected, or when the API is reset.
 */
@property (nonatomic, readonly) BOOL isValid;

/**
 * Gets the ANT transmission type of the connected sensor.
 */
@property (nonatomic, readonly) UCHAR transmissionType;

/**
 * Gets the ANT device ID of the connected sensor.
 */
@property (nonatomic, readonly) USHORT deviceNumber;

/**
 * Gets the current connection status.
 */
@property (nonatomic, readonly) WFSensorConnectionStatus_t connectionStatus;


/**
 * Disconnects the sensor.
 */
- (void)disconnect;

/**
 * Retrieves the most current data available from the sensor.
 *
 * @note WFSensorData is an abstract base class for all sensor data types.
 * The specific type will be determined by the type of sensor.  The instance
 * returned must be cast to the specific type in order to be useful.
 *
 * @return A WFSensorData derived instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFSensorData*)getData;

/**
 * Retrieves the most current raw data available from the sensor.
 *
 * @note This method will return raw (unformatted) data from the sensor.
 * It is made available for applications which require processing of data
 * as close to the original measured values a possible.  There may be other
 * rarely used data available via this method as well.  For most applications,
 * the WFSensorConnection::getData method should be used instead.
 * <br /><br />
 * WFSensorData is an abstract base class for all sensor data types.
 * The specific type will be determined by the type of sensor.  The instance
 * returned must be cast to the specific type in order to be useful.
 *
 * @return A WFSensorData derived instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFSensorData*)getRawData;

/**
 * Returns a boolean value indicating whether new data is available.
 *
 * @return <c>TRUE</c> if new data is available since the last time
 * WFSensorConnection::getData was invoked, otherwise <c>FALSE</c>.
 */
- (BOOL)hasData;

/**
 * Returns the signal efficiency for the connected sensor.
 *
 * @return The ratio of messages received from the sensor over the
 * number of messages expected.  This value should give a good
 * indication of the reception quality for the sensor.  If the
 * sensor is not currently connected, the return value is <c>-1</c>.
 */
- (float)signalEfficiency;

@end
