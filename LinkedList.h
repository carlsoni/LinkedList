// ASU CSE310 Fall 2022 Assignment #1
// Name: Ian Carlson
// ASU ID:1223065376
// Emails: imcarls1@asu.edu    iancarlson0599@gmail.com
// Description: This header file contains the data and the functions related to 
//          the Car storage program using a Linked List Data Structure. It includes 
//          a constructor, destructor, and functions that relate to adding, removing,
//          finding, and modifying the data within a car object. 
//          

#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;

//Car represents a Car information
struct Car
{
    string model, make;
    int vin;            //vehicle identification number
    double price;
    struct Car* next;
};

//class LinkedList will contains a linked list of Cars
class LinkedList
{
private:
    struct Car* head;
    int carCount; // car count varible to keep track of the number of cars
public:
    LinkedList();
    ~LinkedList();
    bool findCar(int aVin);
    bool addCar(string model, string make, int vin, double price);
    bool removeByVin(int aVin);
    bool removeByModelAndMake(string model, string make);
    bool changeCarInfo(int aVin, string newModelAndMake);
    bool updateCarPrice(int aVin, double newPrice);
    void printCarListByMake(string make);
    void printCarList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = NULL;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    head = NULL;
    cout << "The number of deleted Car is: " << this->carCount;
    this->carCount = 0;
}

//A function to identify if the parameterized Car is inside the LinkedList or not.
//Return true if it exists and false otherwise.

//This works 
bool LinkedList::findCar(int aVin)
{
    Car* current = head;

    // checks all the cars within the List by vin number 
    if(head->vin == aVin){
        return true;
    }
    while(current != NULL){
        if(current->vin == aVin){
            return true;                // returns true when found
        }
        current = current->next;
    }
    return false;
}

//Creates a new Car and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of Cars by their make and model, i.e.
//first by make, if two cars have same makes, then we will list them by model. Note: each Car
//has a unique vin, the vehicle identification number, but may have the same make and model.
//In case two Cars have same make and model, they should be inserted according to the
//increasing order of their vins.
//Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::addCar(string model, string make, int vin, double price)
{
    //if the Car already exist, return false
    Car* newCar = new Car();
    newCar->model = model;
    newCar->make = make;
    newCar->vin = vin;          // creates a new car and sets the values within
    newCar->price = price;
    newCar->next = NULL;
   
    if(head == NULL){
        head = newCar;
        this->carCount++;   // sets the newCar to head if there is no head and increases the carCount
        return true;
    }


    if(newCar->make.compare(head->make) < 0){
        newCar->next = head;
        head = newCar;
        this->carCount++;           // compares the head node to see if it it's needed to insert the new Car at the begining of an established list
        return true;
    }
    else if(newCar->make.compare(head->make) == 0 && (newCar->model.compare(head->model) < 0 || (newCar->model.compare(head->model) == 0 && newCar->vin < head->vin))){
            newCar->next = head;
            head = newCar;
            this->carCount++;
            return true;                // checks to see if the head needs to be moved and repaced by the new car
    }                                   // if so the car is added and made the new head
    if(head->next == NULL){
        head->next = newCar;
        this->carCount++;
        return true;
    }


    
    Car* current = head->next;
    Car* previous = head;
    
    while(current != NULL){
        if(newCar->make.compare(current->make) < 0){
            newCar->next = current;
            previous->next = newCar;            // loops through the list checking to see if it alphabetically belongs in the current spot 
            this->carCount++;                   // if it does then it is inserted between the prieveous and current car
            return true;
        }
        else if(newCar->make.compare(current->make) == 0 && (newCar->model.compare(current->model) < 0 || (newCar->model.compare(current->model) == 0 && newCar->vin < current->vin))){
                 newCar->next = current;                            // checks all the cars to see if the new car needs to be put in the middle or the end of the linked list
                 previous->next = newCar;                           // if so the car is placd appropiatly via dividing the lis in 2 adding the car to the end of the first
                 this->carCount++;
                 return true;                                       // and re-ataching the list
        }
        else if(current->next == NULL){
            current->next = newCar;
            this->carCount++;                   // inserts the new car at the end of the list
            return true;
        }

        previous = current;
        current = current->next;
    }
   //add your own code
   //----
   return false;
}

