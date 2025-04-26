#include <iostream>
#include "user.h"
#include "group.h"

User::User() : Entity() {}
User::User(const std::string& userName) : Entity(userName) {}
User::User(const std::string& userName, int userID, const std::string& userInfo) : 
    Entity(userName, userID, userInfo) {}    

const std::shared_ptr<Group> User::getGroupLink() const {               
    return groupLink.lock();
}      

void User::printInfo() {
    std::cout << "Имя: " << name << " ID: " << id << " Доп. информация: " << addInfo << std::endl;
    if (auto group = groupLink.lock()) {
        std::cout << "Имя группы: " << group->getName() 
                  << " Адрес группы: " << group.get() 
                  << " Доп. информация группы: " << group->getInfo() << std::endl;
    } else {
        std::cout << "Группа: nullptr" << std::endl;
    }
}

// Функция для задания ссылки группы, в которой состоит пользователь
// friend class Group;
// friend class UserGroupManager;
void User::setGroup(std::shared_ptr<Group> group){
    groupLink = group;
}
