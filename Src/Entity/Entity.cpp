#include "Entity.hpp"

Entity::Entity() = default;

Entity::Entity(const sf::Vector2i& indices, const sf::Vector2f& bodySize, const OriginSpot originSpot)
{
    body.setSize(bodySize);
    const sf::FloatRect& bodyBounds{ body.getLocalBounds() };

    switch (originSpot)
    {
    case OriginSpot::topLeft:
        body.setOrigin(0.f, 0.f);
        break;
    case OriginSpot::topCenter:
        body.setOrigin(bodyBounds.width / 2.f, 0.f);
        break;
    case OriginSpot::topRight:
        body.setOrigin(bodyBounds.width, 0.f);
        break;
    case OriginSpot::middleLeft:
        body.setOrigin(0.f, bodyBounds.height / 2.f);
        break;
    case OriginSpot::middleCenter:
        body.setOrigin(bodyBounds.width / 2.f, bodyBounds.height / 2.f);
        break;
    case OriginSpot::middleRight:
        body.setOrigin(bodyBounds.width, bodyBounds.height / 2.f);
        break;
    case OriginSpot::bottomLeft:
        body.setOrigin(0.f, bodyBounds.height);
        break;
    case OriginSpot::bottomCenter:
        body.setOrigin(bodyBounds.width / 2.f, bodyBounds.height);
        break;
    case OriginSpot::bottomRight:
        body.setOrigin(bodyBounds.width, bodyBounds.height);
        break;
    }

    body.setPosition(16.f * indices.x, 16.f * indices.y); //change to tile size for 16.f
}
