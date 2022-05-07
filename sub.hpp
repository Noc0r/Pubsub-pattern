#pragma once
#include "event.hpp"

class subscriber
{
public:
    virtual void evaluate(event_base* e) = 0;
};