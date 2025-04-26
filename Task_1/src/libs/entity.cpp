#include "entity.h"

void Entity::checkAndAddID(int new_id, std::vector<int>& list) {
    if (std::find(list.begin(), list.end(), new_id) != list.end()) { 
        throw std::runtime_error("Вы попытались присвоить ID, которое уже занято!"); 
    }
    list.push_back(new_id);
}

void Entity::checkAndAddName(const std::string& new_name, std::vector<std::string>& list) { 
    if (std::find(list.begin(), list.end(), new_name) != list.end()) { 
        throw std::runtime_error("Вы попытались присвоить имя, которое уже занято!"); 
    }
    list.push_back(new_name);
}

Entity::Entity() : name("_"), id(0), addInfo("_") {
    for (int i = 0; i < idLists.size() + 1; i++) {
        if (find(idLists.begin(), idLists.end(), i) == idLists.end()) {
            id = i;
            break;
        }            
    }
    checkAndAddID(id, idLists);      
    checkAndAddName(name, namesLists); 
}

Entity::Entity(const std::string& initialName) : name(initialName), id(0), addInfo("_") {
    for (int i = 0; i < idLists.size() + 1; i++) {
        if (find(idLists.begin(), idLists.end(), i) == idLists.end()) {
            id = i;
            break;
        }            
    }      
    checkAndAddID(id, idLists);      
    checkAndAddName(name, namesLists);     
}

Entity::Entity(const std::string& initialName, int identifier, const std::string& info) : 
    name(initialName), id(identifier), addInfo(info) {
    checkAndAddID(id, idLists);
    checkAndAddName(name, namesLists);
}

Entity::~Entity() {
    auto target_id = std::find(idLists.begin(), idLists.end(), id);
    if (target_id != idLists.end()) {
        idLists.erase(target_id);
    }

    auto target_name = std::find(namesLists.begin(), namesLists.end(), name);
    if (target_name != namesLists.end()) {
        namesLists.erase(target_name);
    }
}

void Entity::setName(const std::string& newName) {
    if (newName == name) return;
    checkAndAddName(newName, namesLists);
    
    auto it_name = std::find(namesLists.begin(), namesLists.end(), name);
    if (it_name != namesLists.end()) {
        namesLists.erase(it_name);
    }        
    
    name = newName;
}

void Entity::setID(int newID) {
    if (newID == id) return;
    checkAndAddID(newID, idLists);
    
    auto it_id = std::find(idLists.begin(), idLists.end(), id);
    if (it_id != idLists.end()) {
        idLists.erase(it_id);
    }        
    
    id = newID;
}

void Entity::setInfo(const std::string& info) {
    addInfo = info;
}

std::string Entity::getName() const { return name; }
int Entity::getID() const { return id; }
std::string Entity::getInfo() const { return addInfo; }

const std::vector<std::string>& Entity::getAllNames() const {
    return namesLists;
}

const std::vector<int>& Entity::getAllID() const {
    return idLists;
}