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

void workload()
{
    int random = rand()%10;
    printf("A person will use the bathroom for %d seconds\n", random);
    std::this_thread::sleep_for(std::chrono::seconds(random));
    printf("A person exited the bathroom\n");
}

void spawn_persons()
{
    while (true)
    {    
        std::this_thread::sleep_for(std::chrono::seconds(30));
        bathroom.spawn(workload);
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
 
    bathroom.spawn(workload);
    bathroom.start_bathroom();
    std::thread gen (spawn_persons);

    while (true)
    {
        switch (bathroom.get_current_state())
        {
        case female:
            if( (bathroom.get_male_queue_size() > num_threads) && (bathroom.get_male_queue_size() > bathroom.get_female_queue_size()) )
            {
                printf("#####################################\n");
                printf("\tSwitching state female to male\n");
                printf("\t%" PRIu64 " men in queue\n",bathroom.get_male_queue_size());
                printf("\t%" PRIu64 " women in queue\n", bathroom.get_female_queue_size());
                printf("#####################################\n");
                bathroom.set_current_state(male);
            }
            if( (bathroom.get_male_queue_size() != 0) && (bathroom.get_female_queue_size() == 0) )
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
            if( (bathroom.get_female_queue_size() > num_threads) && (bathroom.get_female_queue_size() > bathroom.get_male_queue_size()) )
            {
                printf("#####################################\n");
                printf("\tSwitching state male to female\n");
                printf("\t%" PRIu64 " men in queue\n",bathroom.get_male_queue_size());
                printf("\t%" PRIu64 " women in queue\n", bathroom.get_female_queue_size());
                printf("#####################################\n");
                bathroom.set_current_state(female);
            }
            if( (bathroom.get_female_queue_size() != 0) && (bathroom.get_male_queue_size() == 0) )
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