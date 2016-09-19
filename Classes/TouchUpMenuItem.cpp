//
//  TouchUpMenuItem.cpp
//  HamburgerHills
//
//  Created by Grant on 7/25/14.
//
//

#include "TouchUpMenuItem.h"

TouchUpMenuItem::TouchUpMenuItem(cocos2d::CCSprite *normal, cocos2d::CCSprite *selected, CCObject *target, cocos2d::SEL_MenuHandler selector, MenuItemCallBack *delegate, ButtonMode mode){
    this->initWithNormalSprite(normal, selected, normal, target, selector);
    this->setDelegate(delegate);
    m_mode = mode;
}

void TouchUpMenuItem::setDelegate(MenuItemCallBack *m){
    m_delegate = m;
}

void TouchUpMenuItem::selected(){
    if(m_delegate){
        m_delegate->menuSelected(m_mode);
    }
    CCMenuItemSprite::selected();
}

void TouchUpMenuItem::unselected(){
    if (m_delegate) {
        m_delegate->menuUnselected(m_mode);
    }
    CCMenuItemSprite::unselected();
}