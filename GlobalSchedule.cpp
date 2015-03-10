/////////////////////
// GlobalSchedule.cpp
/////////////////////

#include "GlobalSchedule.h"

#define SCHEDULE CCDirector::sharedDirector()->getScheduler()

GlobalSchedule* GlobalSchedule::m_pSchedule = NULL;

GlobalSchedule::GlobalSchedule(float fInterval, float fDelay) {
    CCLog("GlobalSchedule()");
    
    CCAssert(!m_pSchedule, "已定义，不能重复定义");

    //SCHEDULE->scheduleSelector(
    //                           schedule_selector(GlobalSchedule::globalUpdate), this, fInterval,
     ///                          false,
     //                          kCCRepeatForever, fDelay);
    this->onEnter();//这里进行了修改，不在这里直接启动计时器，而是在enter里面
    m_pSchedule = this;
}

void GlobalSchedule::onEnter()
{
    CCNode::onEnter();
    schedule(schedule_selector(GlobalSchedule::globalUpdate), 60.0f);//在这里启动计时器
}

GlobalSchedule::~GlobalSchedule() {
    CCLog("GlobalSchedule().~()");
    
    unschedule(schedule_selector(GlobalSchedule::globalUpdate));
}

void GlobalSchedule::globalUpdate() {
    CCLog("global update");
    /*这里是你写的计时器发生代码*/
}

void GlobalSchedule::start(float fInterval, float fDelay) {
    new GlobalSchedule(fInterval, fDelay);
}

void GlobalSchedule::stop() {
    CCLog("GlobalSchedule().stop()");
    
    CCAssert(m_pSchedule, "未定义");
    CC_SAFE_DELETE(m_pSchedule);
}
