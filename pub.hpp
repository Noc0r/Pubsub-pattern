#pragma once
#include "sub.hpp"
#include <set>
#include <map>
#include <mutex>

using event_group = std::set<event_id>;

class publisher
{
public:
    publisher(const event_group& group);
    void subscribe(subscriber* sub, event_id topic);
    void unsubscribe(subscriber* sub, event_id topic);
    void publish(const event_base &e);

private:
    std::mutex                                  _mutex;
    std::map<event_id, std::set<subscriber *>>  _topics;
};