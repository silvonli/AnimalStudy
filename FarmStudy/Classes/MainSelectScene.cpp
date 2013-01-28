//
//  MainSelectScene.cpp
//  AnimalStudy
//
//  Created by sumomoxiaowen on 12-10-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MainSelectScene.h"
#include "AreaScene.h"
#include "DataManager.h"


// 位置
#define AREAPOS_FRUIT           ccp(311, 540)
#define AREAPOS_VEGETABLE       ccp(559, 106)
#define AREAPOS_LIVESTOCK       ccp(922, 462)
#define AREAPOS_CAOA            ccp(96,  345)
#define AREAPOS_CAOB            ccp(853, 296)
#define AREAPOS_SUN             ccp(892, 704)

// 热区范围
static CCPoint polyFruit[]      = {ccp(668, 642),  ccp(0,  757), ccp(0, 319), ccp(673, 453)};
static CCPoint polyVegetable[]  = {ccp(417, 341),  ccp(0, 197),  ccp(0,0),    ccp(1024, 0), ccp(1024, 190)};
static CCPoint polyLivestock[]  = {ccp(1024, 632), ccp(603,359), ccp(1024,288)};

// 渐隐动画
#define ACTIONTINT1 CCTintTo::create(0.1f, 150, 150, 0)
#define ACTIONTINT2 CCTintTo::create(0.1f, 255, 255, 255)


CCScene* CMainSelect::scene()
{
    CCScene *scene = CCScene::create();
    CMainSelect *layer = CMainSelect::create();
    scene->addChild(layer);
    
    return scene;
}


bool CMainSelect::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->setTouchEnabled(true);
   
    // 创建背景
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* backgroud = CCSprite::create("mainsel/bg.png");
    backgroud->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(backgroud);
    
   
    _fruit = CCSprite::create("mainsel/fruit.png");
    _fruit->setPosition(AREAPOS_FRUIT);
    this->addChild(_fruit);
    
    _vegetable = CCSprite::create("mainsel/vegetable.png");
    _vegetable->setPosition(AREAPOS_VEGETABLE);
    this->addChild(_vegetable);
    
    _livestock = CCSprite::create("mainsel/livestock.png");
    _livestock->setPosition(AREAPOS_LIVESTOCK);
    this->addChild(_livestock);
    
    CCSprite *sprtCaoA = CCSprite::create("mainsel/CaoA.png");
    sprtCaoA->setPosition(AREAPOS_CAOA);
    this->addChild(sprtCaoA);
    
    CCSprite *sprtCaoB = CCSprite::create("mainsel/CaoB.png");
    sprtCaoB->setPosition(AREAPOS_CAOB);
    this->addChild(sprtCaoB);
    
    CCSprite *sprtSunShine = CCSprite::create("mainsel/sunshine.png");
    sprtSunShine->setPosition(AREAPOS_SUN);
    this->addChild(sprtSunShine);
    
    CCSprite *sprtSun = CCSprite::create("mainsel/sun.png");
    sprtSun->setPosition(AREAPOS_SUN);
    this->addChild(sprtSun);
    
    // 创建太阳
    CCScaleTo *scaleAc1 = CCScaleTo::create(0.1, 1.05);
    CCScaleTo *scaleAc2 = CCScaleTo::create(0.1, 1.08);
    CCScaleTo *scaleAc3 = CCScaleTo::create(0.1, 1.1);
    CCScaleTo *scaleAc4 = CCScaleTo::create(0.1, 1);
    sprtSunShine->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(scaleAc1, scaleAc2, scaleAc3, scaleAc4, NULL)));

    return true;
}



void CMainSelect::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}


bool CMainSelect::polyContainPnt(CCPoint vert[], int numVert, CCPoint test)
{
    bool bContain = false;
    int i, j;
    
    for (i = 0, j = numVert-1; i < numVert; j = i++)
    {
        if ((vert[i].y>test.y) != (vert[j].y>test.y) &&
            (test.x < (vert[j].x-vert[i].x) * (test.y-vert[i].y) / (vert[j].y-vert[i].y) + vert[i].x) )
        {
            bContain = !bContain;
        }
    }
    return bContain;
}


bool CMainSelect::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
    CCPoint touchLocation = pTouch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    
    // 哪个区被tap
    if (polyContainPnt(polyFruit, sizeof(polyFruit)/sizeof(CCPoint), touchLocation))
    {
        _fruit->runAction(CCSequence::create(ACTIONTINT1, ACTIONTINT2, NULL));
        _tapedArea = "fruit";
    }
    else if (polyContainPnt(polyVegetable, sizeof(polyVegetable)/sizeof(CCPoint), touchLocation))
    {
        _vegetable->runAction(CCSequence::create(ACTIONTINT1, ACTIONTINT2, NULL));
        _tapedArea = "vegetable";
    }
    else if (polyContainPnt(polyLivestock, sizeof(polyLivestock)/sizeof(CCPoint), touchLocation))
    {
        _livestock->runAction(CCSequence::create(ACTIONTINT1, ACTIONTINT2, NULL));
        _tapedArea = "livestock";
    }
    else
    {
        _tapedArea = "";
    }
    
	return true;
}

void CMainSelect::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{    
    if (_tapedArea.length() != 0)
    {
        CCScene *scene = CArea::scene(_tapedArea);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(TRANSITION_DURATION,scene));
    }}
