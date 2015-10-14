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
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    //添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, bgSprite);
    initUI();
    scheduleUpdate();
    
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
                
                //buyTarget->setPosition(pos);
                //检测是否可以创建商品
                moveCheck(pos, tag-SHOP_ITEM_LAYOUT_TAG);
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
                map->getLayer("goodsLayer")->setTileGID(9 + tag - SHOP_ITEM_LAYOUT_TAG, convertTotileCoord(endPos));
                canBuild = false;
            }
            else{
                // 得到放手时鼠标/手指的屏幕坐标，这个坐标是相对于地图的。所以计算它时应该要考虑到地图的移动和缩放。
                auto endPos =Vec2((widget->getTouchEndPosition().x - bgOrigin.x)/bgSprite->getScale(), (widget->getTouchEndPosition().y - bgOrigin.y)/bgSprite->getScale());
                // 把上面得到的屏幕坐标转换围地图坐标
                auto coord = convertTotileCoord( endPos);
                // 再把地图坐标转换为固定的一些屏幕坐标
                auto screenPos = this->convertToScreenCoord(coord);
                // 创建提醒项，把它设置在screenPos处
                auto tips = Sprite::create("tip.png");
                tips->setPosition(screenPos);
                bgSprite->addChild(tips);
                // 让提醒项出现一段时间后移除它
                tips->runAction(Sequence::create(DelayTime::create(1.0f),                                                CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),                                                NULL));
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
    auto seedPanel = this->getChildByTag(SEEDPANEL_TAG);
    if (seedPanel) {
        this->removeChild(seedPanel);
    }
    if (comeOut == true) {
        panel_shop->runAction(EaseElasticInOut::create(MoveBy::create(1, Vec2(-panel_shop->getContentSize().width/3*2, 0)), 0.5f));
        shop_btn->runAction(EaseElasticInOut::create(MoveBy::create(1, Vec2(-panel_shop->getContentSize().width/3*2, 0)), 0.5f));
        comeOut = false;
    }
    if(touches.size() == 1)
    {
        auto touch = touches[0];
        auto screenPos = touch->getLocation();
        auto mapSize = map->getMapSize();
        Vec2 pos;
        pos.x = (screenPos.x - bgOrigin.x) / bgSprite->getScale();
        pos.y = (screenPos.y - bgOrigin.y) / bgSprite->getScale();
        auto tilePos = this->convertTotileCoord(pos);
        if(tilePos.x >= 0 && tilePos.x <= mapSize.width-1 && tilePos.y >= 0 && tilePos.y <= mapSize.height-1)
        {
            int gid = map->getLayer("goodsLayer")->getTileGIDAt(tilePos);
            if (gid != 0) {
                switch (gid) {
                    case 9:
                        tileType = TileType::GROUD;
                        break;
                    case 18:
                    case 20:
                    case 22:
                        tileType = TileType::GROUD_CROP;
                        break;
                    case 19:
                    case 21:
                    case 23:
                        tileType = TileType::CROP_HARVEST;
                        break;
                    default:
                        tileType = TileType::OTHER;
                        break;
                }
                touchObjectPos = tilePos;
                map->getLayer("tipsLayer")->setTileGID(17, tilePos);
                this->schedule(schedule_selector(GameScene::updatePress),2);
                press = true;
            }
        }
    }
}

