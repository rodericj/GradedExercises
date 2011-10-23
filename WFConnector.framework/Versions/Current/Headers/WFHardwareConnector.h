//
//  WFHardwareConnector.h
//  WFHardwareConnector
//
//  Created by Michael Moore on 2/9/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/hardware_connector_types.h>
#import <WFConnector/_WFHardwareConnector.h>


#define WF_API_VERSION  @"2.0.1"


@class WFSensorConnection;
@class WFConnectionParams;
@class WFConnectorSettings;
@class WFFisicaInfo;


#pragma mark -
#pragma mark WFHardwareConnector Interface Declaration

/**
 * The WFHardwareConnector represents the bridge between the fisica
 * sensor receiver (dongle or case) and the iPhone application.
 *
 * The connector, along with the WFHardwareConnectorDelegate protocol, provide
 * an interface to the fisica device.  The connector is used to configure
 * the device and obtain the latest data from the sensors.  The delegate
 * protocol updates the delegate of status changes to the sensors and data
 * availability.
 */
@interface WFHardwareConnector : _WFHardwareConnector
{
}


#pragma mark -
#pragma mark WFHardwareConnector Property Declarations

/**
 * Gets the current Wahoo Fitness API version string.
 */
@property (nonatomic, readonly) NSString* apiVersion;

/**
 * Gets a boolean value indicating whether the fisica device is connected.
 *
 * This property specifies the status of the dongle or case accessory.  When
 * the device is physically connected to the iPhone and communication has been
 * established, the value will be <code>true</code>.  To determine the status
 * of remote sensors (heartrate, FootPod, etc.), see the
 * WFHardwareConnector::isSensorConnected: method.
 */
@property (nonatomic, readonly) BOOL isFisicaConnected;

/**
 * Gets a WFFisicaInfo instance describing the properties and capabilities of
 * the currently connected fisica hardware.
 */
@property (nonatomic, readonly) WFFisicaInfo* fisicaInfo;

/**
 * Gets or sets the sample rate in seconds.
 *
 * The value of this property will determine how often data updates are sent
 * to the delegate.  The WFHardwareConnectorDelegate::hardwareConnectorHasData
 * method will be invoked at the sample rate.
 */
@property (nonatomic, assign) NSTimeInterval sampleRate;

/** Gets the persistent settings for the Wahoo API. */
@property (nonatomic, readonly) WFConnectorSettings* settings;


#pragma mark -
#pragma mark WFHardwareConnector Method Declarations

/**
 * Returns the number of unallocated communication channels.
 *
 * @return The number of unallocated channels.
 */
- (UCHAR)availableChannelCount;

/**
 * Returns the current state of the WFHardwareConnector.
 *
 * @return The current state.
 * <br /><br />
 * The return value is a bit-field representing the current state.  Values are:
 * <br /><br />
 * <table>
 * <tr><td><b>Value</b></td><td><b>Description</b></td></tr>
 * <tr><td>WF_HWCONN_STATE_NOT_CONNECTED</td><td>The fisica device is not
 * physically connected.</td></tr>
 * <tr><td>WF_HWCONN_STATE_CONNECTED</td><td>The fisica device is physically
 * connected.</td></tr>
 * <tr><td>WF_HWCONN_STATE_ACTIVE</td><td>The fisica device is in normal
 * operation mode.</td></tr>
 * <tr><td>WF_HWCONN_STATE_RESET</td><td>The fisica device is performing a
 * reset operation.</td></tr>
 * </table>
 * <br /><br />
 * With the exception of WF_HWCONN_STATE_NOT_CONNECTED, these values are
 * masked together to define the current state.  For example, the normal
 * operational state is defined by:
 * <br /><br />
 * <code>UCHAR ucNormalState = WF_HWCONN_STATE_CONNECTED | WF_HWCONN_STATE_ACTIVE;</code>
 */
- (WFHardwareConnectorState_t) currentState;

/**
 * Returns the firmware version running on the fisica device.
 *
 * @return A 32-bit unsigned integer representing the firmware version.  The
 * lower 24 bits contain the data.  The bytes are arranged {MSB...LSB} as
 * {0, Major Version, Minor Version, Revision}.
 */
