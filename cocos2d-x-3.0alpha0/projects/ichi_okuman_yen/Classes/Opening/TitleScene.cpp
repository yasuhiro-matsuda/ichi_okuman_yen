#include "TitleScene.h"
#include "CCBReader/CCBReader.h"
#include "CCBReader/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;

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

