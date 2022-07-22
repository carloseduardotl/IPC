#pragma once
#include "Function_pool.h"
#include <thread>
#include <functional>
#include <stdint.h>

enum state
{
    male,
    female,
    initial
};

class Bathroom
{    
    private:
    Function_pool male_queue;
    Function_pool female_queue;
    std::vector<std::thread> thread_pool;
    state current_state;
    uint64_t num_threads;

    public:
    Bathroom();

    void clear_bathroom();
    void start_bathroom();
    void spawn(std::function<void()> func);

    uint64_t get_male_queue_size();
    uint64_t get_female_queue_size();

    void set_current_state(state future_state);
    state get_current_state();

    void set_num_thread(uint64_t threads);
};