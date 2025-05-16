#ifndef USER_H
#define USER_H

#include <memory>
#include <string>
#include "entity.h"

class Group;

class User : public Entity {
private:     
    std::weak_ptr<Group> groupLink; // weak_ptr решает проблему циклических ссылок в классах
    friend class Group;
    friend class UserGroupManager;
    void setGroup(std::shared_ptr<Group> group);

public:
    User();
    User(const std::string& userName);
    User(const std::string& userName, int userID, const std::string& userInfo = "_");
    ~User() override{}
    
    const std::shared_ptr<Group> getGroupLink() const;
    void printInfo();
};

#endif 