void GameScene::onTouchesMoved(const std::vector<Touch *> &touches, Event *event)
{
    auto winSize = Director::getInstance()->getWinSize();
    press = false;
    map->getLayer("tipsLayer")->removeTileAt(touchObjectPos);
    this->unschedule(schedule_selector(GameScene::updatePress));
    
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

void GameScene::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{
    this->unschedule(schedule_selector(GameScene::updatePress));
    
    Size winSize = Director::getInstance()->getWinSize();
    if (touches.size() == 1) {
        auto touch = touches[0];
        auto screenPos = touch->getLocation();
        if (press) {
            log("是短按");
            if (tileType == GROUD) {
                auto panel = SeedChooseLayer::create();
                panel->setPosition(screenPos);
                this->addChild(panel, 10, SEEDPANEL_TAG);
            }
            
            
            map->getLayer("tipsLayer")->removeTileAt(touchObjectPos);
            press = false;
        }
    }
}

Vec2 GameScene::convertTotileCoord(Vec2 position)
{
    auto mapSize = map->getMapSize();
    //计算当前缩放下，每块瓦片的长宽
    auto BBoxSize = map->getBoundingBox().size;
    auto tileWidth = map->getBoundingBox().size.width / map->getMapSize().width;
    auto tileHeight = map->getBoundingBox().size.height / map->getMapSize().height;
    //把position转换为瓦片坐标，确保得到的是整数
    //int posx = mapSize.height - position.y / tileHeight;
    int posx = mapSize.height - position.y / tileHeight + position.x / tileWidth - mapSize.width / 2;
    int posy = mapSize.height - position.y / tileHeight - position.x / tileWidth + mapSize.width / 2;
    
    return Point(posx, posy);
}

Vec2 GameScene::convertToScreenCoord(Vec2 position)
{
    auto mapSize = map->getMapSize();
    auto tileSize = map->getTileSize();
    auto BBoxSize = map->getBoundingBox().size;
    auto tileWidth = map->getBoundingBox().size.width / map->getMapSize().width;
    auto tileHeight = map->getBoundingBox().size.height / map->getMapSize().height;

    auto variable1 = (position.x + mapSize.width / 2 - mapSize.height) * tileHeight * tileWidth;
    auto variable2 = (-position.y + mapSize.width / 2 + mapSize.height) * tileWidth * tileHeight;
    
    int posx = (variable1 + variable2) / 2 / tileHeight;
    int posy = (variable2 - variable1) / 2 / tileWidth;
    
    return Point(posx, posy);
}

void GameScene::moveCheck(Vec2 position, int tag)
{
    auto mapSize = map->getMapSize();
    //将position转化为地图坐标
    auto tilePos = this->convertTotileCoord(position);
    
    //canBuild是用于判断是否可以生成瓦片的变量
    canBuild = false;
    perPos = currPos;
    
    //约束tilePos的范围，如果tilePos在正确地取值范围内
    if (tilePos.x >= 0 && tilePos.x <= mapSize.width - 1 && tilePos.y >=0 && tilePos.y <= mapSize.height - 1)
    {
        //前半段map->getLayer("2")是取得地图中名称为“2”的图层，而getTileGIDAt(tilePos)则是得到tilePos坐标上瓦片的GID标识（GID标识为0时，表示该处没有任何瓦片
        currPos = tilePos;
        int gid = map->getLayer("goodsLayer")->getTileGIDAt(tilePos);
        //该处没有其他障碍瓦片时
        if(gid == 0)
        {
            //设置拖动过程中正常的buyTarget纹理
            buyTarget->setTexture(move_textures[tag]);
            canBuild =true;
        }
        else{
            buyTarget->setTexture(move_textures_en[tag]);
            canBuild = false;
        }
        auto screenPos = this->convertToScreenCoord(tilePos);
        buyTarget->setPosition(screenPos);
        if(perPos != currPos)
        {
            map->getLayer("tipsLayer")->removeTileAt(perPos);
            map->getLayer("tipsLayer")->setTileGID(17, currPos);
        }
    }
    //如果地图外（四个角）
    else
    {
        buyTarget->setPosition(position);
        buyTarget->setTexture(move_textures_en[tag]);
        map->getLayer("tipsLayer")->removeTileAt(perPos);
        canBuild = false;
    }
}

void GameScene::updatePress(float t)
{
    this->unschedule(schedule_selector(GameScene::updatePress));
    if (press) {
        log("是长按");
        map->getLayer("tipsLayer")->removeTileAt(touchObjectPos);
        press = false;
    }
}

void GameScene::update(float dt)
{
    //通过标示得到场景中的子节点
    auto seedPanel = this->getChildByTag(SEEDPANEL_TAG);
    //判断瓦片是否为空土块，并且是否已经创建好了播种界面
    if (tileType == GROUD && seedPanel != NULL)
    {
        //得到选择的农作物类型
        auto type = ((SeedChooseLayer*)seedPanel)->getCurrType();
        //根据农作物类型种植相应的农作物
        switch (type) {
            case WHEAT:
                map->getLayer("goodsLayer")->setTileGID(18, touchObjectPos);
                this->removeChild(seedPanel);
                break;
            case CORN:
                map->getLayer("goodsLayer")->setTileGID(20, touchObjectPos);
                this->removeChild(seedPanel);
                break;
            case CARROT:
                map->getLayer("goodsLayer")->setTileGID(22, touchObjectPos);
                this->removeChild(seedPanel);
                break;
            default:
                break;
        }
    }
}
