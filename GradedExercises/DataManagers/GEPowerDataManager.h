//
//  GEPowerDataManager.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GECommonSensorManager.h"

@class WFBikePowerConnection;

@interface GEPowerDataManager : GECommonSensorManager {

}

@property (readonly, nonatomic) WFBikePowerConnection* bikePowerConnection;

@end
