//
// Created by Vlad Puscaru on 12.12.2023.
//

#include "Action.h"

int Action::getId() const {
    return m_id;
}

Action::ActionTypes Action::getType() const {
    return m_type;
}

Action::Action(int id, Action::ActionTypes type)
    : m_id(id), m_type(type)
{

}
