//
//  GEHeartRateDataManager.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GECommonSensorManager.h"

@class WFHeartrateConnection;

@interface GEHeartRateDataManager : GECommonSensorManager

@property (readonly, nonatomic) WFHeartrateConnection *heartrateConnection;

+(GEHeartRateDataManager *)sharedInstance;

@end