- (ULONG)firmwareVersion;

/**
 * Returns an array of WFSensorConnection instances for all connected sensors
 * of the specified type.
 *
 * @param sensorType The type of sensor for which to get connections.  If this
 * parameter is <c>WF_SENSORTYPE_NONE</c>, all connections for any type are returned.
 *
 * @return An NSArray containing the matching WFSensorConnection instances.
 */
- (NSArray*)getSensorConnections:(WFSensorType_t)sensorType;

/**
 * Initializes a sensor connection request based on the specified parameters.
 *
 * This method will initiate a connection request based on the specified
 * parameters, and return a WFSensorConnection instance which may be used to
 * manage the connection.  The connection process is asynchronous.  Unless
 * a sensor specified in the parameters is already connected, it is likely
 * that the sensor will not have connected when this method returns.
 *
 * The WFSensorConnection may be used to monitor the connection status.  There
 * are two ways to be notified when the sensor connection is established.  The
 * WFHardwareConnectorDelegate::hardwareConnector:connectedSensor: is invoked
 * whenever any sensor connection is established.  When using this method, the
 * connectionInfo parameter must be checked to determine which sensor has
 * connected (if multiple connections were requested).  The other option is
 * to set the WFSensorConnection::delegate property on the instance returned.
 * The delegate will be alerted to any change in the connection status.
 *
 * The WFSensorConnection class is an abstract base class for sensor connection
 * management.  The actual object type returned will be determined by the
 * WFConnectionParams::sensorType value.  It is recommended that the instance
 * returned be cast as the specific type, and then cached as an instance
 * member used for managing the connection.  The WFSensorConnection is used
 * to retrieve data from the sensor, as well as to disconnect, or monitor the
 * state of the connection.
 *
 * A best-practices outline for connecting to a heart rate monitor follows:
 *
 * <ol>
 * <li>Create a WFConnectionParams instance and set the
 * WFConnectionParams::sensorType property to <c>WF_SENSORTYPE_HEARTRATE</c></li>
 *
 * <li>Create a WFDeviceParams instance and set its values to a previously
 * paired heart rate monitor (see the WFSensorConnection documentation for
 * information about initial pairing).</li>
 *
 * <li>Assign the WFDeviceParams instance to the WFConnectionParams::device1
 * property.</li>
 *
 * <li>Repeat the last two steps for any other previously paired heart rate
 * monitors (up to four).  Just use the device2, device3, or device4 property
 * instead of device1 specified in the last step.</li>
 *
 * <li>Invoke the WFHardwareConnector::requestSensorConnection: method.</li>
 *
 * <li>Cast the return value as a WFHeartrateConnection and cache as an
 * instance member.</li>
 *
 * <li>Set the WFSensorConnection::delegate property.</li>
 *
 * <li>Once the connection has been established, use the
 * WFHeartrateConnection::getHeartrateData method to retrieve a WFHeartrateData
 * instance.  This instance will contain the latest heart rate data.</li>
 *
 * <li>When the heart rate monitor is no longer needed, use the
 * WFSensorConnection::disconnect method to end the connection.</li>
 *
 * <li>After the connection is ended, the
 * WFSensorConnectionDelegate::connection:stateChanged: method will be invoked.
 * Check that the WFSensorConnection::isConnected is <c>FALSE</c>.  Release
 * the previously cached WFSensorConnection instance.</li>
 * </ol>
 *
 * @param params A WFConnectionParams instance which specifies the connection
 * parameters.
 *
 * @return If a device matching the connection parameters is already connected,
 * the existing WFSensorConnection instance is returned, and no new connection
 * is initialized.  If an error occurs (such as no unallocated communication
 * channels available), the return is <c>nil</c>.  Otherwise, the value returned
 * is a WFSensorConnection instance which may be used to manage the connection.
 */
- (WFSensorConnection*)requestSensorConnection:(WFConnectionParams*)params;

