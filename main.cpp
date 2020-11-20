#include <iostream>
#include <cmath>
#include <string>



float pointLoad [10] [2]; //pointLoad array is used to store forces acting on a beam
float distributedLoad [5] [2]; //distributedLoad array is used to store distributed load, where magnitude per length is stored (N/m) and length of acting
float beamLength; //Length of a beam


 
    void getBeamLength(){ //Gets length of a beam and checks if the inputted value is valid
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
    else {
 
        flag = true;
        beamLength = length;
    }
    }
    }





bool lengthCheck (float distance){  //function to check if distance of a force is valid
    if (distance > beamLength || distance < 0)
        return false;
    else 
        return true;
}

void forceInput (){
    bool lengthCheckFlag = false;
    bool directionFlag = false;
    bool magnitudeFlag = false;
    bool initialFlag = false;
    bool answerFlag = false;
    std::string usersAnswer; 

    while (!initialFlag){
    
    std::cout << "Any point loads for Your beam? (Yes/No)" << std::endl;
    std::cin >> usersAnswer;

    if (usersAnswer == "Yes"){

    int i = 0; //i is used to fill the array with forces
    std::string upOrDown;
    while (usersAnswer == "Yes"){
        
        while (!magnitudeFlag){
        std::cout << "Enter force magnitude: "; //User is asked to enter magnitude of a force
        std::cin >> pointLoad [i] [0];
        if (pointLoad [i] [0] > 0)

                magnitudeFlag = true;

        else{
            std::cout << "ERROR: INVALID INPUT" << std::endl;
            std::cout << "Please try again" << std::endl << std::endl;
        }
        }
        magnitudeFlag = false;
        
        while (!directionFlag){
        std::cout << "Direction of the force (Up/Down): "; //Direction is used to calculate moment later
        std::cin >> upOrDown;
        if (upOrDown == "Down"){
            pointLoad [i] [0] = pointLoad [i] [0] * (-1);
            directionFlag = true;
        }
        else if (upOrDown == "Up"){
            directionFlag = true;
        }
        else{
            std::cout << std::endl <<"ERROR: INVALID INPUT" << std::endl;
            std::cout << "Please try again" << std::endl << std::endl;
        }
        }

        directionFlag = false;

        while (!lengthCheckFlag){  //That block of code prompts user to input distance from the left edge of a beam and checks if the value is valid
        std::cout << std::endl << "Distance from the left edge: ";
        std::cin >> pointLoad [i] [1];

        lengthCheckFlag = lengthCheck(pointLoad [i] [1]);
        
        if(!lengthCheckFlag){
            std::cout << std::endl << "INVALID INPUT" << std::endl;
            std::cout << "Please try again" << std::endl << std::endl;
        }
        else 
            lengthCheckFlag = true;
        }

        i++;
        lengthCheckFlag = false;

        while (!answerFlag){
        std::cout << "More point loads to add? (Yes/No): "; //Checks if more forces expected for input
        std::cin >> usersAnswer;
        std::cout << std::endl;
        if (usersAnswer == "No"){
        std::cout << "Proceeding to distributed load...";
        answerFlag = true;
        }
        else if (usersAnswer == "Yes"){
            answerFlag = true;
        }
        else if (usersAnswer != "Yes" && usersAnswer != "No"){
        std::cout << std::endl << "INVALID INPUT" << std::endl;
        std::cout << "Please try again" << std::endl << std::endl;
        }
        }

        answerFlag = false;
        initialFlag = true;
    }
        }
       else if (usersAnswer == "No"){
            initialFlag = true;
            std::cout << std::endl << "Proceeding to distributed load...";
       }

       else {
           std::cout << std::endl <<"INVALID INPUT" << std::endl;
           std::cout << "Please try again" << std::endl << std::endl;
       }
    }
}

void distributedInput(){

}



int main(){

    getBeamLength();

    forceInput();

    return 0;
}