#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include "functions.h"

struct pointLoad {

    float Magnitude; 
    float distanceLeft;
    int direction;   

};

struct distributedLoad {

    float Magnitude; 
    float startLeft;
    float endLeft;
    int direction;   

};

struct pointLoad Storage1 [10];

struct distributedLoad Storage2 [3]; //distributedLoad array is used to store distributed load, where magnitude per length is stored (kN/m) and length of acting

float beamLength; //Length of a beam
//For point loads 1st column is used to save magnitude of a force, 2nd is for distance from left edge of a beam, and 3rd is used to define direction (up or down)
//For distributed loads 1st column is used to save magnitude of a load, 2nd is a starting point of a load, 3rd is an ending point of a load and 4th is used to define direction (up or down)
float leftSupport, rightSupport;

int pointLoadCounter = 0;
int distributedLoadCounter = 0;
 
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
        std::cin >> Storage1[i].Magnitude;
        if (Storage1[i].Magnitude > 0)

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

        directionPointCheck(upOrDown, directionFlag, Storage1[i].direction);
        }

        directionFlag = false;

        while (!lengthCheckFlag){  //That block of code prompts user to input distance from the left edge of a beam and checks if the value is valid
        std::cout << std::endl << "Distance from the left edge: ";
        std::cin >> Storage1[i].distanceLeft;

        lengthCheckFlag = lengthCheck(Storage1[i].distanceLeft, beamLength);
        
        if(!lengthCheckFlag){
            std::cout << std::endl << "INVALID INPUT" << std::endl;
            std::cout << "Please try again" << std::endl << std::endl;
        }
        else 
            lengthCheckFlag = true;
        }

        i++;
        pointLoadCounter++;

        lengthCheckFlag = false;

        while (!answerFlag){
        std::cout << "More point loads to add? (Yes/No): "; //Checks if more forces expected for input
        std::cin >> usersAnswer;
        std::cout << std::endl;
        
        pointLoadsCheck (usersAnswer, answerFlag);
        }

        answerFlag = false;
        initialFlag = true;
    }
        }
        else if (usersAnswer == "No"){
            
        }
    }
}

