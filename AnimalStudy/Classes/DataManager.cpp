//
//  DataManager.cpp
//  AnimalStudy
//
//  Created by sumomoxiaowen on 12-9-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <cstddef>
#include "DataManager.h"

CDataManager* CDataManager::_instance = NULL;


CDataManager* CDataManager::getDataManager()
{
    if (NULL == _instance) 
    {
        _instance = new CDataManager;
    }
    return _instance;
}
CDataManager::CDataManager()
{
    CCString dataPlistFile = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Data.plist");
    _data = CCDictionary::dictionaryWithContentsOfFile(dataPlistFile.getCString());
    _data->retain();
}
CDataManager::~CDataManager()
{
    if(_instance)
    {
        _data->release();
        delete _instance;
        _instance = NULL;
    }

}

const char* CDataManager::getAreaFileFrames(CCString area)
{
    CCDictionary *pAreaDict  = (CCDictionary*) _data->objectForKey(area.getCString());
    return pAreaDict->valueForKey("SpriteFramesFile")->getCString();
}

const char* CDataManager::getAreaFileBatchNode(CCString area)
{
    CCDictionary *pAreaDict  = (CCDictionary*) _data->objectForKey(area.getCString());
    return  pAreaDict->valueForKey("BatchNodeFile")->getCString();
}

const char* CDataManager::getAreaFileBackground(CCString area)
{
    CCDictionary *pAreaDict  = (CCDictionary*) _data->objectForKey(area.getCString());
    return  pAreaDict->valueForKey("BackgroundFile")->getCString();  
}

const char* CDataManager::getAreaFileStudyBackground(CCString area)
{
    CCDictionary *pAreaDict  = (CCDictionary*) _data->objectForKey(area.getCString());
    return  pAreaDict->valueForKey("StudyBackgroundFile")->getCString();  
}
const char* CDataManager::getAreaFileStudyForeground(CCString area)
{
    CCDictionary *pAreaDict  = (CCDictionary*) _data->objectForKey(area.getCString());
    return  pAreaDict->valueForKey("StudyForegroundFile")->getCString();   
}
int CDataManager::getAreaObjectCount(CCString area)
{
    CCDictionary *pAreaDict  = (CCDictionary*) _data->objectForKey(area.getCString());
    CCArray *sprites = (CCArray*) pAreaDict->objectForKey("Objects");
    return sprites->count();
}
const char* CDataManager::getAreaObjectFrameName(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("FrameName")->getCString();
}

CCPoint CDataManager::getAreaObjectPosition(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    float x = spriteDict->valueForKey("PositionX")->floatValue();
    float y = spriteDict->valueForKey("PositionY")->floatValue();
    return ccp(x, y);
}
bool CDataManager::isAreaObjectHasAnimation(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("HasAnimation")->boolValue();
}
int CDataManager::getAreaObjectAnimationFrameNum(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("AnimationFrameNum")->intValue();
}
bool CDataManager::isAreaObjectAnimationFrameNeedReverse(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("AnimationFrameNeedReverse")->boolValue();
}
float CDataManager::getAreaObjectAnimationFrameDelay(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("AnimationFrameDelay")->floatValue();
}

const char* CDataManager::getAreaObjectAnimationFrameNamePrefix(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("AnimationFrameNamePrefix")->getCString();
}

bool CDataManager::areaObjectCanStudy(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("CanStudy")->boolValue();
}

const char* CDataManager::getAreaObjectPronunceCN(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("PronunceCN")->getCString();
}

const char* CDataManager::getAreaObjectPronunceEN(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("PronunceEN")->getCString();
}

const char* CDataManager::getAreaObjectPronunceJS(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("PronunceJS")->getCString();
}

const char* CDataManager::getAreaObjectWordCN(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("WordCN")->getCString();
}

const char* CDataManager::getAreaObjectWordEN(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("WordEN")->getCString();
}
const char* CDataManager::getAreaObjectStudyAnimal(CCString area, int index)
{
    CCDictionary *spriteDict = getAreaObject(area, index);
    return spriteDict->valueForKey("StudyAnimal")->getCString();
}

float CDataManager::getAreaObjectScale(CCString area, int index)
{
    float fRet =  1;
    CCDictionary *spriteDict = getAreaObject(area, index);
    const CCString *cRet = spriteDict->valueForKey("Scale");
    if (cRet->length() != 0)
    {
        fRet = cRet->floatValue();
    }
    return fRet;
    
}
CCDictionary * CDataManager::getAreaObject(CCString area, int index)
{
    CCDictionary *pAreaDict  = (CCDictionary*) _data->objectForKey(area.getCString());
    CCArray *sprites = (CCArray*) pAreaDict->objectForKey("Objects");
    return (CCDictionary*)sprites->objectAtIndex(index);
}
