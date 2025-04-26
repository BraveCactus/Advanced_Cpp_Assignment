#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class Entity {
protected:
    std::string name;
    int id = 0;
    std::string addInfo;
    inline static std::vector<int> idLists;
    inline static std::vector<std::string> namesLists;

    void checkAndAddID(int new_id, std::vector<int>& list);
    void checkAndAddName(const std::string& new_name, std::vector<std::string>& list);

public:
    Entity();
    Entity(const std::string& initialName);
    Entity(const std::string& initialName, int identifier, const std::string& info = "_");
    
    virtual ~Entity();

    void setName(const std::string& newName);
    void setID(int newID);
    void setInfo(const std::string& info);

    std::string getName() const;
    int getID() const;
    std::string getInfo() const;
    const std::vector<std::string>& getAllNames() const;
    const std::vector<int>& getAllID() const;
};

#endif 