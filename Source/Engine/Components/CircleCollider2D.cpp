#include "CircleCollider2D.h"

namespace Cpain {

    void Cpain::CircleCollider2D::update(float deltaTime) {

    }

    bool Cpain::CircleCollider2D::checkCollision(ColliderComponent& other) {
        float distance = (owner->transform.position - other.owner->transform.position).length();
        auto collider = dynamic_cast<CircleCollider2D*>(&other);
        if (collider) {
            float radii = radius + collider->radius;
            if (distance <= radii) return true;
        }

        return false;
    }

}
