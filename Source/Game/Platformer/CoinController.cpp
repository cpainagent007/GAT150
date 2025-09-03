#include "CoinController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(CoinController)

void CoinController::onCollision(Cpain::Actor* collider) {
    if (collider->tag == "player") {
        EVENT_NOTIFY_DATA(add_points, score);
        owner->active = false;
    }
}

void CoinController::read(const Cpain::Json::value_t& value) {
    Object::read(value);

    JSON_READ(value, score);
}

void CoinController::update(float deltaTime) {

}

void CoinController::start() {
    m_rigidBody = owner->getComponent<Cpain::RigidBody>();
}

void CoinController::onNotify(const Cpain::Event& event) {
    
}