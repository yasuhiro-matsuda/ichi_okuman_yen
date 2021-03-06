#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"
#include "AppMacros.h"

NS_ICHI_BEGIN

class TitleScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    // シーン切り替え後にBGMを再生
    virtual void onEnterTransitionDidFinish() override;
    // タップでゲーム開始させる
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
    CREATE_FUNC(TitleScene);
};

NS_ICHI_END

#endif // __TITLE_SCENE_H__
