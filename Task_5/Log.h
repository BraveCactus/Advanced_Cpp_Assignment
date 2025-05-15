#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <iostream>

//Уровни важности сообщений 
enum LogLevel{
    LOG_NORMAL,
    LOG_WARNING,
    LOG_ERROR
};

struct Event{
    std::time_t time;
    LogLevel level;
    std::string msg;
};

class Log{
private:    
    std::vector<Event> events;
    static const size_t MAX_REMEMBERED_EVENTS = 10;

public:
    // Получение единственного экземпляра логгера
    static Log* Instance();

    void message(const LogLevel level, const std::string& msg);

    void print() const;

    // Для выполнения условий паттерна Sigleton запрещаем копирование и присвоение
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

};