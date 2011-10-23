/*
 *  _WFAntFileManager.h
 *  WFConnector
 *
 *  Created by Michael Moore on 8/4/10.
 *  Copyright 2010 Wahoo Fitness. All rights reserved.
 *
 */


#import <Foundation/Foundation.h>
#import <WFConnector/WFAntFileManagerDelegate.h>


@interface _WFAntFileManager : NSObject
{
}


@property (nonatomic, assign) id<WFAntFileManagerDelegate> delegate;

@end
