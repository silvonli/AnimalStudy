//
//  AnimalStudyAppDelegate.cpp
//  AnimalStudy
//
//  Created by sumomoxiaowen on 12-9-22.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#include "AppDelegate.h"
#include "MainSelectScene.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

    // create a scene. it's an autorelease object
    CCScene *pScene = CMainSelect::scene();

    // run
    pDirector->runWithScene(pScene);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.14);//设置音量0.0-1.0
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgmusic.mp3", true);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