//Removes the specified Car from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeByVin(int aVin)
{   
    
    bool found = this->findCar(aVin);
    if(!found){
        return false;           // runs find car and returns false if no car is found
    }

    Car* current = head;
    if(head->vin == aVin){
        head = head->next;
        this->carCount--;       // removes the head and moves the head pointer up if the first Car is the one to be removed
        return true;
    }
    while (current->next != NULL)
    {
        /* code */                          // Searches the Linked list for a vin number, when found it removes te attached Car from the list
        if(current->next->vin == aVin){
            current->next = current->next->next;
            this->carCount--;
            return true;        //subtracts one from the car count
        }
        current = current->next;
    }
    return false;
    
}

//Removes the given Car from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all Cars with
//the same model and make should be removed from the list.

//This works 
bool LinkedList::removeByModelAndMake(string model, string make)
{
    bool found = false;
    
    while(head->make == make && head->model == model){
        head = head->next;
        this->carCount--;                               // will continue to remove the first car from the list if the new first car is 
        found = true;                                   // the same make and model
    }
    
    Car* current = head->next;
    Car* priv = head;

    bool instanceOfRemoving;
    while(current != NULL){
        instanceOfRemoving = false;
        if(current->make == make && current->model == model){
            priv->next = current->next;
            found = true;
            instanceOfRemoving = true;                  // Searches the list for a make and model, when it's found 
        }                                               // it is removed, all instances of a car with this same make and model
        if(instanceOfRemoving){                         // will be removed
            current = current->next;
            this->carCount--;

        }else{
            priv = current;
            current = current->next;
        }
        
    }
    if(!found){
        cout << "No such Car found.\n";                 // will print out a quote saying there is no car found if no instance of a make and model
    }
    return found;

}

//Modifies the data of the given Car. Return true if it modifies successfully and
//false otherwise. Note: after changing a Car model and make, the linked list must still
//maintain the alphabetical order.
bool LinkedList::changeCarInfo(int aVin, string newModelAndMake)
{
    //split newModelAndMake string to get model and make accordingly
    //add your own code
    //----
    Car* current = head;
    char *s = " ";
    char str[80];
    
    bool found = this->findCar(aVin);
    if(!found){
        return false;           // find call
    }

    strcpy(str, newModelAndMake.c_str());
    char* newModel = strtok(str, s);            // uses strcpy and strtok to split a string into 2 strings assigning them to 
    char* newMake = strtok(NULL, s);            // char pointers

    double newPrice;

    while(current != NULL){
        if(current->vin == aVin){
            newPrice = current->price;          // finds the price of the car with a given vin
            break;
        }
        current = current->next;
    }
    this->removeByVin(aVin);                                                    // removes the car with the vin and re-adds it with new paramaters
    this->addCar(newModel, newMake, aVin, newPrice);

    return true;
    //add your own code
    //----
}

//this doesnt work
bool LinkedList::updateCarPrice(int aVin, double newPrice)
{
    Car* current = head;
    bool found = this->findCar(aVin);
    if(!found){
        return false;
    }
    if(head->vin == aVin){
        head->price = newPrice;         // sets the first car to a new price if the vins match
        return true;
    }
    while(current != NULL){
        if(current->vin == aVin){
            current->price = newPrice;          // searches the list for a car with a vin,
            return true;                        // when found, the car price is updated
        }
        current = current->next;
    }
    return false;
}

//Prints all Cars in the list with the same make.

//this works 
void LinkedList::printCarListByMake(string make)
{
    Car* temp = head;
    bool found = false;
    while (temp != NULL)
    {
        /* code */
        if(make.compare(temp->make) == 0){
            found = true;
            cout << left << setw(12) << temp->model
            << left << setw(12) << temp->make           // Checks if a given car is a specific make, if so it is printed
            << right << setw(8) << temp->vin
            << setw(10) << fixed << setprecision(2) << temp->price << "\n";
        }
        temp = temp->next;
    }
    if (!found)
    {
        cout << "\nNo Cars with the specified make found.\n";       // prints an error message if no cars of the given make
    }
    
}

//Prints all Cars in the linked list starting from the head node.

//This works 
void LinkedList::printCarList()
{
    Car* temp = head;
    while(temp != NULL){
        cout << left << setw(12) << temp->model
            << left << setw(12) << temp->make
            << right << setw(8) << temp->vin
            << setw(10) << fixed << setprecision(2) << temp->price << "\n";
        temp = temp->next;
    }
}