//
//  AnimalStudyAppController.h
//  AnimalStudy
//
//  Created by sumomoxiaowen on 12-9-22.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    UIImageView  *splashView;
}

@end

