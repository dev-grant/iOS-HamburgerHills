//
//  HillsLayer.cpp
//  HamburgerHills
//
//  Created by Grant on 7/14/14.
//
//

#include "HillsLayer.h"
#include "QueryCallbacks.h"

using namespace std;
using namespace cocos2d;

const char* HillsLayer::LEVELNAMES[] = {"testLevel1.json", "testLevel2.json", "testLevel3.json"};

CCScene* HillsLayer::scene(const char* levelName, int tag){
    CCScene *scene = CCScene::create();
    
    HillsLayer* layer = new HillsLayer();
    layer->init(levelName, tag);
    scene->addChild(layer);
    layer->release();
    
    scene->addChild(layer->setupMenuLayer());
    scene->addChild(layer->setupHUDLayer());
    scene->addChild(layer->setupLevelEndLayer());
    scene->addChild(layer->setupDeathLayer());
    
    return scene;
}

CCLayer* HillsLayer::setupHUDLayer(){
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItem* rollButton = new TouchUpMenuItem(CCSprite::create("ui_roll.png"), CCSprite::create("ui_roll_s.png"), this, menu_selector(HillsLayer::menuSelected), this, ROLL);
    rollButton->setPosition(-s.width/2 + 130, -s.height/2 + 80);
    
    CCMenuItem* plankButton = new TouchUpMenuItem(CCSprite::create("ui_plank.png"), CCSprite::create("ui_plank_s.png"), this, menu_selector(HillsLayer::menuSelected), this, PLANK);
    plankButton->setPosition(s.width/2 - 130, -s.height/2 + 80);
    
    CCMenuItem* timeBg = CCMenuItemImage::create("ui_timeBG.png", "ui_timeBG.png");
    timeBg->setScale(.75);
    timeBg->setPosition(s.width/2 - 150, s.height/2 - 55);
    timeBg->setEnabled(false);
    
    CCMenuItemFont* timerLabel = CCMenuItemFont::create("000");
    timerLabel->setScale(1.5);
    timerLabel->setTag(1);
    timerLabel->setFontName("Myriad");
    timerLabel->setColor(ccc3(86, 34, 16));
    timerLabel->setPosition(s.width/2-100, s.height/2-50);
    
    CCMenuItemFont* limbsLabel = CCMenuItemFont::create("0");
    limbsLabel->setScale(1.5);
    limbsLabel->setTag(2);
    limbsLabel->setFontName("Myriad");
    limbsLabel->setColor(ccc3(86, 34, 16));
    limbsLabel->setPosition(-s.width/2+100, s.height/2-50);
    
    m_HUDLayer = CCMenu::create(rollButton, plankButton, timeBg, timerLabel, limbsLabel, NULL);
    //m_HUDLayer->alignItemsHorizontally();
    
    updateAfterOrientationChange();
    
    //[[NSNotificationCenter defaultCenter] addObserver:self
	//										 selector:@selector(updateAfterOrientationChange:)
	//											 name:UIDeviceOrientationDidChangeNotification
	//										   object:nil];
    return m_HUDLayer;
}

CCLayer* HillsLayer::setupMenuLayer()
{
    CCMenuItem *backItem = CCMenuItemSprite::create(CCSprite::create("ui_menu.png"), CCSprite::create("ui_menu_s.png"), this, menu_selector(BasicRUBELayer::goBack));
    CCMenuItem* reloadItem = CCMenuItemSprite::create(CCSprite::create("ui_restart.png"), CCSprite::create("ui_restart_s.png"), this, menu_selector(HillsLayer::reloadLevel));
    m_menuLayer = CCMenu::create(backItem,reloadItem,NULL);
    m_menuLayer->alignItemsHorizontallyWithPadding(20);
    
    updateAfterOrientationChange();
    
    backItem->setPositionY(backItem->getPositionY() - 20);
    reloadItem->setPositionY(reloadItem->getPositionY() - 20);
    
    //[[NSNotificationCenter defaultCenter] addObserver:self
	//										 selector:@selector(updateAfterOrientationChange:)
	//											 name:UIDeviceOrientationDidChangeNotification
	//										   object:nil];
    return m_menuLayer;
}

CCLayer* HillsLayer::setupLevelEndLayer(){
    //CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItem* bg = CCMenuItemImage::create("ui_levelEndHD.png", "ui_levelEndHD.png");
    //bgItem->setPosition(s.width/2, s.height/2);
    bg->setEnabled(false);
    
    CCMenuItem* storeItem = CCMenuItemSprite::create(CCSprite::create("ui_endStore.png"), CCSprite::create("ui_endStore_s.png"), this, menu_selector(BasicRUBELayer::loadWorld));
    storeItem->setPosition(-157, -242);
    
    CCMenuItem* reloadItem = CCMenuItemSprite::create(CCSprite::create("ui_endRestart.png"), CCSprite::create("ui_endRestart_s.png"), this, menu_selector(HillsLayer::reloadLevel));
    reloadItem->setPosition(-53, -242);
    
    CCMenuItem* menuItem = CCMenuItemSprite::create(CCSprite::create("ui_endMenu.png"), CCSprite::create("ui_endMenu_s.png"), this, menu_selector(BasicRUBELayer::goBack));
    menuItem->setPosition(55, -242);
    
    CCMenuItem* nextItem = CCMenuItemSprite::create(CCSprite::create("ui_endNext.png"), CCSprite::create("ui_endNext_s.png"), this, menu_selector(HillsLayer::nextLevel));
    nextItem->setPosition(159, -242);
    
    
    m_levelEndLayer = CCMenu::create(bg, storeItem, reloadItem, menuItem, nextItem, NULL);
    m_levelEndLayer->setVisible(false);
    
    return m_levelEndLayer;
}

