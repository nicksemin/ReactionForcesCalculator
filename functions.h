#include <iostream>
#include <iomanip>
#include <cmath>

void directionPointCheck (std::string answer, bool& flag, int& direction){

    if (answer == "Down"){
            direction = -1;
            flag = true;
        }
        else if (answer == "Up"){
            flag = true;
            direction = 1;
        }
        else{
            std::cout << std::endl <<"ERROR: INVALID INPUT" << std::endl << "Please try again" << std::endl << std::endl;
        }
        }

        void pointLoadsCheck (std::string answer, bool& flag){
        std::cout << "More point loads to add? (Yes/No): "; //Checks if more forces expected for input
        std::cin >> answer;
        std::cout << std::endl;
        if (answer == "No"){
        std::cout << "Proceeding to distributed load...";
        flag = true;
        }
        else if (answer == "Yes"){
            flag = true;
        }
        else if (answer != "Yes" && answer != "No"){
       std::cout << std::endl <<"ERROR: INVALID INPUT" << std::endl << "Please try again" << std::endl << std::endl;
        }
        }

        void output (float rightForce, float leftForce){
    
    if (rightForce > 0){
    std::cout <<"The rection force at right support is: "<< std::fixed << std::setprecision(2) << abs(rightForce)<< "kN"<<" Upwards"<< std::endl;
    }

    else if (rightForce < 0){
        std::cout <<"The rection force at right support is: "<< std::fixed << std::setprecision(2)<< abs(rightForce)<< "kN"<<" Downwards"<< std::endl;
    }

    if (leftForce > 0){
    std::cout <<"The rection force at left support is: "<< std::fixed << std::setprecision(2)<< abs(leftForce)<< "kN"<<" Upwards"<< std::endl;
    }

    else if (leftForce < 0){
        std::cout <<"The rection force at left support is: "<< std::fixed << std::setprecision(2)  << abs(leftForce)<< "kN"<<" Downwards"<< std::endl;
    }
    
    }

    bool lengthCheck (float distance, float length){  //function to check if distance of a force is valid
    if (distance > length || distance < 0)
        return false;
    else 
        return true;
}