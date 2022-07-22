#include "Function_pool.h"
#include "Bathroom.h"

#include <stdio.h>
#include <inttypes.h>

#include <cstdlib>
#include <functional>
#include <string>
#include <iostream>
#include <mutex>
#include <functional>
#include <thread>
#include <vector>

Bathroom bathroom;   

void workload_men()
{
    int random = rand()%10;
    printf("A men will use the bathroom for %d seconds\n", random);
    std::this_thread::sleep_for(std::chrono::seconds(random));
    printf("A men exited the bathroom\n");
}

void workload_women()
{
    int random = rand()%10;
    printf("A women will use the bathroom for %d seconds\n", random);
    std::this_thread::sleep_for(std::chrono::seconds(random));
    printf("A women exited the bathroom\n");
}

void spawn_persons()
{
    while (true)
    {    
        bathroom.spawn(workload_men, workload_women);
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
}

int main()
{
    std::cout << "stating operation" << std::endl;
    std::cout << "Number of threads: ";
    unsigned int num_threads;
    std::cin >> num_threads;
    std::cout << "number of threads = " << num_threads << std::endl;
    bathroom.set_num_thread(num_threads);

    std::thread gen (spawn_persons);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    bathroom.start_bathroom();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        uint64_t male_queue_size = bathroom.get_male_queue_size();
        uint64_t female_queue_size = bathroom.get_female_queue_size();
        switch (bathroom.get_current_state())
        {
        case female:
            if( (male_queue_size > num_threads) && (male_queue_size > female_queue_size) )
            {
                printf("#####################################\n");
                printf("\tSwitching state female to male\n");
                printf("\t%" PRIu64 " men in queue\n",bathroom.get_male_queue_size());
                printf("\t%" PRIu64 " women in queue\n", bathroom.get_female_queue_size());
                printf("#####################################\n");
                bathroom.set_current_state(male);
            }
            if( (male_queue_size!= 0) && (female_queue_size == 0) )
            {
                printf("#####################################\n");
                printf("\tSwitching state female to male\n");
                printf("\t%" PRIu64 " men in queue\n",bathroom.get_male_queue_size());
                printf("\t%" PRIu64 " women in queue\n", bathroom.get_female_queue_size());
                printf("#####################################\n");
                bathroom.set_current_state(male);
            }
            break;

        case male:
            if( (female_queue_size > num_threads) && (female_queue_size > male_queue_size) )
            {
                printf("#####################################\n");
                printf("\tSwitching state male to female\n");
                printf("\t%" PRIu64 " men in queue\n",bathroom.get_male_queue_size());
                printf("\t%" PRIu64 " women in queue\n", bathroom.get_female_queue_size());
                printf("#####################################\n");
                bathroom.set_current_state(female);
            }
            if( (female_queue_size != 0) && (male_queue_size == 0) )
            {
                printf("#####################################\n");
                printf("\tSwitching state male to female\n");
                printf("\t%" PRIu64 " men in queue\n",bathroom.get_male_queue_size());
                printf("\t%" PRIu64 " women in queue\n", bathroom.get_female_queue_size());
                printf("#####################################\n");
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