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
    
    //_studyObjects;
    _areaName = name;

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // create render texture and make it visible for testing purposes
    _rt = CCRenderTexture::create(size.width, size.height);
    _rt->setPosition(ccp(size.width/2, size.height/2));
    _rt->setVisible(false);
     this->addChild(_rt);
    
    // 创建背景
    CCSprite* backgroud = CCSprite::create(dataManager->getAreaFileBackground(_areaName));
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

    
    // 加载frames
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(dataManager->getAreaFileFrames(_areaName));
    
    // 创建对象
    for (int i=0; i<dataManager->getAreaObjectCount(_areaName); ++i) 
    {        
        const char *frameName = dataManager->getAreaObjectFrameName(_areaName, i);
        CCPoint pos           = dataManager->getAreaObjectPosition(_areaName, i);
        float   fSclae        = dataManager->getAreaObjectScale(_areaName, i);
        CCSprite *sprite      = CCSprite::createWithSpriteFrameName(frameName);        
        sprite->setPosition(pos);
        sprite->setTag(i);
        sprite->setScale(fSclae);
        this->addChild(sprite);
        
        // 带动画
        if ( dataManager->isAreaObjectHasAnimation(_areaName, i)) 
        {
            float delay        = dataManager->getAreaObjectAnimationFrameDelay(_areaName, i);
            const char* prefix = dataManager->getAreaObjectAnimationFrameNamePrefix(_areaName, i);
            int   frameNum     = dataManager->getAreaObjectAnimationFrameNum(_areaName, i);
            
            CCArray *arrFrames = CCArray::create(); // 动画帧数组
            for(int j=1; j<=frameNum; ++j) 
            {     
                CCString *name = CCString::createWithFormat("%s%02d.png",prefix, j);
                arrFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
            }
            if (dataManager->isAreaObjectAnimationFrameNeedReverse(_areaName, i))
            {
                CCArray *arrFramesRev = CCArray::createWithArray(arrFrames);
                arrFramesRev->reverseObjects();
                arrFrames->addObjectsFromArray(arrFramesRev);
            }
            CCAnimation *anim = CCAnimation::createWithSpriteFrames(arrFrames, delay);
            sprite->runAction(CCRepeatForever::create(CCAnimate::create(anim)));
        }
       
        if (dataManager->areaObjectCanStudy(_areaName, i)) 
        {
            _studyObjects.addObject(sprite);
        }
        
    }
    return true;
}

void CArea::animalTapFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
    int nIndex = sprite->getTag();
    
    CCScene *scene = CStudy::scene(_areaName, nIndex);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(TRANSITION_DURATION,scene));
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
    CCPoint touchLocation = pTouch->getLocationInView();		
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    for(int i = _studyObjects.count()-1; i >=0 ; --i)
	{
		CCSprite *tapedSprite = (CCSprite *)_studyObjects.objectAtIndex(i);
        
        if (isPointOnSprite(tapedSprite, touchLocation))
        {// 被tap的学习物品
                        
            CCFiniteTimeAction* ac = CCCallFuncN::create(this, callfuncN_selector(CArea::animalTapFinished));
            if (_areaName.compare("diningroom") == 0)
            {
                tapedSprite->runAction(CCSequence::create(ACTIONJUMP1, ACTIONJUMP2, ACTIONJUMP3, ac, NULL));
            }
            else
            {
                tapedSprite->runAction(CCSequence::create(ACTIONSCALE1, ACTIONSCALE2, ac, NULL));
            }
           
            break;
        }
	}
  
}

void CArea::btnReturnCallback(CCObject* pSender)
{
    CCScene *scene = CMainSelect::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeUp::create(TRANSITION_DURATION,scene));
}



bool CArea::isPointOnSprite(CCSprite * sprite, CCPoint point)
{
    
    bool bOn = false;
    CCRect rc = sprite->boundingBox();
    if (rc.containsPoint(point))
    {// 点在外包矩形内
        
        unsigned int w = 30;
        unsigned int h = 30;
        unsigned int numPixels = w * h;

        
        _rt->beginWithClear(0,0,0,0);
        glColorMask(1, 0, 0, 1);
        sprite->visit();
        glColorMask(1, 1, 1, 1);
        
        // read the pixel
        ccColor4B *buffer = (ccColor4B *)malloc( sizeof(ccColor4B) * numPixels );
        glReadPixels(point.x, point.y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        _rt->end();
            
        for(int i=0; i<numPixels; i++)
        {
            ccColor4B color = buffer[i];
            
            if (color.r > 0)
            {
                bOn = true;
                break;
            }
        }
 
        free(buffer);        
    }
    return bOn;
}
