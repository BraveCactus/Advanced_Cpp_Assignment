#include <iostream>
#include <string>
#include <sstream>
#include "user_group_manager.h"

void printHelp() {
    std::cout << "Доступные команды:" << std::endl;
    std::cout << "  createUser <userId> <username> [доп.инфо] - Создать нового пользователя" << std::endl;
    std::cout << "  deleteUser <userId> - Удалить пользователя" << std::endl;
    std::cout << "  allUsers - Показать всех пользователей" << std::endl;
    std::cout << "  getUser <userId> - Показать информацию о пользователе" << std::endl;
    std::cout << "  createGroup <groupId> <groupName> [доп.инфо] - Создать новую группу" << std::endl;
    std::cout << "  deleteGroup <groupId> - Удалить группу" << std::endl;
    std::cout << "  allGroups - Показать все группы" << std::endl;
    std::cout << "  getGroup <groupId> - Показать информацию о группе" << std::endl;
    std::cout << "  addUserToGroup <userId> <groupId> - Добавить пользователя в группу" << std::endl;
    std::cout << "  removeUserFromGroup <userId> <groupId> - Удалить пользователя из группы" << std::endl;
    std::cout << "  setUserInfo <userId> <инфо> - Установить доп. информацию для пользователя" << std::endl;
    std::cout << "  setGroupInfo <groupId> <инфо> - Установить доп. информацию для группы" << std::endl;
    std::cout << "  help - Показать эту справку" << std::endl;
    std::cout << "  exit - Выйти из программы" << std::endl;
}

void processCommand(const std::string& command, UserGroupManager& manager) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "createUser") {
        int userId;
        std::string username, info = "_";
        if (iss >> userId >> username) {
            std::getline(iss, info);
            if(info.empty()){
                info = "_";
            }
            manager.createUser(userId, username, info);
        } else {
            std::cout << "Ошибка: Неверные аргументы для createUser. Использование: createUser <userId> <username> [доп.инфо]" << std::endl;
        }
    }
    else if (cmd == "deleteUser") {
        int userId;
        if (iss >> userId) {
            manager.deleteUser(userId);
        } else {
            std::cout << "Ошибка: Неверные аргументы для deleteUser. Использование: deleteUser <userId>" << std::endl;
        }
    }
    else if (cmd == "allUsers") {
        manager.allUsers();
    }
    else if (cmd == "getUser") {
        int userId;
        if (iss >> userId) {
            manager.getUser(userId);
        } else {
            std::cout << "Ошибка: Неверные аргументы для getUser. Использование: getUser <userId>" << std::endl;
        }
    }
    else if (cmd == "createGroup") {
        int groupId;
        std::string groupName, info = "_";
        if (iss >> groupId >> groupName) {
            std::getline(iss, info);
            if (info.empty())
            {
                info = "_";
            }
            
            manager.createGroup(groupId, groupName, info);
        } else {
            std::cout << "Ошибка: Неверные аргументы для createGroup. Использование: createGroup <groupId> <groupName> [доп.инфо]" << std::endl;
        }
    }
    else if (cmd == "deleteGroup") {
        int groupId;
        if (iss >> groupId) {
            manager.deleteGroup(groupId);
        } else {
            std::cout << "Ошибка: Неверные аргументы для deleteGroup. Использование: deleteGroup <groupId>" << std::endl;
        }
    }
    else if (cmd == "allGroups") {
        manager.allGroups();
    }
    else if (cmd == "getGroup") {
        int groupId;
        if (iss >> groupId) {
            manager.getGroup(groupId);
        } else {
            std::cout << "Ошибка: Неверные аргументы для getGroup. Использование: getGroup <groupId>" << std::endl;
        }
    }
    else if (cmd == "addUserToGroup") {
        int userId, groupId;
        if (iss >> userId >> groupId) {
            manager.addUserToGroup(userId, groupId);
        } else {
            std::cout << "Ошибка: Неверные аргументы для addUserToGroup. Использование: addUserToGroup <userId> <groupId>" << std::endl;
        }
    }
    else if (cmd == "removeUserFromGroup") {
        int userId, groupId;
        if (iss >> userId >> groupId) {
            manager.removeUserFromGroup(userId, groupId);
        } else {
            std::cout << "Ошибка: Неверные аргументы для removeUserFromGroup. Использование: removeUserFromGroup <userId> <groupId>" << std::endl;
        }
    }
    else if (cmd == "setUserInfo") {
        int userId;
        std::string info;
        if (iss >> userId) {
            getline(iss, info);
            if (!info.empty() && info[0] == ' ') {
                info = info.substr(1);
            }
            manager.setUserInfo(userId, info);
        } else {
            std::cout << "Ошибка: Неверные аргументы для setUserInfo. Использование: setUserInfo <userId> <инфо>" << std::endl;
        }
    }
    else if (cmd == "setGroupInfo") {
        int groupId;
        std::string info;
        if (iss >> groupId) {
            getline(iss, info);
            if (!info.empty() && info[0] == ' ') {
                info = info.substr(1);
            }
            manager.setGroupInfo(groupId, info);
        } else {
            std::cout << "Ошибка: Неверные аргументы для setGroupInfo. Использование: setGroupInfo <groupId> <инфо>" << std::endl;
        }
    }
    else if (cmd == "help") {
        printHelp();
    }
    else if (cmd == "exit") {
        exit(0);
    }
    else {
        std::cout << "Ошибка: Неизвестная команда. Введите 'help' для списка команд." << std::endl;
    }
}

int main() {    
    UserGroupManager manager;
    std::string command;

    std::cout << "Система управления пользователями и группами" << std::endl;
    std::cout << "Введите 'help' для списка команд" << std::endl;

    while (true) { 
        std::cout << "> ";
        getline(std::cin, command);
        if (!command.empty()) {
            processCommand(command, manager);
        }
    }

    return 0;
}