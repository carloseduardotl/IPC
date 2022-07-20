#include "Function_pool.h"
#include <cstdlib>
#include <functional>
#include <string>
#include <iostream>
#include <mutex>
#include <functional>
#include <thread>
#include <vector>

enum state
{
    male,
    female,
    empty
};

typedef struct bathroom
{
    Function_pool male_queue;
    Function_pool female_queue;
    std::vector<std::thread> thread_pool;
    state current;
} bathroom;

//Function_pool func_pool;

void clear_bathroom(bathroom * room)
{
    room->male_queue.done();
    for (unsigned int i = 0; i < room->thread_pool.size(); i++)
    {
        room->thread_pool.at(i).join();
    }
    room->thread_pool.clear();
}

void spawn(bathroom * room, std::function<void()> func)
{
    srand(time(0));
    volatile int male, female;
    male = rand()%20;
    female = rand()%20;

    for(int i=0; i< male; i++) room->male_queue.push(func);
    for(int i=0; i< female; i++) room->female_queue.push(func);

    std::cout << "Spawned " << male << " men and " << female << " women" << std::endl;
}

void example_function()
{
    int ran;
    ran = rand()%10;
    //std::cout << "Person entered the bathroom, using for " << ran << " seconds" << std::endl;
    //std::this_thread::sleep_for(std::chrono::seconds(ran));
    std::cout << "Person exited" << std::endl;
}

void workload()
{
    int random = rand()%10;
    std::cout << "A person will use the bathroom for " << random << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(random));
    std::cout << "A person exited the bathroom" << std::endl;
}


int main()
{
    bathroom room;
    std::cout << "stating operation" << std::endl;
    int num_threads = 5; //std::thread::hardware_concurrency();
    std::cout << "number of threads = " << num_threads << std::endl;
    //std::vector<std::thread> thread_pool;
    /*for (int i = 0; i < 50; i++)
    {
        room.male_queue.push(example_function);
        //std::cout << "queue line: " << func_pool.get_queue_size() << std::endl;
    }*/
    spawn(&room, workload);
    for (int i = 0; i < num_threads; i++)
    {
        room.thread_pool.push_back(std::thread(&Function_pool::infinite_loop_func, &room.male_queue));
    }
    //here we should send our functions
    clear_bathroom(&room);
    /*
    room.male_queue.restart();
    room.male_queue.push(nunca_executar);
    room.male_queue.push(nunca_executar);
    room.male_queue.push(nunca_executar);
    room.male_queue.push(nunca_executar);
    room.male_queue.push(nunca_executar);
    std::cout << "Thread pool size: " << room.thread_pool.size() << std::endl;
    std::cout << "queue line: " << room.male_queue.get_queue_size() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for (int i = 0; i < 5; i++)
    {
        room.thread_pool.push_back(std::thread(&Function_pool::infinite_loop_func, &room.male_queue));
    }
    std::cout << "Thread pool size: " << room.thread_pool.size() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    clear_bathroom(&room);
    */
}