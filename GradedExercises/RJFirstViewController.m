//
//  RJFirstViewController.m
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "RJFirstViewController.h"
#import <WFConnector/WFBikePowerData.h>
#import "WFConnector/WFConnectorSettings.h"
#import "WFConnector/WFConnectionParams.h"
#import "WFConnector/WFHardwareConnector.h"

#import "GEHeartRateDataManager.h"

@implementation RJFirstViewController

-(IBAction)connectHeartRate:(id)sender {
    WFConnectionParams* params = nil;
    //
    // if wildcard search is specified, create empty connection params.
    if (YES)// wildcardSwitch.on )
    {
        params = [[[WFConnectionParams alloc] init] autorelease];
        params.sensorType = WF_SENSORTYPE_HEARTRATE;
    }
    //
    // otherwise, get the params from the stored settings.
    else
    {
        params = [[WFHardwareConnector sharedConnector].settings connectionParamsForSensorType:WF_SENSORTYPE_HEARTRATE];
    }
    
    if ( params != nil)
    {
        // if the connection request is a wildcard, use proximity search.
        if ( params.isWildcard )
        {
            [GEHeartRateDataManager sharedInstance].sensorConnection = [[WFHardwareConnector sharedConnector] requestSensorConnection:params withProximity:WF_PROXIMITY_RANGE_1];
        }
        // otherwise, use normal connection request.
        else
        {
            [GEHeartRateDataManager sharedInstance].sensorConnection = [[WFHardwareConnector sharedConnector] requestSensorConnection:params];
        }
        
        // set delegate to receive connection status changes.
        [GEHeartRateDataManager sharedInstance].sensorConnection.delegate = self;
    }

    
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"First", @"First");
        self.tabBarItem.image = [UIImage imageNamed:@"first"];
    }
    return self;
}
							
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (void)connection:(WFSensorConnection*)connectionInfo stateChanged:(WFSensorConnectionStatus_t)connState {
    NSLog(@"something about a connection");
}


@end
