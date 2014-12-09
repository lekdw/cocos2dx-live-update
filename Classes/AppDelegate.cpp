#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	// 캐쉬 디렉토리에 에셋 디렉토리가 없으면 생성한다.
	std::string assetPath = FileUtils::getInstance()->getWritablePath() + "asset/";

	if (!FileUtils::getInstance()->isDirectoryExist(assetPath))
		FileUtils::getInstance()->createDirectory(assetPath);

	// 캐쉬 디렉토리의 에셋 디렉토리에서 먼저 리소스 파일을 찾을 수 있도록 설정한다.
	// 요청하는 리소스 파일이 캐쉬 디렉토리의 에셋 디렉토리에 없을 경우는 번들 리소스 디렉토리에서 찾는다.
	std::vector<std::string> searchPath;
	searchPath.push_back(assetPath);

	for (std::string path : FileUtils::getInstance()->getSearchPaths()) {
		searchPath.push_back(path);
	}

	FileUtils::getInstance()->setSearchPaths(searchPath);

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
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
