//
//  GameScene.cpp
//  SLG
//
//  Created by dengkai on 15/8/13.
//
//

#include "GameScene.h"
#define SHOP_ITEM_LAYOUT_TAG    100
#define SEEDPANEL_TAG           888
#define HARVESTPANEL_TAG        889
#define REMOVEPANEL_TAG         890

const char* shop_textures[8] =
{
    "shopItem/Item1.png",
    "shopItem/Item2.png",
    "shopItem/Item3.png",
    "shopItem/Item4.png",
    "shopItem/Item5.png",
    "shopItem/Item6.png",
    "shopItem/Item1.png",
    "shopItem/Item2.png"
};

const char* move_textures[8] =
{
    "shopItem/moveItem1.png",
    "shopItem/moveItem2.png",
    "shopItem/moveItem3.png",
    "shopItem/moveItem4.png",
    "shopItem/moveItem5.png",
    "shopItem/moveItem6.png",
    "shopItem/moveItem1.png",
    "shopItem/moveItem2.png"
};

const char* move_textures_en[8] =
{
    "shopItem_en/Item1.png",
    "shopItem_en/Item2.png",
    "shopItem_en/Item3.png",
    "shopItem_en/Item4.png",
    "shopItem_en/Item5.png",
    "shopItem_en/Item6.png",
    "shopItem_en/Item1.png",
    "shopItem_en/Item2.png"
};

const char* shop_info[8] =
{
    "土地",
    "破树",
    "烂树",
    "烂草",
    "破屋",
    "破地",
    "婆婆",
    "破",
};

const int shop_money[8] =
{
    20,
    40,
    60,
    100,
    120,
    99,
    50,
    200,
};

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if( !Layer::init() )
    {
        return false;
    }
    mapLayer = LayerColor::create(Color4B(78,127,41,255));
    this->addChild(mapLayer, -1);
    
    bgSprite = Sprite::create("2.jpg");
    bgSprite->setAnchorPoint(Vec2::ZERO);
    bgSprite->setPosition(Vec2::ZERO);
    bgOrigin = Vec2::ZERO;
    mapLayer->addChild(bgSprite);
    
    treeSprite = Sprite::create("1.png");
    treeSprite->setAnchorPoint(Vec2::ZERO);
    treeSprite->setPosition(Vec2::ZERO);
    treeSprite->setScale(2);
    bgSprite->addChild(treeSprite, 2);
    
    map = TMXTiledMap::create("mymap8.tmx");
    map->setAnchorPoint(Vec2::ZERO);
    map->setPosition(Vec2::ZERO);
    bgSprite->addChild(map, 1);
    
    //创建一个事件监听器
    auto listener = EventListenerTouchAllAtOnce::create();
    //绑定触摸事件
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    //添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, bgSprite);
    initUI();
    
    return true;
}

void GameScene::initUI()
{
    playerLayout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Ui_3/Ui_1.json"));
    addChild(playerLayout);
    
    //获取商店层和购物车按钮
    panel_shop = dynamic_cast<Layout*>(playerLayout->getChildByName("panel_shop"));
    shop_btn = dynamic_cast<Button*>(playerLayout->getChildByName("button_shop"));
    //为购物车按钮绑定TouchEvent回调
    shop_btn->addTouchEventListener(CC_CALLBACK_2(GameScene::menuShopCallback, this));
    comeOut = false;
    
    auto shop_scrollView = dynamic_cast<ScrollView*>(panel_shop->getChildByName("scrollview_shop"));
    
    for (int i = 0; i < shop_scrollView->getChildren().size(); ++i)
    {
        Layout* shop_layout = static_cast<Layout*>(shop_scrollView->getChildren().at(i));
        shop_layout->setTag(SHOP_ITEM_LAYOUT_TAG + i);
        
        ImageView* buy_Sprite = static_cast<ImageView*>(shop_layout->getChildByName("shopitem"));
        buy_Sprite->loadTexture(shop_textures[i]);
        buy_Sprite->addTouchEventListener(CC_CALLBACK_2(GameScene::SpriteCallback, this));
        
        TextField* info = static_cast<TextField*>(shop_layout->getChildByName("info"));
        info->setText(shop_info[i]);
        
        TextField* money = static_cast<TextField*>(shop_layout->getChildByName("money_image")->getChildByName("money"));
        money->setText(std::to_string(shop_money[i]));
    }
    
}

