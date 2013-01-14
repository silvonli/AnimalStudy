//
//  AreaScene.cpp
//  AnimalStudy
//
//  Created by sumomoxiaowen on 12-9-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "AreaScene.h"
#include "SimpleAudioEngine.h"
#include "DataManager.h"
#include "StudyScene.h"
#include "MainSelectScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* CArea::scene(CCString areaName)
{
    CCScene *scene = CCScene::create();
    CArea *layer = CArea::areaWithName(areaName);
   
    scene->addChild(layer);
    return scene;
}

CArea::CArea()
{
}

CArea::~CArea()
{

}

CArea* CArea::areaWithName(CCString name)
{
    CArea *pLayer = new CArea();
    if (pLayer && pLayer->initWithName(name))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;

}
bool CArea::initWithName(CCString name)
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    //_animalArr;
    _areaName = name;

    
    // 创建背景
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* backgroud = CCSprite::spriteWithFile(dataManager->getAreaFileBackground(_areaName));
    backgroud->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(backgroud);
    
    // 按钮
    CCMenuItemImage *pReturn = CCMenuItemImage::create("btnReturnNor.png",
                                                       "btnReturnSel.png",
                                                       this,
                                                       menu_selector(CArea::btnReturnCallback) );
    
    pReturn->setPosition(RETURNBTNPOS);

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pReturn, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    
    // 创建sprite sheet
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(dataManager->getAreaFileFrames(_areaName));
    CCSpriteBatchNode *spriteSheet = CCSpriteBatchNode::batchNodeWithFile(dataManager->getAreaFileBatchNode(_areaName));
    this->addChild(spriteSheet);
    
    // 创建对象
    for (int i=0; i<dataManager->getAreaObjectCount(_areaName); ++i) 
    {        
        const char *frameName = dataManager->getAreaObjectFrameName(_areaName, i);
        CCPoint pos           = dataManager->getAreaObjectPosition(_areaName, i);
        float   fSclae        = dataManager->getAreaObjectScale(_areaName, i);
        CCSprite *sprite = CCSprite::spriteWithSpriteFrameName(frameName);        
        sprite->setPosition(pos);
        sprite->setTag(i);
        sprite->setScale(fSclae);
        spriteSheet->addChild(sprite, 0, i);
        
        // 带动画
        if ( dataManager->isAreaObjectHasAnimation(_areaName, i)) 
        {
            float delay        = dataManager->getAreaObjectAnimationFrameDelay(_areaName, i);
            const char* prefix = dataManager->getAreaObjectAnimationFrameNamePrefix(_areaName, i);
            int   frameNum     = dataManager->getAreaObjectAnimationFrameNum(_areaName, i);
            
            CCArray *arrFrames = CCArray::array(); // 动画帧数组
            for(int j=1; j<=frameNum; ++j) 
            {     
                CCString *name = CCString::stringWithFormat("%s%02d.png",prefix, j);
                arrFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
            }
            if (dataManager->isAreaObjectAnimationFrameNeedReverse(_areaName, i))
            {
                CCArray *arrFramesRev = CCArray::arrayWithArray(arrFrames);
                arrFramesRev->reverseObjects();
                arrFrames->addObjectsFromArray(arrFramesRev);
            }
            CCAnimation *anim = CCAnimation::animationWithSpriteFrames(arrFrames, delay);
            sprite->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(anim)));
        }
       
        if (dataManager->areaObjectCanStudy(_areaName, i)) 
        {
            _animalArr.addObject(sprite);
        }
        
    }
    return true;
}


void CArea::animalTapFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
    int nIndex = sprite->getTag();
    
    CCScene *scene = CStudy::scene(_areaName, nIndex);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::transitionWithDuration(TRANSITION_DURATION,scene));
}

void CArea::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool CArea::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void CArea::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{    
    CCPoint touchLocation = pTouch->locationInView();		
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    for(int i = _animalArr.count()-1; i>=0 ; --i)
	{
		CCSprite *tapAnimal = (CCSprite *)_animalArr.objectAtIndex(i);
        
        if (CCRect::CCRectContainsPoint(tapAnimal->boundingBox(), touchLocation))
        {// 被tap的动物
                        
            CCFiniteTimeAction* ac = CCCallFuncN::actionWithTarget(this, callfuncN_selector(CArea::animalTapFinished));
            tapAnimal->runAction(CCSequence::actions(ACTIONJUMP1, ACTIONJUMP2, ACTIONJUMP3, ac, NULL));
            break;
        }
	}
  
}

void CArea::btnReturnCallback(CCObject* pSender)
{
    CCScene *scene = CMainSelect::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeUp::transitionWithDuration(TRANSITION_DURATION,scene));
}

