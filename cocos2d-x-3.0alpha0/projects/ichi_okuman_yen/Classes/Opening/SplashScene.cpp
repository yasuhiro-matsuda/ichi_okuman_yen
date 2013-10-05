#include "SplashScene.h"
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

    return true;
}

