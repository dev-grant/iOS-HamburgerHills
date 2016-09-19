//  Author: Chris Campbell - www.iforce2d.net
//  -----------------------------------------
//
//  only for this demo project, you can remove this in your own app
//

#ifndef EXAMPLES_MENU_LAYER
#define EXAMPLES_MENU_LAYER

#include "cocos2d.h"

class ExamplesMenuLayer : public cocos2d::CCLayer {
public:
    static cocos2d::CCScene* scene();
    virtual bool init();
    
    void loadLevel(CCObject* pSender);
};

#endif /* EXAMPLES_MENU_LAYER */
