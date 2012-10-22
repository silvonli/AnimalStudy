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
    CCSprite* backgroud = CCSprite::spriteWithFile("mainsel/bg.png");
    backgroud->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(backgroud);
    
    // 按钮
    CCMenuItemImage *pLack = CCMenuItemImage::create("mainsel/lackNor.png",
                                                     "mainsel/lackSel.png",
                                                      this,
                                                      menu_selector(CMainSelect::lakeCallback) );
    
    CCMenuItemImage *pForest = CCMenuItemImage::create("mainsel/forestNor.png",
                                                       "mainsel/forestSel.png",
                                                       this,
                                                       menu_selector(CMainSelect::forestCallback) );
    
    CCMenuItemImage *pDesert = CCMenuItemImage::create("mainsel/desertNor.png",
                                                       "mainsel/desertSel.png",
                                                        this,
                                                        menu_selector(CMainSelect::desertCallback) );
    
    CCMenuItemImage *pPrairie = CCMenuItemImage::create("mainsel/prairieNor.png",
                                                        "mainsel/prairieSel.png",
                                                        this,
                                                        menu_selector(CMainSelect::prairieCallback) );
    
    pLack->setPosition(    ccp(171, 437) );
    pForest->setPosition(  ccp(539, 401) );
    pDesert->setPosition(  ccp(864, 411) );
    pPrairie->setPosition( ccp(392, 208) );
    
   
    CCMenu* pMenu = CCMenu::create(pLack, pForest, pDesert, pPrairie, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    // 创建sprite sheet
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("mainsel/jingyu.plist");
    CCSpriteBatchNode *spriteSheet = CCSpriteBatchNode::batchNodeWithFile("mainsel/jingyu.png");
    this->addChild(spriteSheet);
    
    // 创建对象
    CCSprite *sprite = CCSprite::spriteWithSpriteFrameName("jingyu01.png");        
    sprite->setPosition(ccp(920,220));
    spriteSheet->addChild(sprite, 0);
          
    CCArray *arrShang = CCArray::array(); // 动画帧数组
    for(int i=1; i<=8; ++i)
    {     
        CCString *name = CCString::stringWithFormat("jingyu%02d.png", i);
        arrShang->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
    
    CCArray *arrPeng = CCArray::array(); // 动画帧数组
    for(int i=9; i<=11; ++i)
    {
        CCString *name = CCString::stringWithFormat("jingyu%02d.png", i);
        arrPeng->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
    
    CCFiniteTimeAction *delay = CCDelayTime::actionWithDuration(1);

    CCAnimate* anShang = CCAnimate::actionWithAnimation(CCAnimation::animationWithSpriteFrames(arrShang, 0.2));
    CCAnimate* anPeng  = CCAnimate::actionWithAnimation(CCAnimation::animationWithSpriteFrames(arrPeng, 0.2));
    sprite->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)CCSequence::actions(anShang, delay, anPeng, anPeng->reverse(), anShang->reverse(),delay,delay, delay ,NULL)));
    return true;
}



void CMainSelect::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool CMainSelect::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void CMainSelect::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{    
    CCPoint touchLocation = pTouch->locationInView();		
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
      
    // tap 海洋
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if (touchLocation.y<size.height*3/4.0) 
    {
        CCScene *scene = CArea::scene("ocean");
        CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(CROSSFADEDELAY,scene));
    }
}

void CMainSelect::lakeCallback(CCObject* pSender)
{
    CCScene *scene = CArea::scene("lack");
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(CROSSFADEDELAY,scene));
}
void CMainSelect::forestCallback(CCObject* pSender)
{
    CCScene *scene = CArea::scene("forest");
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(CROSSFADEDELAY,scene));
}
void CMainSelect::desertCallback(CCObject* pSender)
{
    CCScene *scene = CArea::scene("desert");
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(CROSSFADEDELAY,scene));
}
void CMainSelect::prairieCallback(CCObject* pSender)
{
    CCScene *scene = CArea::scene("prairie");
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(CROSSFADEDELAY,scene));

}