/**
 * Initializes a sensor connection request, with limited search range specified.
 *
 * @note This method is not available for older fisica keys.  These devices use
 * the AP1 ANT chip which does not support proximity searching.  If the connected
 * fisica is the AP1 version, this method will return <c>nil</c>.
 *
 * @param params A WFConnectionParams instance which specifies the connection
 * parameters.
 *
 * @param proximity A WFProximityRange_t value which limits the proximity of the
 * search.  There are ten range levels available, with <c>WF_PROXIMITY_RANGE_1</c>
 * being the closest.  When <c>WF_PROXIMITY_RANGE_1</c> is specified, the device
 * must be very close to the fisica key for a connection to be established.  The
 * search distance increases with each range level.
 *
 * @return If a device matching the connection parameters is already connected,
 * the existing WFSensorConnection instance is returned, and no new connection
 * is initialized.  If an error occurs (such as no unallocated communication
 * channels available), the return is <c>nil</c>.  Otherwise, the value returned
 * is a WFSensorConnection instance which may be used to manage the connection.
 */
- (WFSensorConnection*)requestSensorConnection:(WFConnectionParams*)params withProximity:(WFProximityRange_t)proximity;

/**
 * Prepares the WFHardwareConnector for background mode.
 *
 * @note This method should be invoked when the application receives
 * notification that the app is entering background mode.  When the
 * application returns from background mode, the
 * WFHardwareConnector::returnFromBackground method should be invoked.
 */
- (void)prepareForBackground;

/**
 * Resets all sensor connections and sets the fisica device to IDLE mode.
 *
 * @note This method should be used with care, as it will reset all
 * active sensor connections.  To disconnect individual sensors, use the
 * WFSensorConnection::disconnect method instead.
 *
 * @see WFHardwareConnector::requestSensorConnection:
 * @see WFHardwareConnector::getSensorConnections:
 *
 * @return <c>TRUE</c> if all sensors were disconnected and the fisica device
 * set to IDLE mode, otherwise <c>FALSE</c>.
 */
- (BOOL)resetConnections;

/**
 * Resets the sample timer, based on the current sample rate.
 */
- (void)resetSampleTimer;

/**
 * Restores normal operation upon returning from background mode.
 *
 * @note The WFHardwareConnector::prepareForBackground method should be invoked
 * when the application receives notification that the app is entering
 * background mode.  When the application returns from background mode, this
 * method should be invoked to restore normal operation.
 */
 - (void)returnFromBackground;

/**
 * Specifies whether the WFHardwareConnector should invoke the
 * WFHardwareConnectorDelegate::hardwareConnectorHasData method only when new
 * data is available.
 *
 * By default, the WFHardwareConnectorDelegate::hardwareConnectorHasData
 * method is invoked at the sample rate whether or not new data is present.
 * If the checkData value is <c>TRUE</c>, the delegate method will only be
 * invoked if there is new data present on at least one sensor.
 *
 * @param checkData <c>TRUE</c> if the
 * WFHardwareConnectorDelegate::hardwareConnectorHasData method should only
 * be invoked when new data is present.  Otherwise <c>FALSE</c>.
 */
- (void)setSampleTimerDataCheck:(BOOL)checkData;


#pragma mark -
#pragma mark WFHardwareConnector Data Access Methods

/**
 * Resets all accumulated and calculated data for all sensor types.
 *
 * This method can be invoked at the beginning of a workout to put the sensors
 * in a known state.
 *
 * @return <c>TRUE</c> if the reset was successful, otherwise <c>FALSE</c>.
 */
- (BOOL)resetAllSensorData;


#pragma mark -
#pragma mark WFHardwareConnector Class Method Declarations

/**
 * Returns the singleton WFHardwareConnector instance.
 *
 * As of API version 2.0, the WFHardwareConnector is enforced as a singleton.
 * This method may be used to obtain a reference to that instance.  If the
 * instance does not yet exist when this method is invoked, it will be created.
 *
 * @return The WFHardwareConnector singleton instance.
 */
+ (WFHardwareConnector*)sharedConnector;

@end
