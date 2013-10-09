#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"
#include "AppMacros.h"

NS_ICHI_BEGIN

class TitleScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void playBGM(float milliSecond);

    CREATE_FUNC(TitleScene);
};

NS_ICHI_END

#endif // __TITLE_SCENE_H__
