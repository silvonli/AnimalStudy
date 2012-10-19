//
//  DataManager.h
//  AnimalStudy
//
//  Created by sumomoxiaowen on 12-9-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef AnimalStudy_DataManager_h
#define AnimalStudy_DataManager_h


#define CROSSFADEDELAY 1
#define JINGYUANIMATIONDELAY 0.2                    // 鲸鱼动画时间
#define STUDYWORDFONTSSIZE   30                     // 学习字字号
#define STUDYWORDSIZE        CCSizeMake(170, 100)   // 学习字大小

#define ACTIONSCALE1 CCScaleTo::actionWithDuration(0.5, 1.1)
#define ACTIONSCALE2 CCScaleTo::actionWithDuration(0.5, 1)

#define ACTIONJUMP1  CCJumpBy::create(0.5,  CCPointMake(0,0), 30, 1)
#define ACTIONJUMP2  CCJumpBy::create(0.3,  CCPointMake(0,0), 18, 1)
#define ACTIONJUMP3  CCJumpBy::create(0.2,  CCPointMake(0,0), 12, 1)
//
//CCActionInterval* waves = CCWaves::actionWithWaves(5, 20, true, false, ccg(15,10), 5);  
//CCActionInterval* shaky = CCShaky3D::actionWithRange(4, false, ccg(15,10), 5);  
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

private:
    CCDictionary* getAreaObject(CCString area, int index);

private:
    CDataManager();
    static CDataManager *_instance;
    
    CCDictionary *_data;
};

#endif
