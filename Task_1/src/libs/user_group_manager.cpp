#include "user_group_manager.h"
#include <iostream>

void UserGroupManager::createUser(int userId, const std::string& username, const std::string& userInfo) {
    if (users.find(userId) != users.end()) {
        std::cout << "Ошибка: пользователь с ID " << userId << " уже существует" << std::endl;
        return;
    }
    try {
        users[userId] = std::make_shared<User>(username, userId, userInfo);
        std::cout << "Пользователь " << username << " (ID: " << userId 
                  << ", Доп. информация: " << userInfo << ") успешно создан" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка создания пользователя: " << e.what() << std::endl;
    }
}

void UserGroupManager::deleteUser(int userId) {
    auto it = users.find(userId);
    if (it == users.end()) {
        std::cout << "Ошибка: пользователь с ID " << userId << " не найден" << std::endl;
        return;
    }
    
    if (auto group = it->second->getGroupLink()) {
        group->removeUser(it->second);
    }
    
    users.erase(it);
    std::cout << "Пользователь с ID " << userId << " успешно удален" << std::endl;
}

void UserGroupManager::allUsers() const {
    if (users.empty()) {
        std::cout << "Нет ни одного пользователя" << std::endl;
        return;
    }
    
    std::cout << "Список всех пользователей:" << std::endl;
    for (const auto& [id, user] : users) {
        user->printInfo();
        std::cout << "-------------------" << std::endl;
    }
}

void UserGroupManager::getUser(int userId) const {
    auto it = users.find(userId);
    if (it == users.end()) {
        std::cout << "Ошибка: Пользователя с ID " << userId << " не найден" << std::endl;
        return;
    }
    
    std::cout << "Информация о пользователе:" << std::endl;
    it->second->printInfo();
}

void UserGroupManager::createGroup(int groupId, const std::string& groupName, const std::string& groupInfo) {
    if (groups.find(groupId) != groups.end()) {
        std::cout << "Ошибка: Группа с ID " << groupId << " уже существует" << std::endl;
        return;
    }
    try {
        groups[groupId] = std::make_shared<Group>(groupName, groupId, groupInfo);
        std::cout << "Группа " << groupName << " (ID: " << groupId 
                  << ", Доп. информация: " << groupInfo << ") успешно создана" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка создания группы: " << e.what() << std::endl;
    }
}

void UserGroupManager::deleteGroup(int groupId) {
    auto it = groups.find(groupId);
    if (it == groups.end()) {
        std::cout << "Ошибка: Группа с ID " << groupId << " не найдена" << std::endl;
        return;
    }
    
    for (auto& user : it->second->getUsers()) {
        user->setGroup(nullptr);
    }
    
    groups.erase(it);
    std::cout << "Группа с ID " << groupId << " успешно удалена" << std::endl;
}

void UserGroupManager::allGroups() const {
    if (groups.empty()) {
        std::cout << "Нет никаких групп" << std::endl;
        return;
    }
    
    std::cout << "Список всех групп:" << std::endl;
    for (const auto& [id, group] : groups) {
        group->printInfo();
        std::cout << "-------------------" << std::endl;
    }
}

void UserGroupManager::getGroup(int groupId) const {
    auto it = groups.find(groupId);
    if (it == groups.end()) {
        std::cout << "Ошибка: Группа с ID " << groupId << " не найдена" << std::endl;
        return;
    }
    
    std::cout << "Информация о группе:" << std::endl;
    it->second->printInfo();
}

void UserGroupManager::addUserToGroup(int userId, int groupId) {
    auto userIt = users.find(userId);
    auto groupIt = groups.find(groupId);
    
    if (userIt == users.end()) {
        std::cout << "Ошибка: Пользователь с ID " << userId << " не найден" << std::endl;
        return;
    }
    if (groupIt == groups.end()) {
        std::cout << "Ошибка: Группа с ID " << groupId << " не найдена" << std::endl;
        return;
    }
    
    try {
        groupIt->second->addUser(userIt->second);
        std::cout << "Пользователь " << userIt->second->getName() << " (ID: " << userId 
                 << ") добавлен в группу " << groupIt->second->getName() 
                 << " (ID: " << groupId << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void UserGroupManager::removeUserFromGroup(int userId, int groupId) {
    auto userIt = users.find(userId);
    auto groupIt = groups.find(groupId);
    
    if (userIt == users.end()) {
        std::cout << "Ошибка: Пользователь с ID " << userId << " не найден" << std::endl;
        return;
    }
    if (groupIt == groups.end()) {
        std::cout << "Ошибка: Группа с ID " << groupId << " не найдена" << std::endl;
        return;
    }
    
    try {
        groupIt->second->removeUser(userIt->second);
        std::cout << "Пользователь " << userIt->second->getName() << " (ID: " << userId 
                 << ") удален из группы " << groupIt->second->getName() 
                 << " (ID: " << groupId << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void UserGroupManager::setUserInfo(int userId, const std::string& info) {
    auto it = users.find(userId);
    if (it == users.end()) {
        std::cout << "Ошибка: Пользователь с ID " << userId << " не найден" << std::endl;
        return;
    }
    it->second->setInfo(info);
    std::cout << "Доп. информация для пользователя " << it->second->getName() 
             << " (ID: " << userId << ") установлена: " << info << std::endl;
}

void UserGroupManager::setGroupInfo(int groupId, const std::string& info) {
    auto it = groups.find(groupId);
    if (it == groups.end()) {
        std::cout << "Ошибка: Группа с ID " << groupId << " не найдена" << std::endl;
        return;
    }
    it->second->setInfo(info);
    std::cout << "Доп. информация для группы " << it->second->getName() 
             << " (ID: " << groupId << ") установлена: " << info << std::endl;
}