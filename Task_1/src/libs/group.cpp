#include "group.h"
#include "user.h"
#include <iostream>

Group::Group() : Entity() {}
Group::Group(const std::string& groupName) : Entity(groupName) {}
Group::Group(const std::string& groupName, int groupID, const std::string& groupInfo) : 
    Entity(groupName, groupID, groupInfo) {}

Group::~Group() {
    usersList.clear();
}

void Group::addUser(std::shared_ptr<User> user) {
    if (!user) {
        throw std::runtime_error("Попытка добавить nullptr!");
    }
    
    auto it = std::find_if(usersList.begin(), usersList.end(),
        [user](const auto& u) { return u->getID() == user->getID(); });
        
    if (it != usersList.end()) {
        throw std::runtime_error("Пользователь уже в группе!");
    }

    // Удаляем пользователя из старой группы, если он в ней состоял
    if (user->getGroupLink() != nullptr)
    {
        user->getGroupLink()->removeUser(user);
    }
    

    usersList.push_back(user);
    user->setGroup(shared_from_this());
}

void Group::removeUser(std::shared_ptr<User> user) {
    auto it = std::find_if(usersList.begin(), usersList.end(),
        [user](const auto& u) { return u->getID() == user->getID(); });
        
    if (it == usersList.end()) {
        throw std::runtime_error("Пользователь не найден в группе!");
    }
    
    (*it)->setGroup(nullptr);
    usersList.erase(it);
}

const std::vector<std::shared_ptr<User>>& Group::getUsers() const {
    return usersList;
}

void Group::printInfo() {
    std::cout << "Имя: " << name << " ID: " << id << " Доп. информация: " << addInfo << std::endl;
    std::cout << "Список участников: ";
    if (usersList.empty()) {
        std::cout << "(нет участников)" << std::endl;
        return;
    }
    for (const auto& user : usersList) {
        std::cout << user->getName() << " (ID: " << user->getID() << ", Доп. информация: " << user->getInfo() << "), ";
    }
    std::cout << std::endl;
}