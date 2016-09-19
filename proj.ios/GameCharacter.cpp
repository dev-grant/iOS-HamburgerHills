//
//  GameCharacter.cpp
//  HamburgerHills
//
//  Created by Grant on 7/24/14.
//
//

#include "GameCharacter.h"
#include "PositionConstants.h"

using namespace cocos2d;

void GameCharacter::setAlive(bool b){
    m_isAlive = b;
}

bool GameCharacter::isAlive(){
    return m_isAlive;
}

b2Body* GameCharacter::getBody(BodyParts b){
    return bodies[b];
}

CCSprite* GameCharacter::getSprite(BodyParts b){
    return sprites[b];
}

b2RevoluteJoint* GameCharacter::getJoint(JointName j){
    return joints[j];
}

void GameCharacter::setJointNull(JointName j){
    joints[j] = NULL;
}

bool GameCharacter::jointIntact(JointName j){
    if (joints[j] != NULL) {
        return true;
    }
    return false;
}

int GameCharacter::getNumLimbsLost(){
    return m_limbsLost;
}

void GameCharacter::incrementLimbsLostBy(int n){
    m_limbsLost += n;
}

int GameCharacter::indexOfBodyPart(b2Body *b){
    for (int i = 0; i < 10; i++) {
        if (bodies[i] == b) {
            return i;
        }
    }
    return -1;
}

GameCharacter::GameCharacter(b2Vec2 point, b2World* world, RUBELayer* layer){

    m_world = world;
    m_layer = layer;
    
    createPhysics(point);
    createSprites();
}

void GameCharacter::startRolling(){
    for (int i = 1; i < 9; i++){
        JointName j = static_cast<JointName>(i);
        if (jointIntact(j))
            joints[i]->EnableMotor(true);
    }
    m_currentMode = ROLL_MOTOR;
}

void GameCharacter::stopRolling(){
    for (int i = 1; i < 9; i++){
        JointName j = static_cast<JointName>(i);
        if (jointIntact(j))
            joints[i]->EnableMotor(false);
    }
    m_currentMode = OFF_MOTOR;
}

void GameCharacter::startPlanking(){
    for (int i = 1; i < 9; i++){
        JointName j = static_cast<JointName>(i);
        if (jointIntact(j))
            joints[i]->EnableMotor(true);
    }
    m_currentMode = PLANK_MOTOR;
}

void GameCharacter::stopPlanking(){
    for (int i = 1; i < 9; i++){
        JointName j = static_cast<JointName>(i);
        if (jointIntact(j))
            joints[i]->EnableMotor(false);
    }
    m_currentMode = OFF_MOTOR;
}

void GameCharacter::updateRotationSpeed(double x){
    if (m_isAlive) {
        rotationSpeed = x * 12.0f;
    }
    
}

