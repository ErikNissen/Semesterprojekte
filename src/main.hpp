#ifndef NP_SEMESTERPROJEKT_MAIN_HPP
#define NP_SEMESTERPROJEKT_MAIN_HPP

#include "Warehouse.h"
#include <unistd.h>

void endlessThread(Warehouse&);

[[noreturn]] void endlessThreadHandlerIPoint( Warehouse &warehouse );

[[noreturn]] void endlessThreadHandlerKPoint( Warehouse &warehouse );



#endif //NP_SEMESTERPROJEKT_MAIN_HPP

/*

 // global Var
float i = 0;
float x = 0;
float z = 0;
int counter = 0;

 std::mutex m, mm, mmm;

 int mT() {
    std::cout << "call mainTread" << std::endl;
    { // call 2x the search to find the fastestWay
        jthread threadMain(mainThreadX);
//        jthread threadMain2(mainThreadX);
    }
    return 0;
}

void mainThreadX() {
    std::lock_guard<std::mutex> lock(m); // this func can only called be
    once in a time
    std::cout << "spawn 10 threads to search" << std::endl;
    // call 10x search
    std::jthread tm1(searchx);
    std::jthread tm2(searchx);
    std::jthread tm3(searchx);
    std::jthread tm4(searchx);
    std::jthread tm5(searchx);
    std::jthread tm6(searchx);
    std::jthread tm7(searchx);
    std::jthread tm8(searchx);
    std::jthread tm9(searchx);
    std::jthread tm10(searchx);
}

void searchx() {
//    std::lock_guard<std::mutex> lck(mm); // this func can only called be once in a time
    std::cout << "called Search" << std::endl;
    x++;
    i += x;
    i *= x;
    float y = i;
//    osyncstream(cout) << (ysc = y) << endl;
    fastesWay(y);
}

int fastesWay(float y) {
    std::lock_guard<std::mutex> lk(mmm);
//    std::cout << "calling fastesWay and Locked" << std::endl;
    if (z == 0) {
        z = y;
    } else if (z < y) {
        z = z;
    } else if (z > y) {
        z = y;
    }
    counter ++;
    if (counter == 10){
        std::cout << "search threads are done -> the values are" << std::endl;
        std::cout << "i: "  << i
             << "\nx: " << x
             << "\nz: " << z << std::endl;
        i = 0;
        x = 0;
        z = 0;
        counter = 0;
    }
}


 */