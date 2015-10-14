//
//  SeedChooseLayer.cpp
//  SLG
//
//  Created by dengkai on 15/8/18.
//
//

#include "SeedChooseLayer.h"

bool SeedChooseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    currType = CropsType::NOTHING;
    auto bgSprite = Sprite::create("chooseBg.png");
    bgSprite->setAnchorPoint(Vec2(1, 0));
    this->addChild(bgSprite);
    
    wheat = Sprite::create("wheat.png");
    wheat->setAnchorPoint(Point(0, 0));
    wheat->setAnchorPoint(Point(0,0));
    bgSprite->addChild(wheat);
    
    corn = Sprite::create("corn.png");
    corn->setPosition(Point(bgSprite->getContentSize().width/2, bgSprite->getContentSize().height/2));
    bgSprite->addChild(corn);
    
    carrot = Sprite::create("carrot.png");
    carrot->setAnchorPoint(Point(1, 1));
    carrot->setPosition(Point(bgSprite->getContentSize().width, bgSprite->getContentSize().height));
    bgSprite->addChild(carrot);
    
    //创建事件监听，OneByOne表示单点
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(SeedChooseLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, wheat);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), corn);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), carrot);
    return true;

}

bool SeedChooseLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Point locationInNode = target->convertTouchToNodeSpace(touch);
    Size size = target->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(locationInNode)) {
        target->setOpacity(180);
        if (target == wheat) {
            currType = CropsType::WHEAT;
        }else if(target == corn)
        {
            currType = CropsType::CORN;
        }else if(target == carrot)
        {
            currType = CropsType::CARROT;
        }else{
            currType = CropsType::NOTHING;
        }
        return true;
    }
    return false;
}