void GameCharacter::runMotors(){
    if (m_isAlive) {
        switch (m_currentMode) {
            case OFF_MOTOR:
                break;
            case ROLL_MOTOR:
                if (jointIntact(F_TORSO_BICEP))
                    joints[F_TORSO_BICEP]->SetMotorSpeed(-5.0f * (joints[F_TORSO_BICEP]->GetJointAngle() - CC_DEGREES_TO_RADIANS(ROLL_BICEP_ANGLE)));
                if (jointIntact(B_TORSO_BICEP))
                    joints[B_TORSO_BICEP]->SetMotorSpeed(-5.0f * (joints[B_TORSO_BICEP]->GetJointAngle() - CC_DEGREES_TO_RADIANS(ROLL_BICEP_ANGLE)));
                
                if (jointIntact(F_BICEP_FOREARM))
                    joints[F_BICEP_FOREARM]->SetMotorSpeed(-5.0f * (joints[F_BICEP_FOREARM]->GetJointAngle() - CC_DEGREES_TO_RADIANS(ROLL_FOREARM_ANGLE)));
                if(jointIntact(B_BICEP_FOREARM))
                    joints[B_BICEP_FOREARM]->SetMotorSpeed(-5.0f * (joints[B_BICEP_FOREARM]->GetJointAngle() - CC_DEGREES_TO_RADIANS(ROLL_FOREARM_ANGLE)));
                
                if (jointIntact(F_TORSO_LEG))
                    joints[F_TORSO_LEG]->SetMotorSpeed(-5.0f * (joints[F_TORSO_LEG]->GetJointAngle() - CC_DEGREES_TO_RADIANS(ROLL_THIGH_ANGLE)));
                if (jointIntact(B_TORSO_LEG))
                    joints[B_TORSO_LEG]->SetMotorSpeed(-5.0f * (joints[B_TORSO_LEG]->GetJointAngle() - CC_DEGREES_TO_RADIANS(ROLL_THIGH_ANGLE)));
                
                if (jointIntact(F_THIGH_CALF))
                    joints[F_THIGH_CALF]->SetMotorSpeed(-5.0f * (joints[F_THIGH_CALF]->GetJointAngle() - CC_DEGREES_TO_RADIANS(ROLL_CALF_ANGLE)));
                if (jointIntact(B_THIGH_CALF))
                    joints[B_THIGH_CALF]->SetMotorSpeed(-5.0f * (joints[B_THIGH_CALF]->GetJointAngle() - CC_DEGREES_TO_RADIANS(ROLL_CALF_ANGLE)));
                break;
            case PLANK_MOTOR:
                
                if (jointIntact(F_TORSO_BICEP))
                    joints[F_TORSO_BICEP]->SetMotorSpeed(-5.0f * (joints[F_TORSO_BICEP]->GetJointAngle() - CC_DEGREES_TO_RADIANS(PLANK_BICEP_ANGLE)));
                if (jointIntact(B_TORSO_BICEP))
                    joints[B_TORSO_BICEP]->SetMotorSpeed(-5.0f * (joints[B_TORSO_BICEP]->GetJointAngle() - CC_DEGREES_TO_RADIANS(PLANK_BICEP_ANGLE)));
                
                if (jointIntact(F_BICEP_FOREARM))
                    joints[F_BICEP_FOREARM]->SetMotorSpeed(-5.0f * (joints[F_BICEP_FOREARM]->GetJointAngle() - CC_DEGREES_TO_RADIANS(PLANK_FOREARM_ANGLE)));
                if (jointIntact(B_BICEP_FOREARM))
                    joints[B_BICEP_FOREARM]->SetMotorSpeed(-5.0f * (joints[B_BICEP_FOREARM]->GetJointAngle() - CC_DEGREES_TO_RADIANS(PLANK_FOREARM_ANGLE)));
                
                if (jointIntact(F_TORSO_LEG))
                    joints[F_TORSO_LEG]->SetMotorSpeed(-5.0f * (joints[F_TORSO_LEG]->GetJointAngle() - CC_DEGREES_TO_RADIANS(PLANK_THIGH_ANGLE)));
                if (jointIntact(B_TORSO_LEG))
                    joints[B_TORSO_LEG]->SetMotorSpeed(-5.0f * (joints[B_TORSO_LEG]->GetJointAngle() - CC_DEGREES_TO_RADIANS(PLANK_THIGH_ANGLE)));
                
                if (jointIntact(F_THIGH_CALF))
                    joints[F_THIGH_CALF]->SetMotorSpeed(-5.0f * (joints[F_THIGH_CALF]->GetJointAngle() - CC_DEGREES_TO_RADIANS(PLANK_CALF_ANGLE)));
                if (jointIntact(B_THIGH_CALF))
                    joints[B_THIGH_CALF]->SetMotorSpeed(-5.0f * (joints[B_THIGH_CALF]->GetJointAngle() - CC_DEGREES_TO_RADIANS(PLANK_CALF_ANGLE)));
                break;
            default:
                break;
        }
        
        joints[ROTATE_BODY_JOINT]->SetMotorSpeed(rotationSpeed);
    }
    
}

