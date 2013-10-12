#include "AppDelegate.h"
#include "SplashScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
USING_NS_ICHI;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();

    director->setOpenGLView(eglView);
	
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // 通常はiPhone retinaのサイズでデザインする
    Size designSize = Size(640, 960);
    // 端末のディスプレイサイズ
    Size winSize = director->getWinSize();
    CCLOG("winSize width: %4.1f, height: %4.1f", winSize.width, winSize.height);
    // 縦長の場合は横幅は固定で縦を伸ばす
    if (winSize.height > winSize.width * 1.5)
    {
        designSize.height = 640 * winSize.height / winSize.width;
    }
    // 全て表示するようにするので、アスペクト比がiPhone3.5インチの1.5より小さいタブレットは左右に黒帯が入って表示されることになる
    eglView->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
    
    // ファイルパスを追加
    auto fileUtils = FileUtils::getInstance();
    fileUtils->addSearchPath("ccbi/");
    
    // 音声の大きさ SEが聞こえ辛いのでBGMは控えめにする
    auto audio = SimpleAudioEngine::getInstance();
    audio->setBackgroundMusicVolume(0.5f);
    CCLOG("volume BGM: %1.3f, SE: %1.3f", audio->getBackgroundMusicVolume(), audio->getEffectsVolume());
    
    // create a scene. it's an autorelease object
    auto scene = SplashScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// ホームボタン押されたりでアプリが裏に回る時に呼ばれる
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    // BGM・SE一時停止
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// アプリが再開された時に呼ばれる
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    // BGM・SE再開
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
