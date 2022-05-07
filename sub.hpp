#pragma once
#include "event.hpp"

class subscriber
{
public:
    virtual void evaluate(const event_base& e) = 0;
};