void GameCharacter::createPhysics(b2Vec2 point){
    float x = point.x;
    float y = point.y;
    
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(9.253284335136414e-002f+x, -1.662271857261658e+000f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(0);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[FRONT_CALF] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(1.790229827165604e-001f, -2.692620754241943e-001f);
            vs[1].Set(1.668579578399658e-001f, -2.105491757392883e-001f);
            vs[2].Set(-4.812584817409515e-002f, -9.011107683181763e-002f);
            vs[3].Set(-1.730533540248871e-001f, -8.848482370376587e-002f);
            vs[4].Set(-1.662510335445404e-001f, -2.777586579322815e-001f);
            shape.Set(vs, 5);
            
            fd.shape = &shape;
            
            bodies[FRONT_CALF]->CreateFixture(&fd);
        }
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(3.319002687931061e-002f, 2.543692290782928e-001f);
            vs[1].Set(-1.600427925586700e-001f, 2.592481672763824e-001f);
            vs[2].Set(-1.730533540248871e-001f, -8.848482370376587e-002f);
            vs[3].Set(-4.812584817409515e-002f, -9.011107683181763e-002f);
            shape.Set(vs, 4);
            
            fd.shape = &shape;
            
            bodies[FRONT_CALF]->CreateFixture(&fd);
        }
    }
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(9.253284335136414e-002f+x, -1.662271857261658e+000f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(0);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[BACK_CALF] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(1.790229827165604e-001f, -2.692620754241943e-001f);
            vs[1].Set(1.668579578399658e-001f, -2.105491757392883e-001f);
            vs[2].Set(-4.812584817409515e-002f, -9.011107683181763e-002f);
            vs[3].Set(-1.730533540248871e-001f, -8.848482370376587e-002f);
            vs[4].Set(-1.662510335445404e-001f, -2.777586579322815e-001f);
            shape.Set(vs, 5);
            
            fd.shape = &shape;
            
            bodies[BACK_CALF]->CreateFixture(&fd);
        }
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(3.319002687931061e-002f, 2.543692290782928e-001f);
            vs[1].Set(-1.600427925586700e-001f, 2.592481672763824e-001f);
            vs[2].Set(-1.730533540248871e-001f, -8.848482370376587e-002f);
            vs[3].Set(-4.812584817409515e-002f, -9.011107683181763e-002f);
            shape.Set(vs, 4);
            
            fd.shape = &shape;
            
            bodies[BACK_CALF]->CreateFixture(&fd);
        }
    }
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(-5.208316445350647e-002f+x, -8.480596542358398e-001f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(0);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[FRONT_FOREARM] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(1.371554434299469e-001f, -1.794202029705048e-001f);
            vs[1].Set(3.190368413925171e-002f, -1.987915635108948e-001f);
            vs[2].Set(2.942012250423431e-002f, -2.699276804924011e-001f);
            vs[3].Set(6.073211133480072e-002f, -2.801545262336731e-001f);
            shape.Set(vs, 4);
            
            fd.shape = &shape;
            
            bodies[FRONT_FOREARM]->CreateFixture(&fd);
        }
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(1.371554434299469e-001f, -1.794202029705048e-001f);
            vs[1].Set(4.382073879241943e-002f, 2.357732057571411e-001f);
            vs[2].Set(-5.893544480204582e-002f, 2.890843152999878e-001f);
            vs[3].Set(-1.318722963333130e-001f, 2.252070307731628e-001f);
            vs[4].Set(3.190368413925171e-002f, -1.987915635108948e-001f);
            shape.Set(vs, 5);
            
            fd.shape = &shape;
            
            bodies[FRONT_FOREARM]->CreateFixture(&fd);
        }
    }
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(-8.226016163825989e-002f+x, -4.547698795795441e-001f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(0);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[FRONT_BICEP] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(1.223441362380981e-001f, 1.751750707626343e-001f);
            vs[1].Set(-9.240657091140747e-002f, 1.786971688270569e-001f);
            vs[2].Set(-1.100168824195862e-001f, -1.663699150085449e-001f);
            vs[3].Set(6.246903911232948e-002f, -1.769360899925232e-001f);
            shape.Set(vs, 4);
            
            fd.shape = &shape;
            
            bodies[FRONT_BICEP]->CreateFixture(&fd);
        }
    }
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(1.670083403587341e-002f+x, -1.208782792091370e+000f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(0);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[FRONT_THIGH] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(1.848269999027252e-001f, 1.868344843387604e-001f);
            vs[1].Set(-3.037229180335999e-005f, 2.759542465209961e-001f);
            vs[2].Set(-1.907905936241150e-001f, 1.937648653984070e-001f);
            vs[3].Set(-1.222442984580994e-001f, -1.337327361106873e-001f);
            vs[4].Set(-6.434965133666992e-002f, -2.633007168769836e-001f);
            vs[5].Set(7.434220612049103e-002f, -2.667407095432281e-001f);
            vs[6].Set(1.557522565126419e-001f, -1.184147894382477e-001f);
            shape.Set(vs, 7);
            
            fd.shape = &shape;
            
            bodies[FRONT_THIGH]->CreateFixture(&fd);
        }
    }
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(6.234782934188843e-002f+x, -6.227128505706787e-001f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(0);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[TORSO] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2CircleShape shape;
            shape.m_radius = 3.353032767772675e-001f;
            shape.m_p.Set(-2.710729092359543e-002f, -1.707344353199005e-001f);
            
            fd.shape = &shape;
            
            bodies[TORSO]->CreateFixture(&fd);
        }
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(2.633318305015564e-001f, 1.636695861816406e-002f);
            vs[1].Set(-2.558779716491699e-002f, 4.600430727005005e-001f);
            vs[2].Set(-2.479637265205383e-001f, 4.784846901893616e-001f);
            vs[3].Set(-3.309513330459595e-001f, -1.744279265403748e-002f);
            shape.Set(vs, 4);
            
            fd.shape = &shape;
            
            bodies[TORSO]->CreateFixture(&fd);
        }
    }

    
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(-1.212817430496216e-002f+x, -2.951889485120773e-002f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(0);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[HEAD] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2CircleShape shape;
            shape.m_radius = 1.633377969264984e-001f;
            shape.m_p.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
            
            fd.shape = &shape;
            
            bodies[HEAD]->CreateFixture(&fd);
        }
    }
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(-8.226016163825989e-002f+x, -4.547698795795441e-001f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(0);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[BACK_BICEP] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(1.223441362380981e-001f, 1.751750707626343e-001f);
            vs[1].Set(-9.240657091140747e-002f, 1.786971688270569e-001f);
            vs[2].Set(-1.100168824195862e-001f, -1.663699150085449e-001f);
            vs[3].Set(6.246903911232948e-002f, -1.769360899925232e-001f);
            shape.Set(vs, 4);
            
            fd.shape = &shape;
            
            bodies[BACK_BICEP]->CreateFixture(&fd);
        }
    }
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(-5.208316445350647e-002f+x, -8.480596542358398e-001f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(0);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[BACK_FOREARM] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(1.371554434299469e-001f, -1.794202029705048e-001f);
            vs[1].Set(4.382073879241943e-002f, 2.357732057571411e-001f);
            vs[2].Set(-5.893544480204582e-002f, 2.890843152999878e-001f);
            vs[3].Set(-1.318722963333130e-001f, 2.252070307731628e-001f);
            vs[4].Set(3.190368413925171e-002f, -1.987915635108948e-001f);
            shape.Set(vs, 5);
            
            fd.shape = &shape;
            
            bodies[BACK_FOREARM]->CreateFixture(&fd);
        }
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(1.371554434299469e-001f, -1.794202029705048e-001f);
            vs[1].Set(3.190368413925171e-002f, -1.987915635108948e-001f);
            vs[2].Set(2.942012250423431e-002f, -2.699276804924011e-001f);
            vs[3].Set(6.073211133480072e-002f, -2.801545262336731e-001f);
            shape.Set(vs, 4);
            
            fd.shape = &shape;
            
            bodies[BACK_FOREARM]->CreateFixture(&fd);
        }
    }
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(1.670083403587341e-002f+x, -1.208782792091370e+000f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(0);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[BACK_THIGH] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(2);
            fd.filter.maskBits = uint16(65533);
            fd.filter.groupIndex = int16(0);
            b2PolygonShape shape;
            b2Vec2 vs[8];
            vs[0].Set(1.848269999027252e-001f, 1.868344843387604e-001f);
            vs[1].Set(-3.037229180335999e-005f, 2.759542465209961e-001f);
            vs[2].Set(-1.907905936241150e-001f, 1.937648653984070e-001f);
            vs[3].Set(-1.222442984580994e-001f, -1.337327361106873e-001f);
            vs[4].Set(-6.434965133666992e-002f, -2.633007168769836e-001f);
            vs[5].Set(7.434220612049103e-002f, -2.667407095432281e-001f);
            vs[6].Set(1.557522565126419e-001f, -1.184147894382477e-001f);
            shape.Set(vs, 7);
            
            fd.shape = &shape;
            
            bodies[BACK_THIGH]->CreateFixture(&fd);
        }
    }
    
    {
        b2BodyDef bd;
        bd.type = b2BodyType(2);
        bd.position.Set(6.234782934188843e-002f+x, -6.227128505706787e-001f+y);
        bd.angle = 0.000000000000000e+000f;
        bd.linearVelocity.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        bd.angularVelocity = 0.000000000000000e+000f;
        bd.linearDamping = 0.000000000000000e+000f;
        bd.angularDamping = 0.000000000000000e+000f;
        bd.allowSleep = bool(4);
        bd.awake = bool(2);
        bd.fixedRotation = bool(16);
        bd.bullet = bool(0);
        bd.active = bool(32);
        bd.gravityScale = 1.000000000000000e+000f;
        bodies[ROTATE_BODY] = m_world->CreateBody(&bd);
        
        {
            b2FixtureDef fd;
            fd.friction = 2.000000029802322e-001f;
            fd.restitution = 0.000000000000000e+000f;
            fd.density = 1.000000000000000e+000f;
            fd.isSensor = bool(0);
            fd.filter.categoryBits = uint16(0);
            fd.filter.maskBits = uint16(0);
            fd.filter.groupIndex = int16(0);
            b2CircleShape shape;
            shape.m_radius = 5.000000000000000e-001f;
            shape.m_p.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
            
            fd.shape = &shape;
            
            bodies[ROTATE_BODY]->CreateFixture(&fd);
        }
    }
    
    {
        b2RevoluteJointDef jd;
        jd.bodyA = bodies[TORSO];
        jd.bodyB = bodies[HEAD];
        jd.collideConnected = bool(0);
        jd.localAnchorA.Set(-1.053650081157684e-001f, 4.352859854698181e-001f);
        jd.localAnchorB.Set(-3.088888525962830e-002f, -1.579079627990723e-001f);
        jd.referenceAngle = 0.000000000000000e+000f;
        jd.enableLimit = bool(1);
        jd.lowerAngle = -3.490658402442932e-001f;
        jd.upperAngle = 5.235987901687622e-001f;
        jd.enableMotor = bool(0);
        jd.motorSpeed = 0.000000000000000e+000f;
        jd.maxMotorTorque = 100;
        joints[TORSO_HEAD] = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
    }
    {
        b2RevoluteJointDef jd;
        jd.bodyA = bodies[TORSO];
        jd.bodyB = bodies[BACK_THIGH];
        jd.collideConnected = bool(0);
        jd.localAnchorA.Set(-4.527708888053894e-002f, -4.459080100059509e-001f);
        jd.localAnchorB.Set(3.697276115417480e-004f, 1.401620060205460e-001f);
        jd.referenceAngle = 0.000000000000000e+000f;
        jd.enableLimit = bool(1);
        jd.lowerAngle = -5.235987901687622e-001f;
        jd.upperAngle = 2.094395160675049e+000f;
        jd.enableMotor = bool(0);
        jd.motorSpeed = 0.000000000000000e+000f;
        jd.maxMotorTorque = 100;
        joints[B_TORSO_LEG] = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
    }
    {
        b2RevoluteJointDef jd;
        jd.bodyA = bodies[BACK_THIGH];
        jd.bodyB = bodies[BACK_CALF];
        jd.collideConnected = bool(0);
        jd.localAnchorA.Set(4.567831754684448e-003f, -2.271620035171509e-001f);
        jd.localAnchorB.Set(-7.126411795616150e-002f, 2.263270020484924e-001f);
        jd.referenceAngle = 0.000000000000000e+000f;
        jd.enableLimit = bool(1);
        jd.lowerAngle = -2.268928050994873e+000f;
        jd.upperAngle = 0.000000000000000e+000f;
        jd.enableMotor = bool(0);
        jd.motorSpeed = 0.000000000000000e+000f;
        jd.maxMotorTorque = 100;
        joints[B_THIGH_CALF] = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
    }
    {
        b2RevoluteJointDef jd;
        jd.bodyA = bodies[TORSO];
        jd.bodyB = bodies[BACK_BICEP];
        jd.collideConnected = bool(0);
        jd.localAnchorA.Set(-1.381889879703522e-001f, 2.425720095634460e-001f);
        jd.localAnchorB.Set(6.419420242309570e-003f, 7.462877035140991e-002f);
        jd.referenceAngle = 0.000000000000000e+000f;
        jd.enableLimit = bool(1);
        jd.lowerAngle = -6.981316804885864e-001f;
        jd.upperAngle = 3.316125631332397e+000f;
        jd.enableMotor = bool(0);
        jd.motorSpeed = 0.000000000000000e+000f;
        jd.maxMotorTorque = 100;
        joints[B_TORSO_BICEP] = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
    }
    {
        b2RevoluteJointDef jd;
        jd.bodyA = bodies[BACK_BICEP];
        jd.bodyB = bodies[BACK_FOREARM];
        jd.collideConnected = bool(0);
        jd.localAnchorA.Set(-1.380270719528198e-002f, -1.466169953346252e-001f);
        jd.localAnchorB.Set(-4.397958517074585e-002f, 2.466729879379272e-001f);
        jd.referenceAngle = 0.000000000000000e+000f;
        jd.enableLimit = bool(1);
        jd.lowerAngle = 0.000000000000000e+000f;
        jd.upperAngle = 1.221730470657349e+000f;
        jd.enableMotor = bool(0);
        jd.motorSpeed = 0.000000000000000e+000f;
        jd.maxMotorTorque = 100;
        joints[B_BICEP_FOREARM] = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
    }
    {
        b2RevoluteJointDef jd;
        jd.bodyA = bodies[5];
        jd.bodyB = bodies[4];
        jd.collideConnected = bool(0);
        jd.localAnchorA.Set(-4.527708888053894e-002f, -4.459080100059509e-001f);
        jd.localAnchorB.Set(3.697276115417480e-004f, 1.401620060205460e-001f);
        jd.referenceAngle = 0.000000000000000e+000f;
        jd.enableLimit = bool(1);
        jd.lowerAngle = -5.235987901687622e-001f;
        jd.upperAngle = 2.094395160675049e+000f;
        jd.enableMotor = bool(0);
        jd.motorSpeed = 0.000000000000000e+000f;
        jd.maxMotorTorque = 100;
        joints[F_TORSO_LEG] = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
    }
    {
        b2RevoluteJointDef jd;
        jd.bodyA = bodies[TORSO];
        jd.bodyB = bodies[FRONT_BICEP];
        jd.collideConnected = bool(0);
        jd.localAnchorA.Set(-1.381889879703522e-001f, 2.425720095634460e-001f);
        jd.localAnchorB.Set(6.419420242309570e-003f, 7.462882995605469e-002f);
        jd.referenceAngle = 0.000000000000000e+000f;
        jd.enableLimit = bool(1);
        jd.lowerAngle = -6.981316804885864e-001f;
        jd.upperAngle = 3.316125631332397e+000f;
        jd.enableMotor = bool(0);
        jd.motorSpeed = 0.000000000000000e+000f;
        jd.maxMotorTorque = 100;
        joints[F_TORSO_BICEP] = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
    }
    {
        b2RevoluteJointDef jd;
        jd.bodyA = bodies[FRONT_BICEP];
        jd.bodyB = bodies[FRONT_FOREARM];
        jd.collideConnected = bool(0);
        jd.localAnchorA.Set(-1.380270719528198e-002f, -1.466169953346252e-001f);
        jd.localAnchorB.Set(-4.397958517074585e-002f, 2.466730028390884e-001f);
        jd.referenceAngle = 0.000000000000000e+000f;
        jd.enableLimit = bool(1);
        jd.lowerAngle = 0.000000000000000e+000f;
        jd.upperAngle = 1.221730470657349e+000f;
        jd.enableMotor = bool(0);
        jd.motorSpeed = 0.000000000000000e+000f;
        jd.maxMotorTorque = 100;
        joints[F_BICEP_FOREARM] = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
    }
    {
        b2RevoluteJointDef jd;
        jd.bodyA = bodies[FRONT_THIGH];
        jd.bodyB = bodies[FRONT_CALF];
        jd.collideConnected = bool(0);
        jd.localAnchorA.Set(4.567831754684448e-003f, -2.271620035171509e-001f);
        jd.localAnchorB.Set(-7.126411795616150e-002f, 2.263270020484924e-001f);
        jd.referenceAngle = 0.000000000000000e+000f;
        jd.enableLimit = bool(1);
        jd.lowerAngle = -2.268928050994873e+000f;
        jd.upperAngle = 0.000000000000000e+000f;
        jd.enableMotor = bool(0);
        jd.motorSpeed = 0.000000000000000e+000f;
        jd.maxMotorTorque = 10000.0f;
        joints[F_THIGH_CALF] = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
    }
    
    {
        b2RevoluteJointDef jd;
        jd.bodyA = bodies[TORSO];
        jd.bodyB = bodies[ROTATE_BODY];
        jd.collideConnected = bool(0);
        jd.localAnchorA.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        jd.localAnchorB.Set(0.000000000000000e+000f, 0.000000000000000e+000f);
        jd.referenceAngle = 0.000000000000000e+000f;
        jd.enableLimit = bool(0);
        jd.lowerAngle = 0.000000000000000e+000f;
        jd.upperAngle = 0.000000000000000e+000f;
        jd.enableMotor = bool(1);
        jd.motorSpeed = 0.000000000000000e+000f;
        jd.maxMotorTorque = 10;
        joints[ROTATE_BODY_JOINT] = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
    }
}

