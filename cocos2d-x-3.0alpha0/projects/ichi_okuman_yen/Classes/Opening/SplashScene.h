#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"
#include "AppMacros.h"

NS_ICHI_BEGIN

class SplashScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void gameStart(float milliSecond);

    CREATE_FUNC(SplashScene);
};

NS_ICHI_END

#endif // __SPLASH_SCENE_H__
