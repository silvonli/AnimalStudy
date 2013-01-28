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

// 热区位置
#define POS_PARLOURHOT      ccp(300, 498)
#define POS_BEDROOMHOT      ccp(765, 485)
#define POS_DININGROOMHOT   ccp(428, 286)
#define POS_KITCHENHOT      ccp(635, 355)
#define POS_WASHROOMHOT     ccp(553, 613)
// 热区范围
static CCPoint polyParlourHot[]    = {ccp(278, 356), ccp(0,  585), ccp(308, 648), ccp(618, 437)};
static CCPoint polyBedroomHot[]    = {ccp(464, 545), ccp(716,602), ccp(1024,461), ccp(778, 378)};
static CCPoint polyDiningRoomHot[] = {ccp(404, 185), ccp(234,339), ccp(427,392),  ccp(622, 260)};
static CCPoint polyKitchenHot[]    = {ccp(622, 260), ccp(427,392), ccp(625,451),  ccp(835, 340)};
static CCPoint polyWashroomHot[]   = {ccp(548, 568), ccp(400,636), ccp(560,665),  ccp(716,602)};
// 渐隐动画
#define ACTIONFADE1 CCFadeIn::create(0.0f)
#define ACTIONFADE2 CCFadeOut::create(0.2f)

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
    CCSprite* backgroud = CCSprite::create("mainsel/bg.jpg");
    backgroud->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(backgroud);
    
    _parlourHot = CCSprite::create("mainsel/parlourHot.png");
    _parlourHot->setPosition(POS_PARLOURHOT);
    _parlourHot->setOpacity(0);
    this->addChild(_parlourHot);
    
    _bedroomHot = CCSprite::create("mainsel/bedroomHot.png");
    _bedroomHot->setPosition(POS_BEDROOMHOT);
    _bedroomHot->setOpacity(0);
    this->addChild(_bedroomHot);
    
    _diningRoomHot = CCSprite::create("mainsel/diningRoomHot.png");
    _diningRoomHot->setPosition(POS_DININGROOMHOT);
    _diningRoomHot->setOpacity(0);
    this->addChild(_diningRoomHot);
    
    _kitchenHot = CCSprite::create("mainsel/kitchenHot.png");
    _kitchenHot->setPosition(POS_KITCHENHOT);
    _kitchenHot->setOpacity(0);
    this->addChild(_kitchenHot);
    
    _washRoomHot = CCSprite::create("mainsel/washRoomHot.png");
    _washRoomHot->setPosition(POS_WASHROOMHOT);
    _washRoomHot->setOpacity(0);
    this->addChild(_washRoomHot);
    
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
    
   
        // 哪个热区被tap
    if (polyContainPnt(polyParlourHot, sizeof(polyParlourHot)/sizeof(CCPoint), touchLocation))
    {
        _parlourHot->runAction(CCSequence::create(ACTIONFADE1, ACTIONFADE2, NULL));
        _tapedArea = "parlour";
    }
    else if (polyContainPnt(polyDiningRoomHot, sizeof(polyDiningRoomHot)/sizeof(CCPoint), touchLocation))
    {
        _diningRoomHot->runAction(CCSequence::create(ACTIONFADE1, ACTIONFADE2, NULL));
        _tapedArea = "diningroom";
    }
    else if (polyContainPnt(polyKitchenHot, sizeof(polyKitchenHot)/sizeof(CCPoint), touchLocation))
    {
        _kitchenHot->runAction(CCSequence::create(ACTIONFADE1, ACTIONFADE2, NULL));
        _tapedArea = "kitchen";
    }
    else if (polyContainPnt(polyBedroomHot, sizeof(polyBedroomHot)/sizeof(CCPoint), touchLocation))
    {
        _bedroomHot ->runAction(CCSequence::create(ACTIONFADE1, ACTIONFADE2, NULL));
        _tapedArea = "bedroom";
    }
    else if (polyContainPnt(polyWashroomHot, sizeof(polyWashroomHot)/sizeof(CCPoint), touchLocation))
    {
        _washRoomHot->runAction(CCSequence::create(ACTIONFADE1, ACTIONFADE2, NULL));
        _tapedArea = "washroom";
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
    }
}