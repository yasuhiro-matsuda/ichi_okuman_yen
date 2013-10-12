#include "PrologueScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
USING_NS_ICHI;


PrologueScene::PrologueScene()
: _messageTTF(nullptr)
, _animationManager(nullptr)
{
    
}

Scene* PrologueScene::createScene()
{
    auto scene = Scene::create();
    // タイトルのccbiファイルを読み込む
    auto nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    // プロローグシーンのローダーを追加
    nodeLoaderLibrary->registerNodeLoader("PrologueScene", PrologueSceneLoader::loader());

    CCBReader* reader = new CCBReader(nodeLoaderLibrary);
    auto prologueNode = reader->readNodeGraphFromFile("ccbi/PrologueScene.ccbi");
    // アニメーションマネージャーをセットする
    static_cast<PrologueScene*>(prologueNode)->setAnimationManager(reader->getAnimationManager());
    scene->addChild(prologueNode);
    // 開放
    reader->release();

    return scene;
}


bool PrologueScene::init()
{
    CCLOG("PrologueScene::init()");
    if ( !Layer::init() )
    {
        return false;
    }
    
    // BGM・SEのプリロード
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_PROLOGUE);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_TOUCH_NORMAL);

    // シングルタップのみ受付 最初のアニメーションまではタップさせない
    setTouchEnabled(false);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    return true;
}

void PrologueScene::onEnterTransitionDidFinish()
{
    CCLOG("PrologueScene::onEnterTransitionDidFinish()");
    Layer::onEnterTransitionDidFinish();

    SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_PROLOGUE, true);
    animationStart();
}

bool PrologueScene::onTouchBegan(Touch *touch, Event *event)
{
    CCLOG("PrologueScene::onTouchBegan()");
    SimpleAudioEngine::getInstance()->playEffect(SE_TOUCH_NORMAL);
    return false;
}

void PrologueScene::animationStart()
{
    CCLOG("PrologueScene::animationStart()");
    _animationManager->runAnimationsForSequenceNamedTweenDuration("Start", 0.0f);
}

void PrologueScene::animationStartEnd()
{
    CCLOG("PrologueScene::animationStartEnd()");
    _animationManager->runAnimationsForSequenceNamedTweenDuration("StartEnd", 0.0f);
}

void PrologueScene::animationTextStart()
{
    CCLOG("PrologueScene::animationTextStart()");
    _animationManager->runAnimationsForSequenceNamedTweenDuration("TextStart", 0.0f);
}
void PrologueScene::animationTextEnd()
{
    CCLOG("PrologueScene::animationTextEnd()");
    _animationManager->runAnimationsForSequenceNamedTweenDuration("TextEnd", 0.0f);
}


bool PrologueScene::onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode)
{
    CCLOG("onAssignCCBMember: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_messageTTF", LabelTTF*, _messageTTF);

    return true;
}

void PrologueScene::setAnimationManager(CCBAnimationManager *pAnimationManager)
{
    CCLOG("PrologueScene::setAnimationManager()");
    CC_SAFE_RELEASE_NULL(_animationManager);
    _animationManager = pAnimationManager;
    CC_SAFE_RETAIN(_animationManager);
    // アニメーション終了を受け取れるようにデリゲートをセット
    _animationManager->setDelegate(this);
}

void PrologueScene::completedAnimationSequenceNamed(const char *name)
{
    CCLOG("completedAnimation: %s", name);
    // タイムラインの名前によって処理を分ける。必要のあるものだけ指定する
    if(strcmp(name,"Start") == 0)
    {
        setTouchEnabled(true);
        animationStartEnd();
    }
    else if(strcmp(name,"StartEnd") == 0)
    {
        animationTextStart();
    }
    else if(strcmp(name,"TextStart") == 0)
    {
        animationTextEnd();
    }
    else if(strcmp(name,"TextEnd") == 0)
    {
        animationTextStart();
    }
}
