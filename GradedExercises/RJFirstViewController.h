//
//  RJFirstViewController.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WFConnector/WFConnector.h>
#import <CoreData/CoreData.h>

@interface RJFirstViewController : UITableViewController <WFSensorConnectionDelegate, 
UITableViewDelegate, UITableViewDataSource, NSFetchedResultsControllerDelegate> {
    
    NSFetchedResultsController *_fetchedResultsController;
    
}

@property (nonatomic, retain) NSFetchedResultsController *fetchedResultsController;

-(IBAction)connectPowerMeter:(id)sender;

-(IBAction)connectHeartRate:(id)sender;

@end