void distributedInput(){
    bool directionFlag = false;
    bool magnitudeFlag = false;
    bool initialFlag = false;
    bool answerFlag = false;
    bool loadLengthFlag1 = false;
    bool loadLengthFlag2 = false;
    std::string usersAnswer; 
    std::string upOrDown;

    while (!initialFlag){
    
    std::cout << std::endl <<"Any distributed loads for Your beam? (Yes/No)" << std::endl;
    std::cin >> usersAnswer;

    if (usersAnswer == "Yes"){

    int i = 0; //i is used to fill the array with forces
    float loadPerDistance;

    while (usersAnswer == "Yes"){
        
        while(!magnitudeFlag){

        std::cout << "Enter kN/m for Your load: "; //User is asked to enter magnitude of a force
        std::cin >> loadPerDistance;
        if ( loadPerDistance > 0)

            //
            magnitudeFlag = true;

        else{
            std::cout << "ERROR: INVALID INPUT" << std::endl;
            std::cout << "Please try again" << std::endl << std::endl;
        }
        }
        magnitudeFlag = false;

        while (!loadLengthFlag1){
        std::cout << "Starting point (in meters, from left edge of a beam):"; //Direction is used to calculate moment later
        std::cin >> Storage2[i].startLeft;
            loadLengthFlag1 = lengthCheck (Storage2[i].startLeft, beamLength);

        if (loadLengthFlag1){
            while (!loadLengthFlag2){
            std::cout << "Ending point (in meters, from left edge of a beam):"; //Direction is used to calculate moment later
            std::cin >> Storage2[i].endLeft;
            
            loadLengthFlag2 = lengthCheck (Storage2[i].endLeft, beamLength);
            if (loadLengthFlag2 && Storage2[i].endLeft > Storage2[i].startLeft){
                loadLengthFlag2 = true;
            }
            else if (loadLengthFlag2){
                std::cout << std::endl <<"Inputted distance should be bigger than "<< Storage2[i].startLeft<< "." << std::endl;
                std::cout << "Please try again" << std::endl << std::endl;
                loadLengthFlag2 = false;
            }
            else {
                std::cout << "ERROR: INVALID INPUT" << std::endl;
                std::cout << "Please try again" << std::endl << std::endl;
            }
        }
        }
        else {
            std::cout << "ERROR: INVALID INPUT" << std::endl;
            std::cout << "Please try again" << std::endl << std::endl;
        }
        }

        loadLengthFlag1 = false;
        loadLengthFlag2 = false;

        Storage2[i].Magnitude = loadPerDistance * (Storage2[i].endLeft - Storage2[i].startLeft);

        while (!directionFlag){
        std::cout << "Direction of the force (Up/Down): "; //Direction is used to calculate moment later
        std::cin >> upOrDown;
        if (upOrDown == "Down"){
            Storage2[i].direction = -1;
            directionFlag = true;
        }
        else if (upOrDown == "Up"){
            Storage2[i].direction = 1;
            directionFlag = true;
        }
        else{
            std::cout << std::endl <<"ERROR: INVALID INPUT" << std::endl;
            std::cout << "Please try again" << std::endl << std::endl;
        }
        }

        directionFlag = false;

        i++;
        distributedLoadCounter++;
    
        while (!answerFlag){
        std::cout << "More distributed loads to add? (Yes/No): "; //Checks if more forces expected for input
        std::cin >> usersAnswer;
        std::cout << std::endl;
        if (usersAnswer == "No"){
        std::cout << "Proceeding to results"<<std::endl;
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

void supportsInput(){
    std::cout << "Left support (from left edge of the beam in meters):";
    std::cin >> leftSupport;
    
    //later functionality to detect whether it is a cantilever or a simply supported beam to be added

    std::cout << "Right support (from left edge of the beam in meters):";
    std::cin >> rightSupport;
}


void calculations(){

    double Moment = 0;
    double Load = 0;
//I define positive moment as one that rotates CCW
    for (int i = 0; i < pointLoadCounter; i++){
        if (Storage1[i].distanceLeft < leftSupport){
            Moment += (-1 * (leftSupport - Storage1[i].distanceLeft) * Storage1[i].Magnitude * Storage1[i].direction);
            Load += (Storage1[i].Magnitude * Storage1[i].direction);
            
        }
        else if (Storage1[i].distanceLeft > leftSupport){
            Moment += ((Storage1[i].distanceLeft - leftSupport) * Storage1[i].Magnitude * Storage1[i].direction);
            Load += (Storage1[i].Magnitude * Storage1[i].direction);
        }

    }

    for (int i = 0; i < distributedLoadCounter; i++ ){

        float lengthOfLoad = Storage2[i].endLeft - Storage2[i].startLeft;//It is critical to have actual distance of the distributed load, because it will be used later to calculate moment
        float distanceToCenter = Storage2[i].startLeft + lengthOfLoad/2;

        if (distanceToCenter < leftSupport){
            Moment += (-1* Storage2[i].Magnitude * (leftSupport - distanceToCenter) * Storage2[i].direction);
            Load += (Storage2[i].Magnitude * Storage2[i].direction);
        }

        else if (distanceToCenter > leftSupport){
            Moment += (Storage2[i].Magnitude * (distanceToCenter - leftSupport) * Storage2[i].direction);
            Load += (Storage2[i].Magnitude * Storage2[i].direction);
        }
    }
    //Since moment around left support is known now, reaction force for right support can be easily solved: 0 = Moment - 
    float rightReactionForce, leftReactionForce;
    
    if (Moment > 0){
        rightReactionForce = Moment/(rightSupport - leftSupport);
    }
    else if (Moment < 0){
        rightReactionForce = -1 * (Moment/(rightSupport - leftSupport));
    }
  
    if (Load > 0){
    leftReactionForce = Load - rightReactionForce;
    }
    else if (Load < 0){
        leftReactionForce = abs(Load) - rightReactionForce;
    }
     output (rightReactionForce, leftReactionForce);
}

int main(){

    getBeamLength();

    forceInput();

    distributedInput();

    supportsInput();

    calculations();

    return 0;

}