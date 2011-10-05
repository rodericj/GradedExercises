//
//  GEDataModel.h
//  GradedExercises
//
//  Created by roderic campbell on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFBikePowerData.h>
#import "GEPowerData.h"

#define kGEPowerDataType    @"GEPowerData"

@interface GEDataModel : NSObject

+(GEPowerData *)insertObject:(NSObject *)object withType:(NSString *)type saveAfter:(BOOL)saveAfter;

@end