CCLayer* HillsLayer::setupDeathLayer(){
    CCMenuItem* deathOverlay = CCMenuItemImage::create("deathOverlay.png", "deathOverlay.png");
    //bgItem->setPosition(s.width/2, s.height/2);
    deathOverlay->setEnabled(false);
    
    m_deathLayer = CCMenu::create(deathOverlay, NULL);
    m_deathLayer->setOpacity(0);
    
    return m_deathLayer;
}

void HillsLayer::nextLevel(){
    m_levelIndex = m_levelIndex + 1;
    const char* nextLvlName = LEVELNAMES[m_levelIndex];
    CCDirector::sharedDirector()->replaceScene(HillsLayer::scene(nextLvlName, m_levelIndex));
}

void HillsLayer::reloadLevel(){
    const char* lvlName = LEVELNAMES[m_levelIndex];
    CCDirector::sharedDirector()->replaceScene(HillsLayer::scene(lvlName, m_levelIndex));
}

void HillsLayer::menuSelected(ButtonMode m){
    switch (m) {
        case ROLL:
            m_character->startRolling();
            break;
        case PLANK:
            m_character->startPlanking();
            break;
        default:
            break;
    }
}

void HillsLayer::menuUnselected(ButtonMode m){
    switch (m) {
        case ROLL:
            m_character->stopRolling();
            break;
        case PLANK:
            m_character->stopPlanking();
            break;
        default:
            break;
    }
}

bool HillsLayer::init(const char* levelName, int tag){
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    m_levelName = levelName;
    m_levelIndex = tag;
    
    RUBELayer::init();
    
    this->setAccelerometerEnabled(true);
    
    CCLayerGradient *skyGradient = CCLayerGradient::create(ccc4(160, 198, 221, 255), ccc4(82, 127, 186,255), ccp(0, 1));
    skyGradient->setScale(3);
    
    m_parallaxNode = CCParallaxNode::create();
    this->addChild(m_parallaxNode, -6);
    m_parallaxNode->setScale(.01f);
    m_parallaxNode->setPosition(0, s.height/2/m_worldScale);
    
    CCSprite *moon = CCSprite::create("bg_moon.png");
    CCSprite *clouds = CCSprite::create("bg_clouds.png");
    CCSprite *bg = CCSprite::create("bg_game.png");
    CCSprite *mg = CCSprite::create("mg_game.png");
    CCSprite *fg = CCSprite::create("fg_game.png");
    
    CCPoint cloudMoonSpeed = ccp(0.05, 0.05);
    CCPoint bgSpeed = ccp(0.05, 0.05);
    
    m_parallaxNode->addChild(fg, 4, bgSpeed, ccp(800, -400));
    m_parallaxNode->addChild(mg, 3, bgSpeed, ccp(800, -50));
    m_parallaxNode->addChild(bg, 2, bgSpeed, ccp(800, -50));
    m_parallaxNode->addChild(clouds, 1, cloudMoonSpeed, ccp(800, 275));
    m_parallaxNode->addChild(moon, 0, cloudMoonSpeed, ccp(800, 275));
    m_parallaxNode->addChild(skyGradient, -1, ccp(0, 0), ccp(0, 0));

    return true;
}

string HillsLayer::getFilename(){
    return m_levelName;
}

CCPoint HillsLayer::initialWorldOffset(){
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    return CCPointMake(s.width/2, 0);
}

float HillsLayer::initialWorldScale(){
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    if (s.height == 1136 || s.height == 568 ){
        m_worldScale = s.width / 32;
        return m_worldScale;
    }else{
        m_worldScale = (s.height - 40) / 8;
        return m_worldScale;
    }
}

void HillsLayer::afterLoadProcessing(b2dJson *json){
    RUBELayer::afterLoadProcessing(json);

    m_world->SetContactListener(this);
    
    m_spawnPoint = json->getBodyByName("spawnPoint");

    m_character = new GameCharacter(m_spawnPoint->GetPosition(), m_world, this);

}


void HillsLayer::updateTimerLabel(){
    m_totalTime += 1;
    CCMenuItemFont* f1 = static_cast<CCMenuItemFont*>(m_HUDLayer->getChildByTag(1));
    
    std::stringstream ss;
    ss << m_totalTime;
    const char* c = ss.str().c_str();
    
    f1->setString(c);
}

