#include <iostream>
#include <thread>
#include <mutex>

//Mutex for each tool
std::mutex mtx_hammer;
std::mutex mtx_screwdriver;
std::mutex mtx_saw;


//function for simulate work
void work(const std::string name, const std::string tool){
        std::cout<< name << " is working with " << tool << std::endl;
        for (int i = 0; i < 100000; i++);
}


void handyGuy1(){
        while (true){
                mtx_hammer.lock();
                mtx_screwdriver.lock();
                mtx_saw.lock();
                work("Handy Guy 1", "hammer");
                work("Handy Guy 1", "screwdriver");
                mtx_saw.unlock();
                mtx_screwdriver.unlock();
                mtx_hammer.unlock();
        }
}

void handyGuy2(){
        while (true){
                mtx_hammer.lock();
                mtx_screwdriver.lock();
                mtx_saw.lock();
                work("Handy Guy 2", "screwdriver");
                work("Handy Guy 2", "saw");
                mtx_saw.unlock();
                mtx_screwdriver.unlock();
                mtx_hammer.unlock();
        }
}

void handyGuy3(){
        while (true){
                mtx_hammer.lock();
                mtx_screwdriver.lock();
                mtx_saw.lock();
                work("Handy Guy 3", "saw");
                work("Handy Guy 3", "hammer");
                mtx_saw.unlock();
                mtx_screwdriver.unlock();
                mtx_hammer.unlock();
        }
}


int main(){
        //creating threads for each handy guy
        std::thread t1(handyGuy1);
        std::thread t2(handyGuy2);
        std::thread t3(handyGuy3);

        //Joining threads to the main thread
        t1.join();
        t2.join();
        t3.join();

        return 0;
}


// To prevent deadlock, all threads lock mutexes in the same fixed order: hammer -> screwdriver -> saw.
// Even if a thread does not use a certain tool, it still locks and unlocks it to maintain consistent lock order.
// This ensures there is no circular wait and guarantees deadlock-free execution.
