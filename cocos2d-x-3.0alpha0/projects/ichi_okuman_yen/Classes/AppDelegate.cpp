#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

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
    fileUtils->addSearchPath("ccbi/ccbResources/");

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