void HillsLayer::update(float dt){
    RUBELayer::update(dt);
    
    if (!m_timerStarted) {
        m_timerStarted = true;
        
        this->schedule(schedule_selector(HillsLayer::updateTimerLabel), .10f);
    }
    
    m_character->updateImagePositions();
    
    for (int i = 0; i < 9; i++) {
        JointName j = static_cast<JointName>(i);
        
        if (m_character->jointIntact(j)) {
            if (m_character->getJoint(j)->GetReactionForce(dt).LengthSquared() > .003f){
                /*CCParticleSystem *emitterA = CCParticleSystemQuad::create("particle_blood.plist");
                emitterA->setScale(.013f);
                
                CCParticleSystem *emitterB = CCParticleSystemQuad::create("particle_blood.plist");
                emitterB->setScale(.013f);
                
                this->addChild(emitterA);
                this->addChild(emitterB);
                
                b2Vec2 posA = m_character->getJoint(j)->GetAnchorA();
                float32 angA = m_character->getJoint(j)->GetBodyA()->GetAngle();
                emitterA->setPosition(ccp(posA.x, posA.y));
                emitterA->setAngle(angA);
                emitterA->setAutoRemoveOnFinish(true);
                
                b2Vec2 posB = m_character->getJoint(j)->GetAnchorB();
                float32 angB = m_character->getJoint(j)->GetBodyB()->GetAngle();
                emitterB->setPosition(ccp(posB.x, posB.y));
                emitterB->setAngle(angB);
                emitterB->setAutoRemoveOnFinish(true);
                
                ParticleData dataB;
                dataB.attachedBody = m_character->getJoint(j)->GetBodyB();
                dataB.particleSystem = emitterB;
                dataB.localPosition = m_character->getJoint(j)->GetLocalAnchorB();
                */
                
                
                m_world->DestroyJoint(m_character->getJoint(j));
                m_character->setJointNull(j);
                
                
                if (j == F_TORSO_BICEP || j == F_TORSO_LEG || j == B_TORSO_BICEP || j == B_TORSO_LEG) {
                    m_character->incrementLimbsLostBy(1);
                }
                /*else{
                    m_character->incrementLimbsLostBy(1);
                }
                */
                
                CCMenuItemFont* limbsLabel = static_cast<CCMenuItemFont*>(m_HUDLayer->getChildByTag(2));
                
                std::stringstream ss;
                ss << m_character->getNumLimbsLost();
                const char* c = ss.str().c_str();
                
                limbsLabel->setString(c);
                
                if (m_character->getJoint(j) == m_character->getJoint(TORSO_HEAD)) {
                    m_character->setAlive(false);
                    for (int i = 1; i < 10; i++){
                        JointName j = static_cast<JointName>(i);
                        if (m_character->jointIntact(j))
                            m_character->getJoint(j)->EnableMotor(false);
                    }
                    CCFadeIn *fadeIn = CCFadeIn::create(2);
                    m_deathLayer->runAction(fadeIn);
                }
            }
        }
    }
    
    if (m_controlEnabled) {
        m_character->runMotors();
        
        m_parallaxNode->setPosition(m_character->getSprite(TORSO)->getPosition());
        
        float centerX, centerY, centerZ;
        float eyeX, eyeY, eyeZ;
        
        this->getCamera()->getCenterXYZ(&centerX, &centerY, &centerZ);
        this->getCamera()->getEyeXYZ(&eyeX, &eyeY, &eyeZ);
        
        centerX = eyeX = m_character->getSprite(TORSO)->getPosition().x ;
        centerY = eyeY = m_character->getSprite(TORSO)->getPosition().y - 4;
        
        
        this->getCamera()->setCenterXYZ(centerX, centerY, centerZ);
        this->getCamera()->setEyeXYZ(eyeX, eyeY, eyeZ);
    }


}

void HillsLayer::didAccelerate(cocos2d::CCAcceleration *pAccelerationValue){
    
    m_character->updateRotationSpeed(pAccelerationValue->x);
}

void HillsLayer::clear(){
    
    if (m_character) {
        m_character->clearSprites();
    }
    
    RUBELayer::clear();
}



void HillsLayer::showLevelEndMenu(){
    m_menuLayer->setVisible(false);
    m_HUDLayer->setVisible(false);

    m_levelEndLayer->setVisible(true);
}

void HillsLayer::BeginContact(b2Contact *contact){
    if (((contact->GetFixtureA()->GetFilterData().categoryBits == 2 && contact->GetFixtureB()->GetFilterData().categoryBits == 4) || (contact->GetFixtureA()->GetFilterData().categoryBits == 4 && contact->GetFixtureB()->GetFilterData().categoryBits == 2)) && m_controlEnabled) {
        m_controlEnabled = false;
        this->showLevelEndMenu();
    }
    
    if ((contact->GetFixtureA()->GetFilterData().categoryBits == 2 && contact->GetFixtureB()->GetFilterData().categoryBits == 8) || (contact->GetFixtureA()->GetFilterData().categoryBits == 8 && contact->GetFixtureB()->GetFilterData().categoryBits == 2)) {
        
        m_world->SetGravity(b2Vec2(0, 10));
    }
}

/*
void HillsLayer::EndContact(b2Contact *contact){
    
}

void HillsLayer::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse){

}
*/
