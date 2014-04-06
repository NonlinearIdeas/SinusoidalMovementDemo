#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
private:
   CCSprite* _sprite;      // weak reference.
   int _ticks;
   int _ticksTotal;
   
   void InitAnimation();
   void UpdateAnimation();
   
public:
   // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
   virtual bool init();
   
   // there's no 'id' in cpp, so we recommend to return the class instance pointer
   static cocos2d::CCScene* scene();
   
   // a selector callback
   void menuCloseCallback(CCObject* pSender);
   
   // Add overrides for starting/ending the scene.
   virtual void onEnterTransitionDidFinish();
   virtual void onExitTransitionDidStart();
   virtual void update(float dt);
   virtual void draw();
   
   // preprocessor macro for "static create()" constructor ( node() deprecated )
   CREATE_FUNC(HelloWorld);
   
};

#endif // __HELLOWORLD_SCENE_H__
