//
//  MainSelectScene.h
//  AnimalStudy
//
//  Created by sumomoxiaowen on 12-10-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef AnimalStudy_MainSelectScene_h
#define AnimalStudy_MainSelectScene_h


#include "cocos2d.h"

USING_NS_CC;

class CMainSelect : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene();
  
    // implement the "static node()" method manually
    CREATE_FUNC(CMainSelect);
    
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    bool polyContainPnt(CCPoint vert[], int numVert, CCPoint test);
private:

    CCSprite *_parlourHot;
    CCSprite *_bedroomHot;
    CCSprite *_diningRoomHot;
    CCSprite *_kitchenHot;
    CCSprite *_washRoomHot;
    
    CCString _tapedArea;


};

#endif
