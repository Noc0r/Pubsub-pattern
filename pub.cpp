#include "pub.hpp"

publisher::publisher(const event_group& group)
{
    for (event_id id : group)
        _topics.insert({id, {}});
}

void publisher::subscribe(subscriber* sub, event_id topic_id)
{
    std::lock_guard<std::mutex> g(_mutex);
    auto topic = _topics.find(topic_id);
    if (topic == _topics.end())
        throw std::runtime_error("wrong topic_id");

    topic->second.insert(sub);
}

void publisher::unsubscribe(subscriber* sub, event_id topic_id)
{
    std::lock_guard<std::mutex> g(_mutex);
    auto topic = _topics.find(topic_id);
    if (topic == _topics.end())
        throw std::runtime_error("wrong topic_id");
        
    topic->second.erase(sub);
}

void publisher::publish(const event_base& e)
{
    std::lock_guard<std::mutex> g(_mutex);
    auto topic = _topics.find(e.id());
    if (topic == _topics.end())
        throw std::runtime_error("this event not supported");
    
    /// Call all subs
    /// if io_context present (for example p2p::hub) then post it instead
    for (auto sub : topic->second)
        sub->evaluate(e);
}