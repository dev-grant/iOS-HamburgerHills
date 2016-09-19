//
//  GameCharacter.h
//  HamburgerHills
//
//  Created by Grant on 7/24/14.
//
//

#ifndef __HamburgerHills__GameCharacter__
#define __HamburgerHills__GameCharacter__

#include "Box2d.h"
#include "cocos2d.h"
#include "RUBELayer.h"

enum BodyParts {FRONT_CALF, BACK_CALF, FRONT_FOREARM, FRONT_BICEP, FRONT_THIGH, TORSO, HEAD, BACK_BICEP, BACK_FOREARM, BACK_THIGH, ROTATE_BODY};

enum JointName {TORSO_HEAD, F_THIGH_CALF, B_THIGH_CALF, F_TORSO_LEG, B_TORSO_LEG, F_TORSO_BICEP, B_TORSO_BICEP, F_BICEP_FOREARM, B_BICEP_FOREARM, ROTATE_BODY_JOINT};

enum MotorMode {OFF_MOTOR, ROLL_MOTOR, PLANK_MOTOR};

class GameCharacter {
protected:
    b2World* m_world;
    RUBELayer* m_layer;
    
    b2Body** bodies = (b2Body**)b2Alloc(11 * sizeof(b2Body*));
    b2RevoluteJoint** joints = (b2RevoluteJoint**)b2Alloc(10 * sizeof(b2RevoluteJoint*));
    
    double rotationSpeed = 0;
    bool m_isAlive = true;
    
    int m_limbsLost = 0;
    
    cocos2d::CCSprite** sprites = (cocos2d::CCSprite**)b2Alloc(10 * sizeof(cocos2d::CCSprite*));
public:
    GameCharacter(b2Vec2 point, b2World* world, RUBELayer* layer);
    
    b2Body* getBody(BodyParts b);
    cocos2d::CCSprite* getSprite(BodyParts b);
    b2RevoluteJoint* getJoint(JointName j);
    
    void updateImagePositions();
    
    void startRolling();
    void stopRolling();
    
    void startPlanking();
    void stopPlanking();

    void runMotors();
    
    void clearSprites();
    
    void updateRotationSpeed(double x);
    
    bool jointIntact(JointName j);
    void setJointNull(JointName j);
    
    int indexOfBodyPart(b2Body* b);
    
    void setAlive(bool b);
    bool isAlive();

    int getNumLimbsLost();
    void incrementLimbsLostBy(int n);
    
private:
    void createPhysics(b2Vec2 point);
    void createSprites();
    
    MotorMode m_currentMode = OFF_MOTOR;

};

#endif /* defined(__HamburgerHills__GameCharacter__) */
