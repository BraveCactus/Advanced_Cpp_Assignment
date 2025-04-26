#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include <vector>
#include <string>
#include "entity.h"
#include "user.h"

class Group : public Entity, public std::enable_shared_from_this<Group> {
    std::vector<std::shared_ptr<User>> usersList;
    
public:
    Group();
    Group(const std::string& groupName);
    Group(const std::string& groupName, int groupID, const std::string& groupInfo = "_");
    
    ~Group() override;
    
    void addUser(std::shared_ptr<User> user);
    void removeUser(std::shared_ptr<User> user);
    const std::vector<std::shared_ptr<User>>& getUsers() const;
    void printInfo();
};

#endif // GROUP_H