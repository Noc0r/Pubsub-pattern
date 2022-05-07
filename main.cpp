#include <iostream>
#include "sub.hpp"
#include "pub.hpp"

enum events_types : event_id
{
    test_event_id = 10,
    test_event2_id,
    test_event3_id,
};

struct args
{
    int a;
    int b;
};

class test_event : public notification<test_event_id>{};

class test_event2 : public event<args, test_event2_id>
{
public:
    test_event2(const args& a) : event<args, test_event2_id>(a)
    {}

    test_event2(args&& a) : event<args, test_event2_id>(a)
    {}
};
class test_event3 : public notification<test_event3_id>{};

class test_sub : public subscriber
{
    virtual void evaluate(const event_base& e) override
    {
        std::cout << "test_sub" << std::endl;
        switch (e.id())
        {
        case test_event_id:
            std::cout << "evaluate event1 without params" << std::endl;
            break;
        case test_event2_id:
            evaluate(&e);
            break;

        default:
            break;
        }
    }

    void evaluate(test_event2* e)
    {
        std::cout << "evaluate event with params: {" << params.a << ", " << params.b << "}" << std::endl;
    }
};

class test_sub2 : public subscriber
{
    virtual void evaluate(const event_base& e) override
    {
        std::cout << "test_sub2" << std::endl;
        switch (e.id())
        {
        case test_event_id:
            std::cout << "evaluate event1 without params" << std::endl;
            break;

        case test_event3_id:
            std::cout << "evaluate event3 without params" << std::endl;
            break;
        default:
            break;
        }
    }
};

int main()
{
    event_group group = {
        test_event_id,
        test_event2_id,
        test_event3_id
    };
    publisher p(group);
    test_sub s1;   
    p.subscribe(&s1, test_event_id);
    p.subscribe(&s1, test_event2_id);
    
    test_sub2 s2;
    p.subscribe(&s2, test_event_id);
    p.subscribe(&s2, test_event3_id);

    p.publish(test_event{});
    p.publish(test_event2{args{5, 10}});
    return 0;
}