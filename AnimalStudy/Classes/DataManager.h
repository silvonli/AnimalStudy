//
//  DataManager.h
//  AnimalStudy
//
//  Created by sumomoxiaowen on 12-9-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef AnimalStudy_DataManager_h
#define AnimalStudy_DataManager_h


#define CROSSFADEDELAY          1                       // 场景切换延时

// 学习文字
#define STUDYWORDFONTSNAME_CN   "STHeitiSC-Medium"      // 字体
#define STUDYWORDFONTSNAME_EN   "Arial-BoldMT"
#define STUDYWORDFONTSSIZE_CN   38                      // 字号
#define STUDYWORDFONTSSIZE_EN   30
#define STUDYWORDSIZE_CN        CCSizeMake(190, 90)     // 位置
#define STUDYWORDSIZE_EN        CCSizeMake(170, 100)
#define STUDYWORDCOLOR          ccc3(60,64,200)           // 颜色

// 按钮位置
#define CHINESEBTNPOS           ccp(824, 118)
#define ENGILISHBTNPOS          ccp(200, 118)
#define RETURNBTNPOS            ccp(60, 708)            

// 放大动画
#define ACTIONSCALE1 CCScaleTo::actionWithDuration(0.2, 1.1)
#define ACTIONSCALE2 CCScaleTo::actionWithDuration(0.2, 1)

// 跳跃动画
#define ACTIONJUMP1  CCJumpBy::create(0.5,  CCPointMake(0,0), 30, 1)
#define ACTIONJUMP2  CCJumpBy::create(0.3,  CCPointMake(0,0), 18, 1)
#define ACTIONJUMP3  CCJumpBy::create(0.2,  CCPointMake(0,0), 12, 1)

#include "cocos2d.h"

using namespace cocos2d;

#define dataManager CDataManager::getDataManager()

class CDataManager
{

public:
    ~CDataManager();
    static CDataManager * getDataManager();
    
    // 区域文件
    const char* getAreaFileFrames(CCString area);
    const char* getAreaFileBatchNode(CCString area);
    const char* getAreaFileBackground(CCString area);
    const char* getAreaFileStudyBackground(CCString area);
    const char* getAreaFileStudyForeground(CCString area);
    
    // 区域对象
    int         getAreaObjectCount(CCString area);
    const char* getAreaObjectFrameName(CCString area, int index);
    CCPoint     getAreaObjectPosition(CCString area, int index);
    bool        isAreaObjectHasAnimation(CCString area, int index);
    int         getAreaObjectAnimationFrameNum(CCString area, int index);
    float       getAreaObjectAnimationFrameDelay(CCString area, int index);
    const char* getAreaObjectAnimationFrameNamePrefix(CCString area, int index);
    bool        areaObjectIsAnimal(CCString area, int index);
    const char* getAreaObjectPronunceCN(CCString area, int index);
    const char* getAreaObjectPronunceEN(CCString area, int index);
    const char* getAreaObjectPronunceJS(CCString area, int index);
    const char* getAreaObjectWordCN(CCString area, int index);
    const char* getAreaObjectWordEN(CCString area, int index);
    const char* getAreaObjectStudyAnimal(CCString area, int index);
    
    float        getAreaObjectScale(CCString area, int index);

private:
    CCDictionary* getAreaObject(CCString area, int index);

private:
    CDataManager();
    static CDataManager *_instance;
    
    CCDictionary *_data;
};

#endif
