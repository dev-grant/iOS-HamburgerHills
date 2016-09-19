//
//  HillsLayer.h
//  HamburgerHills
//
//  Created by Grant on 7/14/14.
//
//

#ifndef __HamburgerHills__HillsLayer__
#define __HamburgerHills__HillsLayer__

#include "RUBELayer.h"
#include "b2dJson.h"
#include "GameCharacter.h"
#include "TouchUpMenuItem.h"
#include "MenuItemCallBack.h"

struct ParticleData{
    cocos2d::CCParticleSystem *particleSystem;
    b2Body *attachedBody;
    b2Vec2 localPosition;
};


class HillsLayer : public RUBELayer, public MenuItemCallBack, public b2ContactListener{
protected:
    
    const char* m_levelName;
    int m_levelIndex;
    
    b2Body* m_spawnPoint;
    GameCharacter* m_character;
    
    cocos2d::CCParallaxNode *m_parallaxNode;
    
    float m_worldScale;
    
    bool m_controlEnabled = true;
    float m_gravity = -10.0f;
    
    bool m_timerStarted = false;
    int m_totalTime = 0;
    
    void showLevelEndMenu();
    
    cocos2d::CCMenu* m_HUDLayer;
    cocos2d::CCMenu* m_levelEndLayer;
    cocos2d::CCMenu* m_deathLayer;
public:
    static const char* LEVELNAMES[];
    
    static cocos2d::CCScene* scene(const char* levelName, int tag);
    
    virtual bool init(const char* levelName, int tag);
    
    virtual std::string getFilename();
    virtual cocos2d::CCPoint initialWorldOffset();
    virtual float initialWorldScale();
    
    virtual void afterLoadProcessing(b2dJson* json);
    virtual void clear();
    
    virtual void update(float dt);
    
    CCLayer* setupHUDLayer();
    virtual cocos2d::CCLayer* setupMenuLayer(); 
    CCLayer* setupLevelEndLayer();
    CCLayer* setupDeathLayer();
    
    virtual void menuSelected(ButtonMode m);
    virtual void menuUnselected(ButtonMode m);
    
    //virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void BeginContact(b2Contact *contact);
    //virtual void EndContact(b2Contact *contact);
    
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
    
    virtual void nextLevel();
    virtual void reloadLevel();
    
    virtual void updateTimerLabel();
};

#endif /* defined(__HamburgerHills__HillsLayer__) */
