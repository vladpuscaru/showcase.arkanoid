//
// Created by Vlad Puscaru on 12.12.2023.
//

#ifndef COMP4300_ASSIGNMENT3_ACTION_H
#define COMP4300_ASSIGNMENT3_ACTION_H


class Action {
public:
    enum ActionTypes {
        START, STOP
    };

    Action(int id, ActionTypes type);

    int getId() const;
    ActionTypes getType() const;
private:
    int m_id;
    ActionTypes m_type;
};


#endif //COMP4300_ASSIGNMENT3_ACTION_H