void GameScene::menuShopCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    Size winSize = Director::getInstance()->getWinSize();
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            //为shop_btn添加一个缩放效果
            shop_btn->runAction(EaseElasticInOut::create(Sequence::create(ScaleBy::create(0.1f, 2), ScaleBy::create(0.2f, 0.5f), NULL), 0.5f));
            break;
            
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::ENDED:
            if (comeOut == false) {
                //为panel_shop和shop_btn添加一个弹性的移动效果，移动的距离是（panel_shop->getContentSize.width/3*2,0)个单位
                panel_shop->runAction(EaseElasticInOut::create(MoveBy::create(1, Vec2(panel_shop->getContentSize().width/3*2, 0)), 0.5f));
                shop_btn->runAction(EaseElasticInOut::create(MoveBy::create(1, Vec2(panel_shop->getContentSize().width/3*2, 0)), 0.5f));
                comeOut = true;
            }
            else if(comeOut == true)
            {
                panel_shop->runAction(EaseElasticInOut::create(MoveBy::create(1, Vec2(-panel_shop->getContentSize().width/3*2, 0)), 0.5f));
                shop_btn->runAction(EaseElasticInOut::create(MoveBy::create(1, Vec2(-panel_shop->getContentSize().width/3*2, 0)), 0.5f));
                comeOut = false;
            }
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
    }
}

void GameScene::SpriteCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    Size winSize = Director::getInstance()->getWinSize();
    //获得所选择的Widget,和它的父Widget（也是商品项）
    Widget* widget = static_cast<Widget*>(pSender);
    Widget* parent = static_cast<Widget*>(widget->getParent());
    //得到商品的标记
    int tag = parent->getTag();
    
    //根据TouchEventType类型进行逻辑处理
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            widget->runAction(EaseElasticInOut::create(ScaleTo::create(0.1f, 1.5), 0.2f));
            break;
        case Widget::TouchEventType::MOVED:
            if(comeOut == true)
            {
                panel_shop->runAction(EaseElasticInOut::create(MoveBy::create(1,Vec2(-panel_shop->getContentSize().width/3*2, 0)), 0.5f));
                shop_btn->runAction(EaseElasticInOut::create(MoveBy::create(1,Vec2(-panel_shop->getContentSize().width/3*2, 0)), 0.5f));
                comeOut = false;
            }
            if (buyTarget == NULL) {
                buyTarget = Sprite::create(move_textures[tag-SHOP_ITEM_LAYOUT_TAG]);
                buyTarget->setAnchorPoint(Vec2(0.5f, 0));
                bgSprite->addChild(buyTarget, 10);
            }
            else
            {
                Vec2 pos;
                pos.x = (widget->getTouchMovePosition().x - bgOrigin.x)/bgSprite->getScale();
                pos.y = (widget->getTouchMovePosition().y - bgOrigin.y)/bgSprite->getScale();
                
                buyTarget->setPosition(pos);
                //检测是否可以创建商品
                //moveCheck(pos, tag-SHOP_ITEM_LAYOUT_TAG);
            }
            break;
            
        //这里TouchEventType::ENDED在正常触摸完后，手指离开屏幕得时候触发，而TouchEventType::CANCELED则是在非正常触摸完结束时触发，比如手指没正常离开时候来了个电话，或者滑动过程中滑出了Widget范围抬起手指。
        case Widget::TouchEventType::ENDED:
            //还原放大的widget
            widget->runAction(EaseElasticInOut::create(ScaleTo::create(0.1f, 1), 0.2f));
            //移除buyTarget
            if(buyTarget!=NULL)
            {
                buyTarget->removeFromParent();
                buyTarget = NULL;
            }
            canBuild = false;
            break;
        case Widget::TouchEventType::CANCELED:
            //还原放大的widget
            widget->runAction(EaseElasticInOut::create(ScaleTo::create(0.1f, 1), 0.2f));
            //生成瓦片
            if (canBuild == true) {
                //得到放手的位置
                auto endPos = Vec2((widget->getTouchEndPosition().x - bgOrigin.x)/bgSprite->getScale(),(widget->getTouchEndPosition().y - bgOrigin.y)/bgSprite->getScale());
                map->getLayer("2")->setTileGID(9 + tag - SHOP_ITEM_LAYOUT_TAG, convertTotileCoord(endPos));
                canBuild = false;
            }
            //移除buyTarget
            if(buyTarget != NULL)
            {
                buyTarget->removeFromParent();
                buyTarget = NULL;
            }
            //弹出购物滚动面板
            if(comeOut == false)
            {
                panel_shop->runAction(EaseElasticInOut::create(MoveBy::create(1,Vec2(panel_shop->getContentSize().width/3*2, 0)), 0.5f));
                shop_btn->runAction(EaseElasticInOut::create(MoveBy::create(1,Vec2(panel_shop->getContentSize().width/3*2, 0)), 0.5f));
                comeOut = true;
            }
            break;
        default:
            break;
    }
}

