#include "SplashScene.h"
#include "TitleScene.h"
#include "CCBReader/CCBReader.h"
#include "CCBReader/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();

    scene->addChild(layer);

    return scene;
}


bool SplashScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    // スプラッシュのccbiファイルを読み込む
    auto nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    CCBReader* reader = new CCBReader(nodeLoaderLibrary);
    auto splashNode = reader->readNodeGraphFromFile("ccbi/SplashScene.ccbi");
    
    // 追加
    this->addChild(splashNode, 0);
    
    // 開放
    reader->release();
    
    // 1.5秒後にタイトルに移動する
    this->scheduleOnce(schedule_selector(SplashScene::gameStart), 1.5f);

    return true;
}

void SplashScene::gameStart(float milliSecond)
{
    CCLOG("Splash display time: %4.4f ms", milliSecond);
    auto scene = TitleScene::createScene();
    // 0.5秒かけてホワイトアウトしてタイトルに移動する
    TransitionFade* fade = TransitionFade::create(0.5f, scene, Color3B::WHITE);
    Director::getInstance()->replaceScene(fade);
}
