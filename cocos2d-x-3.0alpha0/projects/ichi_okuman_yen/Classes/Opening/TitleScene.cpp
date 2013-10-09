#include "TitleScene.h"
#include "CCBReader/CCBReader.h"
#include "CCBReader/CCNodeLoaderLibrary.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
USING_NS_ICHI;

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();

    scene->addChild(layer);

    return scene;
}


bool TitleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    // BGMのプリロード
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_TITLE);
    
    // タイトルのccbiファイルを読み込む
    auto nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    CCBReader* reader = new CCBReader(nodeLoaderLibrary);
    auto TitleNode = reader->readNodeGraphFromFile("ccbi/TitleScene.ccbi");
    
    // 追加
    this->addChild(TitleNode, 0);
    
    // 開放
    reader->release();
    
    // BGM再生(シーン切り替え時間分遅らせる)
    this->scheduleOnce(schedule_selector(TitleScene::playBGM), REPLASE_SCENE_TIME_DEFAULT);

    return true;
}

void TitleScene::playBGM(float milliSecond)
{
    CCLOG("playBGM delay time: %4.4f ms", milliSecond);
    SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_TITLE, true);
}
