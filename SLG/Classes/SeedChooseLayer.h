//
//  SeedChooseLayer.h
//  SLG
//
//  Created by dengkai on 15/8/18.
//
//

#ifndef __SLG__SeedChooseLayer__
#define __SLG__SeedChooseLayer__

USING_NS_CC;

typedef enum
{
    WHEAT = 0,
    CORN = 1,
    CARROT,
    NOTHING
}CropsType;

class SeedChooseLayer: public Layer
{
public:
    virtual bool init()override;
    bool onTouchBegan(Touch* touch, Event* event);
    CC_SYNTHESIZE(CropsType, currType, CurrType);    //选中的作物类型
    CREATE_FUNC(SeedChooseLayer);
private:
    Sprite* wheat;
    Sprite* corn;
    Sprite* carrot;
};
#endif /* defined(__SLG__SeedChooseLayer__) */
