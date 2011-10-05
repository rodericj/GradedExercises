//
//  RJAppDelegate.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WFConnector/WFHardwareConnectorDelegate.h>

@interface RJAppDelegate : UIResponder <UIApplicationDelegate, UITabBarControllerDelegate, WFHardwareConnectorDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) UITabBarController *tabBarController;

@end
