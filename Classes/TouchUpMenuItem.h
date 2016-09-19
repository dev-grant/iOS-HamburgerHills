//
//  TouchUpMenuItem.h
//  HamburgerHills
//
//  Created by Grant on 7/25/14.
//
//

#ifndef __HamburgerHills__TouchUpMenuItem__
#define __HamburgerHills__TouchUpMenuItem__

#include "cocos2d.h"
#include "MenuItemCallBack.h"

class TouchUpMenuItem : public cocos2d::CCMenuItemSprite{
protected:
    MenuItemCallBack *m_delegate;
    ButtonMode m_mode;
public:
    TouchUpMenuItem(cocos2d::CCSprite *normal, cocos2d::CCSprite *selected, CCObject *target, cocos2d::SEL_MenuHandler selector, MenuItemCallBack *delegate, ButtonMode mode);
    void setDelegate(MenuItemCallBack *m);
    void selected();
    void unselected();
};

#endif /* defined(__HamburgerHills__TouchUpMenuItem__) */
