#pragma once
#include <memory>

class Entity;

class Component {
public:
    virtual ~Component() = default;

    virtual void tick() = 0;
    virtual void init() = 0;

    void setOwner(std::weak_ptr<Entity> owner) {
        this->owner = owner;
    }

    std::shared_ptr<Entity> getOwner() const {
        return owner.lock();
    }

private:
    std::weak_ptr<Entity> owner;
};