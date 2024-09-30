#include "Entity.h"
#include "MathUtil.h"

Entity::Entity(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team) : inputHandler(inputHandler), team(team) {
    sprite.setPosition(spawnPos);
    healthbar = new Healthbar(0.25, sf::Vector2f(spawnPos.x, spawnPos.y-15));
}

Entity::~Entity() {
    delete inputHandler;
    delete healthbar;
}

void Entity::move(sf::Vector2f direction, Level& level, float dt) {
    velocity.x = direction.x * speed * dt;
    velocity.y = direction.y * speed * dt;
    sf::Vector2f currentPosition = sprite.getPosition();
    sprite.move(velocity.x, 0);
    if (isColliding(level)) {
        sprite.setPosition(currentPosition);
        velocity.x;
    }
    currentPosition = sprite.getPosition();
    sprite.move(0, velocity.y);
    if (isColliding(level)) {
        sprite.setPosition(currentPosition);
        velocity.y = 0;
    }
}

void Entity::takeDamage(int dmgAmount) {
    health -= dmgAmount;
    std::cout << "took " << dmgAmount << "dmg, current health = " << health << "\n";
}

int Entity::getValue() {
    return value;
}

int Entity::getHealth() {
    return health;
}

int Entity::getMaxHealth() {
    return maxHealth;
}

bool Entity::isDead() {
    return health <= 0;
}

void Entity::listenToInput(float dt, Level& level, sf::RenderWindow& window) {
    inputHandler->handleInputs(getOrigin(), window);
    if (inputHandler->isMoving() && canMove) {
        move(inputHandler->getMoveDir(), level, dt);
    }
    if (inputHandler->isAttacking() && attackTimer.getElapsedTime().asSeconds() > attackDelay) {
        attack(inputHandler->getAttackDir());
        attackTimer.restart();
    }
}

void Entity::display(sf::RenderWindow& window) {
    window.draw(sprite);
    if (health < maxHealth && team == Team::ENEMY) {
        float healthFactor = (float)health/maxHealth;
        healthbar->draw(sf::Vector2f(getOrigin().x - healthbar->getSize().x/2, getOrigin().y - 30), healthFactor, window);
    }
}

bool Entity::isColliding(Level& level) {
    std::vector<std::vector<int>> collisionMap = level.getCollisionMap();
    // sprite points
    sf::FloatRect hitbox = sprite.getGlobalHitbox();
    std::array<sf::Vector2f, 4> points = {
        sf::Vector2f(hitbox.left, hitbox.top),                               //top-left
        sf::Vector2f(hitbox.left + hitbox.width, hitbox.top),                //top-right
        sf::Vector2f(hitbox.left, hitbox.top + hitbox.height),               //bottom-left
        sf::Vector2f(hitbox.left + hitbox.width, hitbox.top + hitbox.height) //bottom-right
    };

    int tileSize = level.getTileSize();
    for (int i = 0; i < 4; ++i) {
        if (collisionMap[points[i].y/tileSize][points[i].x/tileSize] == 1) {
            return true;
        }
    }
    return false;
}

bool Entity::pointInEntity(sf::Vector2f point) {
    return sprite.getGlobalHitbox().contains(point);
}

Team Entity::getTeam() {
    return team;
}

InputHandler* Entity::getInputHandler() {
    return inputHandler;
}

sf::Vector2f Entity::getPosition() {
    return sprite.getPosition();
}   

sf::Vector2f Entity::getOrigin() {
    sf::FloatRect hitbox = sprite.getGlobalHitbox();
    return sf::Vector2f(hitbox.left + (hitbox.width)/2, hitbox.top + (hitbox.height)/2);
}

void Entity::update(sf::RenderWindow& window, Level& level, float dt) {
    if (regenTimer.getElapsedTime().asSeconds() > 1) {
        if (health+regen <= maxHealth) {
            health += regen;
        }
        regenTimer.restart();
    }
    listenToInput(dt, level, window);
}