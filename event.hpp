#pragma once
#include <cstdint>
#include <functional>

using event_id = uint32_t;

class event_base
{
public:
    event_base(event_id id)
    :   _id(id)
    {}
    virtual ~event_base() {}

    event_id id() const { return _id; };

protected:
    event_id _id;
};

template <event_id ID>
class notification : public event_base
{
public:
    notification() : event_base(ID)
    {}
};

template <class paramType, event_id ID>
class event : public notification<ID>
{
public:
    event(const paramType& params)
    :   _params(params)
    {}

    event(paramType&& params)
    :   _params(std::move(params))
    {}

    const paramType &params() const { return _params; }

private:
    paramType _params;
    
};