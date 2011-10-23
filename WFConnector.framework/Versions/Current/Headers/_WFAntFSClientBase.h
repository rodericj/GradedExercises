//
//  _WFAntFSClientBase.h
//  WFConnector
//
//  Created by Michael Moore on 1/28/11.
//  Copyright 2011 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFAntFSClientDelegate.h>


@interface _WFAntFSClientBase : NSObject
{
}

@property (nonatomic, assign) id<WFAntFSClientDelegate> delegate;

@end
