#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>



float pointLoad [10] [3]; //pointLoad array is used to store forces acting on a beam
float distributedLoad [3] [4]; //distributedLoad array is used to store distributed load, where magnitude per length is stored (kN/m) and length of acting
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
            pointLoad [i] [2] = -1;
            directionFlag = true;
        }
        else if (upOrDown == "Up"){
            directionFlag = true;
            pointLoad [i] [2] = 1;
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
        pointLoadCounter++;

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
        std::cin >> distributedLoad [i] [1];
            loadLengthFlag1 = lengthCheck (distributedLoad [i] [1]);

        if (loadLengthFlag1){
            while (!loadLengthFlag2){
            std::cout << "Ending point (in meters, from left edge of a beam):"; //Direction is used to calculate moment later
            std::cin >> distributedLoad [i] [2];
            
            loadLengthFlag2 = lengthCheck (distributedLoad [i] [2]);
            if (loadLengthFlag2 && distributedLoad [i] [2] > distributedLoad[i] [1]){
                loadLengthFlag2 = true;
            }
            else if (loadLengthFlag2){
                std::cout << std::endl <<"Inputted distance should be bigger than "<< distributedLoad[i] [1] << "." << std::endl;
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

        distributedLoad [i] [0] = loadPerDistance * (distributedLoad [i] [2] - distributedLoad [i] [1] );

        while (!directionFlag){
        std::cout << "Direction of the force (Up/Down): "; //Direction is used to calculate moment later
        std::cin >> upOrDown;
        if (upOrDown == "Down"){
            distributedLoad [i] [3] = -1;
            directionFlag = true;
        }
        else if (upOrDown == "Up"){
            distributedLoad [i] [3] = 1;
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
        if (pointLoad [i] [1] < leftSupport){
            Moment += (-1 * (leftSupport - pointLoad [i] [1]) * pointLoad [i] [0] * pointLoad [i] [2]);
            Load += (pointLoad [i] [0] * pointLoad [i] [2]);
            
        }
        else if (pointLoad [i] [1] > leftSupport){
            Moment += ((pointLoad [i] [1] - leftSupport) * pointLoad [i] [0] * pointLoad [i] [2]);
            Load += (pointLoad [i] [0] * pointLoad [i] [2]);
        }

    }

    for (int i = 0; i < distributedLoadCounter; i++ ){

        float lengthOfLoad = distributedLoad [i] [2] - distributedLoad [i] [1];//It is critical to have actual distance of the distributed load, because it will be used later to calculate moment
        float distanceToCenter = distributedLoad [i] [1] + lengthOfLoad/2;

        if (distanceToCenter < leftSupport){
            Moment += (-1* distributedLoad [i] [0] * (leftSupport - distanceToCenter) * distributedLoad [i] [3]);
            Load += (distributedLoad [i] [0] * distributedLoad [i] [3]);
        }

        else if (distanceToCenter > leftSupport){
            Moment += (distributedLoad [i] [0] * (distanceToCenter - leftSupport) * distributedLoad [i] [3]);
            Load += (distributedLoad [i] [0] * distributedLoad [i] [3]);
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

    if (rightReactionForce > 0){
    std::cout <<"The rection force at right support is: "<< std::fixed << std::setprecision(2) << abs(rightReactionForce)<< "kN"<<" Upwards"<< std::endl;
    }
    else if (rightReactionForce < 0){
        std::cout <<"The rection force at right support is: "<< std::fixed << std::setprecision(2)<< abs(rightReactionForce)<< "kN"<<" Downwards"<< std::endl;
    }
    if (leftReactionForce > 0){
    std::cout <<"The rection force at left support is: "<< std::fixed << std::setprecision(2)<< abs(leftReactionForce)<< "kN"<<" Upwards"<< std::endl;
    }
    else if (leftReactionForce < 0){
        std::cout <<"The rection force at left support is: "<< std::fixed << std::setprecision(2)  << abs(leftReactionForce)<< "kN"<<" Downwards"<< std::endl;
    }
}
int main(){

    getBeamLength();

    forceInput();

    distributedInput();

    supportsInput();

    calculations();

    return 0;

}