void GameCharacter::createSprites(){
    
    {
        CCSprite* headSprite = new CCSprite();
        headSprite->initWithFile("sd_head.png");
        
        m_layer->addChild(headSprite);
        m_layer->reorderChild(headSprite, 0);

        headSprite->setScale(.33 / headSprite->getContentSize().height);
        
        sprites[HEAD] = headSprite;
        bodies[HEAD]->SetUserData(headSprite);
        
    }
    {
        CCSprite* torsoSprite = new CCSprite();
        torsoSprite->initWithFile("sd_torso.png");
        
        m_layer->addChild(torsoSprite);
        m_layer->reorderChild(torsoSprite, 1);
        
        torsoSprite->setScale(1 / torsoSprite->getContentSize().height);
        
        sprites[TORSO] = torsoSprite;
        bodies[TORSO]->SetUserData(torsoSprite);
    }
    {
        CCSprite* frontBicepSprite = new CCSprite();
        frontBicepSprite->initWithFile("sd_upperArm.png");
        
        m_layer->addChild(frontBicepSprite);
        m_layer->reorderChild(frontBicepSprite, 4);
        
        frontBicepSprite->setScale(.378 / frontBicepSprite->getContentSize().height);
        
        sprites[FRONT_BICEP] = frontBicepSprite;
        bodies[FRONT_BICEP]->SetUserData(frontBicepSprite);
    }
    {
        CCSprite* backBicepSprite = new CCSprite();
        backBicepSprite->initWithFile("sd_upperArm.png");
        
        m_layer->addChild(backBicepSprite);
        m_layer->reorderChild(backBicepSprite, -5);
        
        backBicepSprite->setScale(.378 / backBicepSprite->getContentSize().height);
        
        sprites[BACK_BICEP] = backBicepSprite;
        bodies[BACK_BICEP]->SetUserData(backBicepSprite);
    }
    {
        CCSprite* frontForearmSprite = new CCSprite();
        frontForearmSprite->initWithFile("sd_lowerArm.png");
        
        m_layer->addChild(frontForearmSprite);
        m_layer->reorderChild(frontForearmSprite, 5);
        
        frontForearmSprite->setScale(.567 / frontForearmSprite->getContentSize().height);
        
        sprites[FRONT_FOREARM] = frontForearmSprite;
        bodies[FRONT_FOREARM]->SetUserData(frontForearmSprite);
    }
    {
        CCSprite* backForearmSprite = new CCSprite();
        backForearmSprite->initWithFile("sd_lowerArm.png");
        
        m_layer->addChild(backForearmSprite);
        m_layer->reorderChild(backForearmSprite, -4);
        
        backForearmSprite->setScale(.567 / backForearmSprite->getContentSize().height);
        
        sprites[BACK_FOREARM] = backForearmSprite;
        bodies[BACK_FOREARM]->SetUserData(backForearmSprite);
    }
    {
        CCSprite* frontThighSprite = new CCSprite();
        frontThighSprite->initWithFile("sd_upperLeg.png");
        
        m_layer->addChild(frontThighSprite);
        m_layer->reorderChild(frontThighSprite, 2);
        
        frontThighSprite->setScale(.539 / frontThighSprite->getContentSize().height);
        
        sprites[FRONT_THIGH] = frontThighSprite;
        bodies[FRONT_THIGH]->SetUserData(frontThighSprite);
    }
    {
        CCSprite* backThighSprite = new CCSprite();
        backThighSprite->initWithFile("sd_upperLeg.png");
        
        m_layer->addChild(backThighSprite);
        m_layer->reorderChild(backThighSprite, -2);
        
        backThighSprite->setScale(.539 / backThighSprite->getContentSize().height);
        
        sprites[BACK_THIGH] = backThighSprite;
        bodies[BACK_THIGH]->SetUserData(backThighSprite);
    }
    {
        CCSprite* frontCalfSprite = new CCSprite();
        frontCalfSprite->initWithFile("sd_lowerLeg.png");
        
        m_layer->addChild(frontCalfSprite);
        m_layer->reorderChild(frontCalfSprite, 3);
        
        frontCalfSprite->setScale(.561 / frontCalfSprite->getContentSize().height);
        
        sprites[FRONT_CALF] = frontCalfSprite;
        bodies[FRONT_CALF]->SetUserData(frontCalfSprite);
    }
    {
        CCSprite* backCalfSprite = new CCSprite();
        backCalfSprite->initWithFile("sd_lowerLeg.png");
        
        m_layer->addChild(backCalfSprite);
        m_layer->reorderChild(backCalfSprite, -3);
        
        backCalfSprite->setScale(.561 / backCalfSprite->getContentSize().height);
        
        sprites[BACK_CALF] = backCalfSprite;
        bodies[BACK_CALF]->SetUserData(backCalfSprite);
    }
    
    updateImagePositions();
    
}

void GameCharacter::clearSprites(){
    for (int i = 0; i < 10; i++) {
        m_layer->removeChild(sprites[i]);
    }
}


void GameCharacter::updateImagePositions(){
    for (int i = 0; i < 10; i++) {
        b2Body* b = bodies[i];
     
        b2Rot rot( b->GetAngle() );
     
        sprites[i]->setPosition(CCPointMake(b->GetPosition().x , b->GetPosition().y ));
        sprites[i]->setRotation( -CC_RADIANS_TO_DEGREES(b->GetAngle()));

    }
    
    
    
}