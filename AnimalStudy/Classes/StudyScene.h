//
//  StudyScene.h
//  StudyStudy
//
//  Created by sumomoxiaowen on 12-9-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef AnimalStudy_StudyScene_h
#define AnimalStudy_StudyScene_h

#include "cocos2d.h"

USING_NS_CC;

class CStudy: public CCLayer
{
    
public:
    CStudy();
    virtual ~CStudy();
    
    static CCScene* scene(CCString area, int nIndex);
    
    static CStudy* animalWithAreaAndIndex(CCString area, int nIndex);
    
    bool initWithAreaAndIndex(CCString area, int nIndex);    
    
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    
    void btnReturnCallback(CCObject* pSender);
    void btnChineseCallback(CCObject* pSender);
    void btnEnglishCallback(CCObject* pSender);
private:
    CCString _areaName;
    int      _index;
    CCSprite *_studiedSprite;
  
};

#endif
