#include "PrologueScene.h"
#include "SimpleAudioEngine.h"
#include "SplashScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
USING_NS_ICHI;


PrologueScene::PrologueScene()
: _state(State_TouchIgnore)
, _messageIndex(0)
, _messageArray(nullptr)
, _messageTTF(nullptr)
, _animationManager(nullptr)
{
    // こっちで初期化するより上のコロンで繋げて書いている方が余計な処理が入らない分軽くなるそう
}

PrologueScene::~PrologueScene()
{
    CCLOG("PrologueScene::~PrologueScene()");
	if (_messageArray != nullptr)
	{
		_messageArray->removeAllObjects();
		CC_SAFE_RELEASE(_messageArray);
	}
    CC_SAFE_RELEASE(_messageTTF);
    CC_SAFE_RELEASE(_animationManager);
}
Scene* PrologueScene::createScene()
{
    auto scene = Scene::create();
    
    auto nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    // プロローグシーンのローダーを追加
    nodeLoaderLibrary->registerNodeLoader("PrologueScene", PrologueSceneLoader::loader());
    CCBReader* reader = new CCBReader(nodeLoaderLibrary);
    // プロローグのccbiファイルを読み込む
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

    // プロローグの内容をセットする
    _messageArray = Array::create(
        ccs("お金持ちになりたい"),
        ccs("それは多くの人が\n子供の頃に持つ夢。"),
        ccs("ただ、多くの人は\n\nなれたらいいな\n\nという願望に留まってしまう。"),
        ccs("お金は生きていく分だけ\nあれば良い。"),
        ccs("その生きていく分をどのようにして取得するかを考え始める。"),
        ccs("自分の好きなことをしたい。"),
        ccs("人に喜んでもらいたい。"),
        ccs("家族との時間を大切にしたい。"),
        ccs("それぞれの想いから、\nみな仕事を選び働く。"),
        ccs("その結果\n\n運良くお金持ちになれた。\n\nという人もいるかもしれない。"),
        ccs("しかし"),
        ccs("お金のことを再優先に考え"),
        ccs("お金持ちになりたい\n\nという夢を実現するべく\n努力し続ける人もいる。"),
        ccs("この物語は\n\nお金持ちになりたいと願い。"),
        ccs("そして、その夢を追い続ける。"),
        ccs("そんな\n\nある一人の少女のお話。"),
        NULL);
    // retainしてあげないとこのブロック抜けたら消えてしまう
    _messageArray->retain();

    // シングルタップのみ受付
    setTouchEnabled(true);
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
    switch (_state)
    {
        // 開始アニメーションが終了していれば開始の終了アニメーションを再生
        case State_StartAnimationEnd:
            animationStartEnd();
            break;
        // テキスト表示開始アニメーション中か終了していればテキスト表示終了アニメーションを再生
        case State_TextStartAnimation:
        case State_TextStartAnimationEnd:
            animationTextEnd();
            break;
        // テキスト表示終了アニメーション中なら次のテキスト表示にスキップ
        case State_TextEndAnimation:
            // 最後はスルー
            if (_messageIndex == _messageArray->count())
            {
                return false;
            }
            animationTextStart();
            break;
        // それ以外は何もしない
        default:
            return false;
    }
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
    _state = State_TouchIgnore;
    _animationManager->runAnimationsForSequenceNamedTweenDuration("StartEnd", 0.0f);
}

void PrologueScene::animationTextStart()
{
    CCLOG("PrologueScene::animationTextStart()");
    _state = State_TextStartAnimation;
    // メッセージを更新してから表示する
    String* message = static_cast<String*>(_messageArray->getObjectAtIndex(_messageIndex));
    _messageTTF->setString(message->getCString());
    
    float duration = 0.0f;
    // 初回だけディレイを取る
    if (_messageIndex == 0)
    {
        duration = 0.3f;
    }
    _animationManager->runAnimationsForSequenceNamedTweenDuration("TextStart", duration);
    // 次のメッセージを表示するようにカウントアップ
    ++_messageIndex;
}
void PrologueScene::animationTextEnd()
{
    CCLOG("PrologueScene::animationTextEnd()");
    _state = State_TextEndAnimation;
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
        _state = State_StartAnimationEnd;
    }
    else if(strcmp(name,"StartEnd") == 0)
    {
        animationTextStart();
    }
    else if(strcmp(name,"TextStart") == 0)
    {
        _state = State_TextStartAnimationEnd;
    }
    else if(strcmp(name,"TextEnd") == 0)
    {
        // メッセージを表示。最後まで表示したら次のシーンへ
        if (_messageIndex < _messageArray->count())
        {
            animationTextStart();
        }
        else
        {
            // TODO チュートリアルを作成後切り替える;
            auto scene = SplashScene::createScene();
            // 0.5秒かけてブラックアウトしてシーンを切り替える
            auto fade = TransitionFade::create(REPLASE_SCENE_TIME_DEFAULT, scene, Color3B::BLACK);
            Director::getInstance()->replaceScene(fade);
        }
    }
}
