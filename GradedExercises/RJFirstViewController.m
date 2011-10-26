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
#import "GEDataModel.h"

@implementation RJFirstViewController

@synthesize fetchedResultsController = _fetchedResultsController;

#pragma mark - Connect Buttons toggled 
-(IBAction)connectHeartRate:(id)sender {
    NSLog(@"tapped");
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

#pragma mark - View lifecycle

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

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	// Do any additional setup after loading the view, typically from a nib.
    UIView *header = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 320, 60)] autorelease];
    header.backgroundColor = [UIColor blackColor];
    
    //Set up the start button
    UIButton *button = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 60, 60)];
    button.backgroundColor = [UIColor redColor];
    [button addTarget:self action:@selector(connectHeartRate:) forControlEvents:UIControlEventTouchUpInside];
    [header addSubview:button];
    [button release];
    
    self.tableView.tableHeaderView = header;
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
#pragma mark - WFSensorConnection state changed
- (void)connection:(WFSensorConnection*)connectionInfo stateChanged:(WFSensorConnectionStatus_t)connState {
    NSLog(@"something about a connection");
}

#pragma mark - FetchedResultsController

/**
 * The fetched results controller catches all SensorData in core data. This is used to populate the table with sensor info 
 */
-(NSFetchedResultsController *)fetchedResultsController {
    if (!_fetchedResultsController) {
        NSManagedObjectContext *context = [GEDataModel sharedInstance].managedObjectContext;
        NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
        
        // Configure the request's entity, and optionally its predicate.
        NSEntityDescription *entity = [NSEntityDescription entityForName:@"SensorData" inManagedObjectContext:context];
        fetchRequest.entity = entity;
        
        //Sort boilerplate
        NSSortDescriptor *sortDescriptor = [[NSSortDescriptor alloc] initWithKey:@"timestamp" ascending:NO];
        NSArray *sortDescriptors = [[NSArray alloc] initWithObjects:sortDescriptor, nil];
        [fetchRequest setSortDescriptors:sortDescriptors];
        [sortDescriptors release];
        [sortDescriptor release];
        
        NSFetchedResultsController *controller = [[NSFetchedResultsController alloc]
                                                  initWithFetchRequest:fetchRequest
                                                  managedObjectContext:context
                                                  sectionNameKeyPath:nil
                                                  cacheName:nil];
        [fetchRequest release];
        controller.delegate = self;
        _fetchedResultsController = controller;
        NSError *error;    
        BOOL success = [_fetchedResultsController performFetch:&error];
        if (!success) {
            NSLog(@"this fetch failed");
        }


    }
    
    return _fetchedResultsController;
}

#pragma mark - UITableViewDataSource
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSLog(@"row %@", indexPath);
}
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return [[self.fetchedResultsController sections] count];
}

- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    id <NSFetchedResultsSectionInfo> sectionInfo = [[self.fetchedResultsController sections] objectAtIndex:section];
    return [sectionInfo numberOfObjects];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSString *reuse = @"reuseablestringforheartrates";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:reuse];
    
    if (!cell) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:reuse] autorelease];
    }
    
    //TODO optiize this. Should use the actual fetchedResultsController
    GEHeartRateData *managedObject = (GEHeartRateData *)[_fetchedResultsController objectAtIndexPath:indexPath];
    cell.textLabel.text = [NSString stringWithFormat:@"%@", managedObject.timestamp];
    cell.detailTextLabel.text = [NSString stringWithFormat:@"%@",managedObject.computedHeartRate];
    // Configure the cell with data from the managed object.
    return cell;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section { 
    id <NSFetchedResultsSectionInfo> sectionInfo = [[self.fetchedResultsController sections] objectAtIndex:section];
    return [sectionInfo name];
}

- (NSArray *)sectionIndexTitlesForTableView:(UITableView *)tableView {
    return [self.fetchedResultsController sectionIndexTitles];
}

- (NSInteger)tableView:(UITableView *)tableView sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)index {
    return [self.fetchedResultsController sectionForSectionIndexTitle:title atIndex:index];
}

#pragma mark - NSFetchedResultsControllerDelegate
/*
 Assume self has a property 'tableView' -- as is the case for an instance of a UITableViewController
 subclass -- and a method configureCell:atIndexPath: which updates the contents of a given cell
 with information from a managed object at the given index path in the fetched results controller.
 */

- (void)controllerWillChangeContent:(NSFetchedResultsController *)controller {
    [self.tableView beginUpdates];
}


- (void)controller:(NSFetchedResultsController *)controller didChangeSection:(id <NSFetchedResultsSectionInfo>)sectionInfo
           atIndex:(NSUInteger)sectionIndex forChangeType:(NSFetchedResultsChangeType)type {
    
    switch(type) {
        case NSFetchedResultsChangeInsert:
            [self.tableView insertSections:[NSIndexSet indexSetWithIndex:sectionIndex]
                          withRowAnimation:UITableViewRowAnimationTop];
            break;
            
        case NSFetchedResultsChangeDelete:
            [self.tableView deleteSections:[NSIndexSet indexSetWithIndex:sectionIndex]
                          withRowAnimation:UITableViewRowAnimationFade];
            break;
    }
}


- (void)controller:(NSFetchedResultsController *)controller didChangeObject:(id)anObject
       atIndexPath:(NSIndexPath *)indexPath forChangeType:(NSFetchedResultsChangeType)type
      newIndexPath:(NSIndexPath *)newIndexPath {
    
    UITableView *tableView = self.tableView;
    
    switch(type) {
            
        case NSFetchedResultsChangeInsert:
            [tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:newIndexPath]
                             withRowAnimation:UITableViewRowAnimationFade];
            break;
            
        case NSFetchedResultsChangeDelete:
            [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath]
                             withRowAnimation:UITableViewRowAnimationFade];
            break;
            
        case NSFetchedResultsChangeUpdate:
//            [self configureCell:[tableView cellForRowAtIndexPath:indexPath]
//                    atIndexPath:indexPath];
            break;
            
        case NSFetchedResultsChangeMove:
            [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath]
                             withRowAnimation:UITableViewRowAnimationFade];
            [tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:newIndexPath]
                             withRowAnimation:UITableViewRowAnimationFade];
            break;
    }
}


- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller {
    [self.tableView endUpdates];
}

-(void)dealloc {
    self.fetchedResultsController = nil;
    [super dealloc];
}
@end
