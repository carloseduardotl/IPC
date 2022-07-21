#include "Function_pool.h"
#include "Bathroom.h"
#include <cstdlib>
#include <functional>
#include <string>
#include <iostream>
#include <mutex>
#include <functional>
#include <thread>
#include <vector>


void workload()
{
    int random = rand()%10;
    //std::cout << "A person will use the bathroom for " << random << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(random));
    //std::cout << "A person exited the bathroom" << std::endl;
}

/*void spawn_persons(std::function<void() > spawn, std::function<void()> workload)
{
    std::this_thread::sleep_for(std::chrono::seconds(30));
    //spawn(workload);
}*/

int main()
{
    std::cout << "stating operation" << std::endl;
    unsigned int num_threads = 5;
    std::cout << "number of threads = " << num_threads << std::endl;

    Bathroom bathroom(num_threads);    
    bathroom.spawn(workload);
    bathroom.start_bathroom();
    //std::thread gen (spawn_persons, bathroom.spawn, workload);

    while (true)
    {
        switch (bathroom.get_current_state())
        {
        case female:
            if( (bathroom.get_male_queue_size() > num_threads) && (bathroom.get_male_queue_size() > bathroom.get_female_queue_size()) )
            {
                std::cout << "switching state female to male" << std::endl;
                std::cout << bathroom.get_male_queue_size() << " men in queue" << std::endl;
                std::cout << bathroom.get_female_queue_size() << " women in queue" << std::endl;
                bathroom.set_current_state(male);
            }
            if( (bathroom.get_male_queue_size() != 0) && (bathroom.get_female_queue_size() == 0) )
            {

                std::cout << "switching state female to male" << std::endl;
                std::cout << bathroom.get_male_queue_size() << " men in queue" << std::endl;
                std::cout << bathroom.get_female_queue_size() << " women in queue" << std::endl;
                bathroom.set_current_state(male);
            }
            break;

        case male:
            if( (bathroom.get_female_queue_size() > num_threads) && (bathroom.get_female_queue_size() > bathroom.get_male_queue_size()) )
            {

                std::cout << "switching state male to female" << std::endl;
                std::cout << bathroom.get_male_queue_size() << " men in queue" << std::endl;
                std::cout << bathroom.get_female_queue_size() << " women in queue" << std::endl;
                bathroom.set_current_state(female);
            }
            if( (bathroom.get_female_queue_size() != 0) && (bathroom.get_male_queue_size() == 0) )
            {

                std::cout << "switching state male to female" << std::endl;
                std::cout << bathroom.get_male_queue_size() << " men in queue" << std::endl;
                std::cout << bathroom.get_female_queue_size() << " women in queue" << std::endl;
                bathroom.set_current_state(female);
            }
            break;
        default:
            break;
        }
    }
    

    bathroom.clear_bathroom();

    return 0;
}