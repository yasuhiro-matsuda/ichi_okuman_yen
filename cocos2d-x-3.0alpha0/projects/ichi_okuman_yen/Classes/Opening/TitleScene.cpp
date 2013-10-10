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
    
    return true;
}

void TitleScene::onEnterTransitionDidFinish()
{
    SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_TITLE, true);
    Layer::onEnterTransitionDidFinish();
}
