#include "Bathroom.h"

Bathroom::Bathroom(uint64_t threads)
{
    current = empty;
    num_threads = threads;
}

void Bathroom::clear_bathroom()
{
    switch (current)
    {
    case male:
        male_queue.done();
        break;
    case female:
        female_queue.done();
        break;
    default:
        break;
    }
    for (unsigned int i = 0; i < thread_pool.size(); i++)
    {
        thread_pool.at(i).join();
    }
    thread_pool.clear();
}

void Bathroom::start_bathroom()
{
    uint64_t male_size = male_queue.get_queue_size();
    uint64_t female_size = female_queue.get_queue_size();
    uint64_t i;

    if(male_size > female_size){
        std::cout << "Male time" << std::endl;
        for (i = 0; i < num_threads; i++) thread_pool.push_back(std::thread(&Function_pool::infinite_loop_func, &male_queue));
        current = male;
    }
    else{
        std::cout << "Female time" << std::endl;
        for (i = 0; i < num_threads; i++) thread_pool.push_back(std::thread(&Function_pool::infinite_loop_func, &female_queue));
        current = female;
    }
}

void Bathroom::spawn(std::function<void()> func)
{
    srand(time(0));
    volatile int male, female;
    male = rand()%20;
    female = rand()%20;

    for(int i=0; i< male; i++) male_queue.push(func);
    for(int i=0; i< female; i++) female_queue.push(func);

    std::cout << "Spawned " << male << " men and " << female << " women" << std::endl;
}