//
// Created by Vlad Puscaru on 12.12.2023.
//

#include "Entity.h"

Entity::Entity(int tag, size_t id)
        : m_tag(tag), m_id(id), m_alive(true)
{

}

void Entity::destroy() {
    m_alive = false;
}

int Entity::getTag() const {
    return m_tag;
}

bool Entity::isAlive() const {
    return m_alive;
}

size_t Entity::getId() const {
    return m_id;
}