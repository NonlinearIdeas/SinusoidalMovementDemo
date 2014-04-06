#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

// This assumes the frame rate is relatively constant
// at 60 fps.
const double SECONDS_PER_TICK = 1.0/60;
const double DURATION = 8.0;     // Seconds for total animation.
const double X_START = 100;      // Pixels
const double Y_START = 200;      // Pixels
const double X_STOP = 800;      // Pixels
const double X_SPEED = (X_STOP-X_START)/DURATION;
const double Y_PERIOD = 4.0;     // Seconds for y cycle.
const double Y_HEIGHT = 100;
const double LAUNCH_ANGLE = M_PI/4; // Angle for line.
const CCPoint ANCHOR(X_START,Y_START);

CCPoint RotatePointAboutAnchor(const CCPoint& pt,double theta,const CCPoint& anchor)
{
   double xPrime = cos(theta) * (pt.x-anchor.x) - sin(theta) * (pt.y-anchor.y) + anchor.x;
   double yPrime = sin(theta) * (pt.x-anchor.x) + cos(theta) * (pt.y-anchor.y) + anchor.y;
   
   return CCPoint(xPrime,yPrime);
}


void HelloWorld::InitAnimation()
{
   _ticks = 0;
   _ticksTotal = DURATION/SECONDS_PER_TICK;
}

void HelloWorld::UpdateAnimation()
{
   if(_ticks <= _ticksTotal)
   {
      double seconds = _ticks*SECONDS_PER_TICK;
      double xPos = X_START + seconds*X_SPEED;
      double yPos = Y_START + Y_HEIGHT*sin(seconds*2*M_PI/Y_PERIOD);
      CCPoint pos = RotatePointAboutAnchor(CCPoint(xPos,yPos), LAUNCH_ANGLE, ANCHOR);
      // Set the position of the sprite
      _sprite->setPosition(pos);
      
      CCLOG("Tick: %d, Seconds: %5.2f, Position: (%f,%f)",_ticks,seconds,pos.x,pos.y);
      if(_ticks%10 == 0)
      {  // Add a trail
         CCSprite* marker = CCSprite::create("Icon-72.png");
         marker->setScale(0.1);
         marker->setPosition(_sprite->getPosition());
         marker->setZOrder(50);
         addChild(marker);
      }
      // Increment the ticks count for next time.
      _ticks++;
   }
}

void HelloWorld::draw()
{
   CCLayer::draw();
   CCPoint start;
   CCPoint stop;
   
   start = RotatePointAboutAnchor(CCPoint(X_START,Y_START), LAUNCH_ANGLE, ANCHOR);
   stop = RotatePointAboutAnchor(CCPoint(X_STOP,Y_START), LAUNCH_ANGLE, ANCHOR);
   ccDrawLine(start,stop);
   
   start = RotatePointAboutAnchor(CCPoint(X_START,Y_START+Y_HEIGHT), LAUNCH_ANGLE, ANCHOR);
   stop = RotatePointAboutAnchor(CCPoint(X_STOP,Y_START+Y_HEIGHT), LAUNCH_ANGLE, ANCHOR);
   ccDrawLine(start,stop);

   start = RotatePointAboutAnchor(CCPoint(X_START,Y_START-Y_HEIGHT), LAUNCH_ANGLE, ANCHOR);
   stop = RotatePointAboutAnchor(CCPoint(X_STOP,Y_START-Y_HEIGHT), LAUNCH_ANGLE, ANCHOR);
   ccDrawLine(start,stop);
}

void HelloWorld::onEnterTransitionDidFinish()
{
   InitAnimation();
   scheduleUpdate();
}

void HelloWorld::onExitTransitionDidStart()
{
   unscheduleUpdate();
}

void HelloWorld::update(float dt)
{
   UpdateAnimation();
}


CCScene* HelloWorld::scene()
{
   // 'scene' is an autorelease object
   CCScene *scene = CCScene::create();
   
   // 'layer' is an autorelease object
   HelloWorld *layer = HelloWorld::create();
   
   // add layer as a child to scene
   scene->addChild(layer);

   
   // return the scene
   return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
   //////////////////////////////
   // 1. super init first
   if ( !CCLayer::init() )
   {
      return false;
   }
   
   /////////////////////////////
   // 2. add a menu item with "X" image, which is clicked to quit the program
   //    you may modify it.
   
   // add a "close" icon to exit the progress. it's an autorelease object
   CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                         "CloseNormal.png",
                                                         "CloseSelected.png",
                                                         this,
                                                         menu_selector(HelloWorld::menuCloseCallback) );
   pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
   
   // create menu, it's an autorelease object
   CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
   pMenu->setPosition( CCPointZero );
   this->addChild(pMenu, 1);
   
   /////////////////////////////
   // 3. add your codes below...
   
   // add a label shows "Hello World"
   // create and initialize a label
   CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
   
   // ask director the window size
   CCSize size = CCDirector::sharedDirector()->getWinSize();
   
   // position the label on the center of the screen
   pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
   
   // add the label as a child to this layer
   this->addChild(pLabel, 1);
   
   
   // Add a sprite to move around
   _sprite = CCSprite::create("Icon-72.png");
   _sprite->setScale(0.5);
   _sprite->setZOrder(100);
   this->addChild(_sprite);
   
   return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
   CCDirector::sharedDirector()->end();
   
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
   exit(0);
#endif
}
