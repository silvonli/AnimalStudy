//
//  StudyScene.cpp
//  StudyScene
//
//  Created by sumomoxiaowen on 12-9-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#include "StudyScene.h"
#include "SimpleAudioEngine.h"
#include "DataManager.h"
#include "AreaScene.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* CStudy::scene(CCString area, int nIndex)
{
    CCScene *scene = CCScene::create();
    CStudy *layer = CStudy::animalWithAreaAndIndex(area, nIndex);
    scene->addChild(layer);
    return scene;
}

CStudy::CStudy() 
{
}

CStudy::~CStudy()
{
}

CStudy* CStudy::animalWithAreaAndIndex(CCString area, int nIndex)
{
    CStudy *pLayer = new CStudy();
    if (pLayer && pLayer->initWithAreaAndIndex(area, nIndex))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;

}
bool CStudy::initWithAreaAndIndex(CCString area, int nIndex)
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    
    _areaName = area;
    _index    = nIndex;
    
    // 背景
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* bg = CCSprite::spriteWithFile(dataManager->getAreaFileStudyBackground(_areaName));
    bg->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(bg);
    
    CCSprite* fg = CCSprite::spriteWithFile(dataManager->getAreaFileStudyForeground(_areaName));
    fg->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(fg);
    
    // 动物
    _animal = CCSprite::spriteWithFile(dataManager->getAreaObjectStudyAnimal(_areaName, _index));
    _animal->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(_animal);
   
    
    // 按钮
    CCMenuItemImage *pReturn = CCMenuItemImage::create( "btnReturnNor.png",
                                                        "btnReturnSel.png",
                                                        this,
                                                        menu_selector(CStudy::btnReturnCallback) );
    
    CCMenuItemImage *pChinese = CCMenuItemImage::create("btnPronunceNor.png",
                                                        "btnPronunceSel.png",
                                                        this,
                                                        menu_selector(CStudy::btnChineseCallback) );
    
    CCMenuItemImage *pEnglish = CCMenuItemImage::create("btnPronunceNor.png",
                                                        "btnPronunceSel.png",
                                                        this,
                                                        menu_selector(CStudy::btnEnglishCallback) );
   
    pReturn->setPosition(  RETURNBTNPOS );
    pChinese->setPosition( CHINESEBTNPOS );
    pEnglish->setPosition( ENGILISHBTNPOS );
    
    // 文字
    CCLabelTTF* wordCN = CCLabelTTF::labelWithString(dataManager->getAreaObjectWordCN(_areaName, _index), STUDYWORDSIZE_CN, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter, STUDYWORDFONTSNAME_CN, STUDYWORDFONTSSIZE_CN);
    wordCN->setAnchorPoint(ccp(0,0));
    wordCN->setColor(STUDYWORDCOLOR);
    pChinese->addChild(wordCN);
    
    CCLabelTTF* wordEN = CCLabelTTF::labelWithString(dataManager->getAreaObjectWordEN(_areaName, _index),STUDYWORDSIZE_EN, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter, STUDYWORDFONTSNAME_EN, STUDYWORDFONTSSIZE_EN);
    wordEN->setAnchorPoint(ccp(0,0));
    wordEN->setColor(STUDYWORDCOLOR);
    pEnglish->addChild(wordEN);
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pReturn, pChinese, pEnglish, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);


                        
    return true;
}

void CStudy::btnReturnCallback(CCObject* pSender)
{
    CCScene *scene = CArea::scene(_areaName);
    CCDirector::sharedDirector()->replaceScene(scene);
}
void CStudy::btnChineseCallback(CCObject* pSender)
{
    const char* pronunce = dataManager->getAreaObjectPronunceCN(_areaName, _index);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(pronunce, false);
}
void CStudy::btnEnglishCallback(CCObject* pSender)
{
    const char * pronunce = dataManager->getAreaObjectPronunceEN(_areaName, _index);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(pronunce, false);
}



void CStudy::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool CStudy::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void CStudy::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{    
    CCPoint touchLocation = pTouch->locationInView();		
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
        
    if (CCRect::CCRectContainsPoint(_animal->boundingBox(), touchLocation))
    {// 动物被tap

        _animal->runAction(CCSequence::actions(ACTIONSCALE1, ACTIONSCALE2, NULL));
  
        const char * pronunce = dataManager->getAreaObjectPronunceJS(_areaName, _index);
        if (strlen(pronunce) != 0)
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(pronunce, false);
        }
    }
}


