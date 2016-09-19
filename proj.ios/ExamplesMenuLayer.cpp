//  Author: Chris Campbell - www.iforce2d.net
//  -----------------------------------------
//
//  only for this demo project, you can remove this in your own app
//

#include "ExamplesMenuLayer.h"

#include "BasicRUBELayer.h"
#include "RUBELayer.h"
#include "HillsLayer.h"

using namespace cocos2d;

CCScene* ExamplesMenuLayer::scene()
{
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new ExamplesMenuLayer();
    layer->init();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

bool ExamplesMenuLayer::init()
{
	if ( CCLayer::init() ) {
        
        setTouchEnabled( true );
        
        CCMenuItem* level1Item = CCMenuItemFont::create("Level 1", this, menu_selector(ExamplesMenuLayer::loadLevel));
        level1Item->setTag(0);
        CCMenuItem* level2Item= CCMenuItemFont::create("Level 2", this, menu_selector(ExamplesMenuLayer::loadLevel));
        level2Item->setTag(1);
        CCMenuItem* level3Item= CCMenuItemFont::create("Fall Level", this, menu_selector(ExamplesMenuLayer::loadLevel));
        level3Item->setTag(2);
        
        CCMenu* menu = CCMenu::create(level1Item, level2Item, level3Item, NULL);
        menu->alignItemsVertically();
        addChild(menu);
        
	}
	return true;
}

void ExamplesMenuLayer::loadLevel(CCObject* pSender)
{
    CCMenuItem* pMenuItem = (CCMenuItem*)(pSender);
    int tag = (int)pMenuItem->getTag();
    
    const char* levelName;
    
    switch (tag){
        case 0:
            levelName = "testLevel1.json";
            break;
        case 1:
            levelName = "testLevel2.json";
            break;
        case 2:
            levelName = "fallTestLevel.json";
            break;
        default:
            break;
    }
    
    CCDirector::sharedDirector()->replaceScene( HillsLayer::scene(levelName, tag) );
}



