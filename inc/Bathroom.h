#pragma once
#include "Function_pool.h"
#include <thread>
#include <functional>
#include <iostream>

enum state
{
    male,
    female,
    empty
};

class Bathroom
{    
    private:
    Function_pool male_queue;
    Function_pool female_queue;
    std::vector<std::thread> thread_pool;
    state current;
    uint64_t num_threads;

    public:
    Bathroom(uint64_t threads);

    void clear_bathroom();
    void start_bathroom();
    void spawn(std::function<void()> func);

    //state get_state();
};