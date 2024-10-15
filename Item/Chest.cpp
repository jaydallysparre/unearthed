#include "Chest.h"
#include <random>

Chest::Chest(sf::Vector2f position) : Interactable(position) {
    spriteTexture.loadFromFile("img/chest.png");
    highlightTexture.loadFromFile("img/highlightchest.png");
    sprite.setTexture(spriteTexture);
}

// Sets highlight, so the player knows they can interact with the chest.

void Chest::setHighlight(bool highlight) {
    if (highlight) {
        sprite.setTexture(highlightTexture);
    }
    else {
        sprite.setTexture(spriteTexture);
    }
}

// Give target entity random stat upgrade.

Alert Chest::use(Entity* entity) {
    std::mt19937 mt {std::random_device{}()};
    std::uniform_int_distribution upgrade {1,6};
    switch (upgrade(mt)) {
        case 1:
            entity->upgradeMaxHealth(10);
            return Alert("+10 Max Health!", 2);
        case 2:
            entity->upgradeAttackDamage(5);
            return Alert("+5 Attack Damage!", 2);
        case 3:
            entity->upgradeAttackSpeed(0.02);
            return Alert("+0.02 Attack Speed!", 2);
        case 4:
            entity->upgradeRegen(1);
            return Alert("+1 Regen!", 2);
        case 5:
            entity->upgradeSpeed(5);
            return Alert("+5 Speed!", 2);
        case 6:
            entity->healToFull();
            return Alert("Healed to full!", 2);
    }
    return Alert("Upgrade not found? This is a bug", 5);
}