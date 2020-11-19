#ifndef LENGTH_H_INCLUDED
#define LENGTH_H_INCLUDED

#include <iostream>

float getBeamLength(){ //Gets length of a beam and checks if the inputted value is valid
    bool flag = false;
    float length;

    while(!flag){
    std::cout << "Please enter length of the beam in meters: ";
    std::cin >> length;
    std::cout << std::endl;

    if (length <= 0){
        std::cout << std::endl <<"INAVLID INPUT" << std::endl;
        std::cout << "Please try again"<< std::endl;
    }
    else 
        flag = true;
    }
    
    return length; 
}



#endif