void GameScene::onTouchesBegan(const std::vector<Touch *> &touches, Event *event)
{
    Size winSize = Director::getInstance()->getWinSize();
    if (comeOut == true) {
        panel_shop->runAction(EaseElasticInOut::create(MoveBy::create(1, Vec2(-panel_shop->getContentSize().width/3*2, 0)), 0.5f));
        shop_btn->runAction(EaseElasticInOut::create(MoveBy::create(1, Vec2(-panel_shop->getContentSize().width/3*2, 0)), 0.5f));
        comeOut = false;
    }
}
void GameScene::onTouchesMoved(const std::vector<Touch *> &touches, Event *event)
{
    auto winSize = Director::getInstance()->getWinSize();
    if(touches.size() > 1)         //多点触摸
    {
        //得到当前两触摸点
        auto point1 = touches[0]->getLocation();
        auto point2 = touches[1]->getLocation();
        //计算两点距离
        auto currDistance = point1.distance(point2);
        //计算两触摸点上一时刻间的距离
        auto prevDistance = touches[0]->getPreviousLocation().distance(touches[1]->getPreviousLocation());
        //两触摸点与原点的差向量，pointVec1和pointVec2相对于bgOrigin的位置
        auto pointVec1 = point1 - bgOrigin;
        auto pointVec2 = point2 - bgOrigin;
        //两触摸点的相对中点
        auto relMidx = (pointVec1.x + pointVec2.x) / 2;
        auto relMidy = (pointVec1.y + pointVec2.y) / 2;
        //计算bgSprite的锚点
        auto anchorX = relMidx / bgSprite->getBoundingBox().size.width;
        auto anchorY = relMidy / bgSprite->getBoundingBox().size.height;
        //相对屏幕的中点
        auto absMidx = (point1.x + point2.x);
        auto absMidy = (point1.y + point2.y);
        
        //缩放时，为了避免出现空白的区域，需要做以下边界处理
        //当bgSprite快要进入到屏幕时，修改bgSprite的位置，即absMidx和absMidy)
        if(bgOrigin.x > 0) {
            absMidx -= bgOrigin.x;
        }
        if(bgOrigin.x < -bgSprite->getBoundingBox().size.width + winSize.width) {
            absMidx +=-bgSprite->getBoundingBox().size.width + winSize.width;
        }
        if(bgOrigin.y > 0){
            absMidy -= bgOrigin.y;
        }
        if(bgOrigin.y < -bgSprite->getBoundingBox().size.height + winSize.height) {
            absMidy += -bgSprite->getBoundingBox().size.height + winSize.height;
        }
        //重设bgSprite锚点和位置
        bgSprite->setAnchorPoint(Vec2(anchorX, anchorY));
        bgSprite->setPosition(Vec2(absMidx, absMidy));
        //根据两触摸点前后的距离计算缩放倍率
        auto scale = bgSprite->getScale() * (currDistance / prevDistance);
        scale = MIN(4, MAX(1, scale));
        bgSprite->setScale(scale);
        //更新原点位置
        bgOrigin = Vec2(absMidx, absMidy) - Vec2(bgSprite->getBoundingBox().size.width * anchorX, bgSprite->getBoundingBox().size.height * anchorY);
    }
    else if(touches.size() == 1)
    {
        //单点时，touches中只有一个touch对象，所以通过touches[0]即可获得
        auto touch = touches[0];
        //计算滑动过程中的滑动增量
        auto diff = touch->getDelta();
        //得到当前bgSprite的位置
        auto currentPos = bgSprite->getPosition();
        //得到滑动后bgSprite应该所在的位置
        auto pos = currentPos + diff;
        //得到此刻bgSprite的尺寸
        auto bgSpriteCurrSize = bgSprite->getBoundingBox().size;
        
        //更新原点位置
        if(pos.x >= bgSpriteCurrSize.width * bgSprite->getAnchorPoint().x)
        {
            diff.x = -bgOrigin.x;
        }
        else if(pos.x <= bgSpriteCurrSize.width * (bgSprite->getAnchorPoint().x - 1) + winSize.width)
        {
            diff.x = -bgSpriteCurrSize.width + winSize.width - bgOrigin.x;
        }
        if(pos.y >= bgSpriteCurrSize.height * bgSprite->getAnchorPoint().y)
        {
            diff.y = -bgOrigin.y;
        }
        else if(pos.y <= bgSpriteCurrSize.height * (bgSprite->getAnchorPoint().y - 1) + winSize.height)
        {
            diff.y = -bgSpriteCurrSize.height + winSize.height - bgOrigin.y;
        }
        
        //边间控制，约束pos的位置
        pos = currentPos + diff;
        bgSprite->setPosition(pos);
        
        bgOrigin +=diff;
    }
}

Vec2 GameScene::convertTotileCoord(Vec2 position)
{
    auto mapSize = map->getMapSize();
    //计算当前缩放下，每块瓦片的长宽
    auto tileWidth = map->getBoundingBox().size.width / map->getMapSize().width;
    auto tileHeight = map->getBoundingBox().size.width / map->getMapSize().width;
    //把position转换为瓦片坐标，确保得到的是整数
    //int posx = mapSize.height - position.y / tileHeight;
    int posx = mapSize.height - position.y / tileHeight + position.x / tileWidth - mapSize.width / 2;
    int posy = mapSize.height - position.y / tileHeight - position.x / tileWidth + mapSize.width / 2;
    
    return Point(posx, posy);
}
