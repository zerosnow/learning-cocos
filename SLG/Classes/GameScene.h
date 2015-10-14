//
//  GameScene.h
//  SLG
//
//  Created by dengkai on 15/8/13.
//
//

#ifndef __SLG__GameScene__
#define __SLG__GameScene__

#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "SeedChooseLayer.h"
USING_NS_CC;
using namespace ui;

typedef enum{
    GROUD = 1,
    GROUD_CROP = 2,
    CROP_HARVEST,
    OTHER
}TileType;

class GameScene:public cocos2d::Layer
{
private:
    cocos2d::Layer* mapLayer;
    Sprite* bgSprite;
    Sprite* treeSprite;
    Sprite* buyTarget;
    Vec2 bgOrigin;
    Vec2 currPos;
    Vec2 perPos;
    
    Layout* playerLayout;
    Layout* panel_shop;
    Button* shop_btn;
    
    TMXTiledMap* map;
    
    bool comeOut;
    bool canBuild;
    TileType tileType;
    
    bool press;
    Vec2 touchObjectPos;
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    virtual void initUI();
    void menuShopCallback(Ref* pSender, Widget::TouchEventType type);
    void SpriteCallback(Ref* pSender, Widget::TouchEventType type);
    Vec2 convertTotileCoord(Vec2 position);
    Vec2 convertToScreenCoord(Vec2 position);
    void moveCheck(Vec2 position, int tag);
    void updatePress(float t);
    void update(float dt);
    
    CREATE_FUNC(GameScene);
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
};

#endif /* defined(__SLG__GameScene__) */
