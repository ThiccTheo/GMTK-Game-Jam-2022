#include "Entity.hpp"
#include "Player/Player.hpp"
#include "Tile/Tile.hpp"

std::unordered_map<EntityType, sf::Vector2f> Entity::bodySizeMap;

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

void Entity::init()
{
    Entity::bodySizeMap[EntityType::tile] = sf::Vector2f(16.f, 16.f);
    Entity::bodySizeMap[EntityType::player] = sf::Vector2f(16.f, 16.f);
}

const Entity* Entity::collisionHandler(const EntityType entityType)
{
    switch (entityType)
    {
        case EntityType::player:
            if (body.getGlobalBounds().intersects(Player::player.body.getGlobalBounds()))
            {
                return &Player::player;
            }
            break;
        case EntityType::tile:
            for (auto& tile : Tile::tiles)
            {
                if (body.getGlobalBounds().intersects(tile.body.getGlobalBounds()))
                {
                    return &tile;
                }
            }
            break;
    }

    return nullptr;
}
