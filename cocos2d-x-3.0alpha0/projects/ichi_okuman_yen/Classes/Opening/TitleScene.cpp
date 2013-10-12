#include "TitleScene.h"
#include "CCBReader/CCBReader.h"
#include "CCBReader/CCNodeLoaderLibrary.h"
#include "SimpleAudioEngine.h"
#include "PrologueScene.h"

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
    CCLOG("TitleScene::init()");
    if ( !Layer::init() )
    {
        return false;
    }
    // BGM・SEのプリロード
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_TITLE);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_TOUCH_NORMAL);
    
    // タイトルのccbiファイルを読み込む
    auto nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    CCBReader* reader = new CCBReader(nodeLoaderLibrary);
    auto TitleNode = reader->readNodeGraphFromFile("ccbi/TitleScene.ccbi");
    
    // 追加
    this->addChild(TitleNode, 0);
    
    // 開放
    reader->release();
    
    // シングルタップのみ受付
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

    return true;
}

void TitleScene::onEnterTransitionDidFinish()
{
    CCLOG("TitleScene::onEnterTransitionDidFinish()");
    Layer::onEnterTransitionDidFinish();

    SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_TITLE, true);

    
}

bool TitleScene::onTouchBegan(Touch *touch, Event *event)
{
    CCLOG("TitleScene::onTouchBegan()");
    SimpleAudioEngine::getInstance()->playEffect(SE_TOUCH_NORMAL);
    auto scene = PrologueScene::createScene();
    // 0.5秒かけてブラックアウトしてプロローグに移動する
    auto fade = TransitionFade::create(REPLASE_SCENE_TIME_DEFAULT, scene, Color3B::BLACK);
    Director::getInstance()->replaceScene(fade);
    return false;
}
