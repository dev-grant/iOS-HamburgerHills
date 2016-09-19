//
//  MenuItemCallBack.h
//  HamburgerHills
//
//  Created by Grant on 7/26/14.
//
//

#ifndef __HamburgerHills__MenuItemCallBack__
#define __HamburgerHills__MenuItemCallBack__


enum ButtonMode {PLANK, ROLL};

class MenuItemCallBack{
public:
    virtual void menuSelected(ButtonMode m) = 0;
    virtual void menuUnselected(ButtonMode m) = 0;
};

#endif /* defined(__HamburgerHills__MenuItemCallBack__) */
