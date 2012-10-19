//
//  AreaScene.h
//  AnimalStudy
//
//  Created by sumomoxiaowen on 12-9-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef AnimalStudy_AreaScene_h
#define AnimalStudy_AreaScene_h

#include "cocos2d.h"

USING_NS_CC;

class CArea: public CCLayer
{

public:
    CArea();
    virtual ~CArea();
    

    static CCScene * scene(CCString areaName);
    static CArea * areaWithName(CCString name);
  
    bool initWithName(CCString name);
    
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    
    void btnReturnCallback(CCObject* pSender);
    void animalTapFinished(CCNode* sender);
    
    
    CCArray _animalArr;
    
    CCString _areaName;
    
};  

#endif
