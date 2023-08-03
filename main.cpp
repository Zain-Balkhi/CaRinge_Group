#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <random>
#include <cmath>
#include <map>
#include <sstream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "Car.h"
using std::ofstream;
using std::ifstream;
using std::fstream;
using namespace std;


// taken from lecture slides linking to https://www.onlinegdb.com/HJT6FfMlv
// Merge two subarrays from arr
void merge(vector<Car> &arr, int left, int mid, int right) {
    // Create X ← arr[left..mid] & Y ← arr[mid+1..right]
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Car> X(n1), Y(n2);

    for (int i = 0; i < n1; i++)
        X[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        Y[j] = arr[mid + 1 + j];

    // Merge the arrays X and Y into arr
    int i, j, k;
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (stoi(X[i].fuelCost08) <= stoi(Y[j].fuelCost08)) {  // stoi bc everything is saved as strings
            arr[k] = X[i];
            i++;
        } else {
            arr[k] = Y[j];
            j++;
        }
        k++;
    }
    // When we run out of elements in either X or Y append the remaining elements
    while (i < n1) {
        arr[k] = X[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = Y[j];
        j++;
        k++;
    }
}

// taken from lecture slides linnking to https://www.onlinegdb.com/HJT6FfMlv
// O(nlogn)
void merge_sort(vector<Car> &arr, int left, int right) {
    if (left < right) {
        // m is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // Merge the sorted subarrays
        merge(arr, left, mid, right);
    }
}

// https://www.geeksforgeeks.org/shellsort/ for help
// https://www.programiz.com/dsa/shell-sort for help
// Shell Sort function with Hibbard's sequence for gap selection
// O(n^(3/2)) based on lecture slides
void shell_sort(vector<Car>& cars) {
    int n = cars.size();
    int gap = 1;

    // Generate Hibbard's sequence for gap selection
    while (gap < n) {  // get the largest gap possible
        gap = gap * 2 + 1;
    }

    while (gap > 0) {
        for (int i = gap; i < n; ++i) {
            Car temp = cars[i];
            int j = i;
            while (j >= gap && stoi(cars[j - gap].fuelCost08) > stoi(temp.fuelCost08)) {
                cars[j] = cars[j - gap];
                j -= gap;
            }
            cars[j] = temp;
        }

        gap = (gap - 1) / 2; // Move to the next gap in the sequence
    }
}



int main() {
    auto start = std::chrono::high_resolution_clock::now(); // start time

    // vector to hold objects that represent the individual cars.
    vector<Car> car_objects;

    fstream vehicles("vehicles.csv", ios_base::in);  // open csv file
    if (!vehicles.is_open()) {  // check if file opened
        return 1;
    }

    string singleLine;  // temp variable for each line in csv
    getline(vehicles, singleLine);  // get the first line of the csv because its just labels and breaks things
    // loop through all the lines in the csv of states
    while (getline(vehicles, singleLine)) {
        string barrels08;
        string barrelsA08;
        string charge120;
        string charge240;
        string city08;
        string city08U;
        string cityA08;
        string cityA08U;
        string cityCD;
        string cityE;
        string cityUF;
        string co2;
        string co2A;
        string co2TailpipeAGpm;
        string co2TailpipeGpm;
        string comb08;
        string comb08U;
        string combA08;
        string combA08U;
        string combE;
        string combinedCD;
        string combinedUF;
        string cylinders;
        string displ;
        string drive;
        string engId;
        string eng_dscr;
        string feScore;
        string fuelCost08;
        string fuelCostA08;
        string fuelType;
        string fuelType1;
        string ghgScore;
        string ghgScoreA;
        string highway08;
        string highway08U;
        string highwayA08;
        string highwayA08U;
        string highwayCD;
        string highwayE;
        string highwayUF;
        string hlv;
        string hpv;
        string id;
        string lv2;
        string lv4;
        string make;
        string model;
        string mpgData;
        string phevBlended;
        string pv2;
        string pv4;
        string range;
        string rangeCity;
        string rangeCityA;
        string rangeHwy;
        string rangeHwyA;
        string trany;
        string UCity;
        string UCityA;
        string UHighway;
        string UHighwayA;
        string VClass;
        string year;
        string youSaveSpend;
        string baseModel;
        string guzzler;
        string trans_dscr;
        string tCharger;
        string sCharger;
        string atvType;
        string fuelType2;
        string rangeA;
        string evMotor;
        string mfrCode;
        string c240Dscr;
        string charge240b;
        string c240bDscr;
        string createdOn;
        string modifiedOn;
        string startStop;
        string phevCity;
        string phevHwy;
        string phevComb;

        istringstream stream(singleLine);  // turn line into a object that can be "read"

        getline(stream, barrels08, ',');  // read value before the next comma
        getline(stream, barrelsA08, ',');
        getline(stream, charge120, ',');
        getline(stream, charge240, ',');
        getline(stream, city08, ',');
        getline(stream, city08U, ',');
        getline(stream, cityA08, ',');
        getline(stream, cityA08U, ',');
        getline(stream, cityCD, ',');
        getline(stream, cityE, ',');
        getline(stream, cityUF, ',');
        getline(stream, co2, ',');
        getline(stream, co2A, ',');
        getline(stream, co2TailpipeAGpm, ',');
        getline(stream, co2TailpipeGpm, ',');
        getline(stream, comb08, ',');
        getline(stream, comb08U, ',');
        getline(stream, combA08, ',');
        getline(stream, combA08U, ',');
        getline(stream, combE, ',');
        getline(stream, combinedCD, ',');
        getline(stream, combinedUF, ',');
        getline(stream, cylinders, ',');
        getline(stream, displ, ',');
        getline(stream, drive, ',');
        getline(stream, engId, ',');
        getline(stream, eng_dscr, ',');
        getline(stream, feScore, ',');
        getline(stream, fuelCost08, ',');
        getline(stream, fuelCostA08, ',');
        getline(stream, fuelType, ',');
        getline(stream, fuelType1, ',');
        getline(stream, ghgScore, ',');
        getline(stream, ghgScoreA, ',');
        getline(stream, highway08, ',');
        getline(stream, highway08U, ',');
        getline(stream, highwayA08, ',');
        getline(stream, highwayA08U, ',');
        getline(stream, highwayCD, ',');
        getline(stream, highwayE, ',');
        getline(stream, highwayUF, ',');
        getline(stream, hlv, ',');
        getline(stream, hpv, ',');
        getline(stream, id, ',');
        getline(stream, lv2, ',');
        getline(stream, lv4, ',');
        getline(stream, make, ',');
        getline(stream, model, ',');
        getline(stream, mpgData, ',');
        getline(stream, phevBlended, ',');
        getline(stream, pv2, ',');
        getline(stream, pv4, ',');
        getline(stream, range, ',');
        getline(stream, rangeCity, ',');
        getline(stream, rangeCityA, ',');
        getline(stream, rangeHwy, ',');
        getline(stream, rangeHwyA, ',');
        getline(stream, trany, ',');
        getline(stream, UCity, ',');
        getline(stream, UCityA, ',');
        getline(stream, UHighway, ',');
        getline(stream, UHighwayA, ',');
        getline(stream, VClass, ',');
        getline(stream, year, ',');
        getline(stream, youSaveSpend, ',');
        getline(stream, baseModel, ',');
        getline(stream, guzzler, ',');
        getline(stream, trans_dscr, ',');
        getline(stream, tCharger, ',');
        getline(stream, sCharger, ',');
        getline(stream, atvType, ',');
        getline(stream, fuelType2, ',');
        getline(stream, rangeA, ',');
        getline(stream, evMotor, ',');
        getline(stream, mfrCode, ',');
        getline(stream, c240Dscr, ',');
        getline(stream, charge240b, ',');
        getline(stream, c240bDscr, ',');
        getline(stream, createdOn, ',');
        getline(stream, modifiedOn, ',');
        getline(stream, startStop, ',');
        getline(stream, phevCity, ',');
        getline(stream, phevHwy, ',');
        getline(stream, phevComb);


        Car temp_car(barrels08,barrelsA08,charge120,charge240,city08,city08U,cityA08,cityA08U,cityCD,cityE,cityUF,co2,co2A,co2TailpipeAGpm,co2TailpipeGpm,comb08,comb08U,combA08,combA08U,combE,combinedCD,combinedUF,cylinders,displ,drive,engId,eng_dscr,feScore,fuelCost08,fuelCostA08,fuelType,fuelType1,ghgScore,ghgScoreA,highway08,highway08U,highwayA08,highwayA08U,highwayCD,highwayE,highwayUF,hlv,hpv,id,lv2,lv4,make,model,mpgData,phevBlended,pv2,pv4,range,rangeCity,rangeCityA,rangeHwy,rangeHwyA,trany,UCity,UCityA,UHighway,UHighwayA,VClass,year,youSaveSpend,baseModel,guzzler,trans_dscr,tCharger,sCharger,atvType,fuelType2,rangeA,evMotor,mfrCode,c240Dscr,charge240b,c240bDscr,createdOn,modifiedOn,startStop,phevCity,phevHwy,phevComb);

        car_objects.push_back(temp_car);
    }

    cout << car_objects.size() << endl;



    // comment out when testing shell sort
    // merge_sort(car_objects, 0, car_objects.size()-1);  // 3.08, 2.962, 2.989, 2.966, 3.029

    // comment out when testing merge sort
    shell_sort(car_objects); // 2.307, 2.209, 2.151, 2.223, 2.178

    for(auto car : car_objects) {
        cout << car.fuelCost08 << endl;
    }


    /*
    for (auto i : car_objects) {
        string year;
        if (i.year.empty()) { year = "XXXXX";} else { year = i.year; };

        string make;
        if (i.make == "") { make = "XXXXX";} else { make = i.make; };

        string model;
        if (i.model == "") { model = "XXXXX";} else { model = i.model; };

        string yearmakemodel = year + " " + make + " " + model;

        string mpg;
        if (i.city08 == "") { mpg = "XXXXX";} else { mpg = i.city08; };

        string type;
        if (i.VClass == "") { type = "XXXXX";} else { type = i.VClass; };

        string car_electric;
        if(stoi(i.charge120) > 0 || stoi(i.charge240) > 0) {
            car_electric = "electric";
        } else {
            car_electric = "gas";
        }

        string drive;
        if (i.drive == "") { drive = "XXXXX";} else { drive = i.drive; };

        // (year make model), mpg, type, electric, and drive type
        cout << yearmakemodel << ", " << mpg << ", " << type << ", " << car_electric << ", " << drive << endl;
    }
*/


    // end time
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
    // To get the value of duration use the count() member function on the duration object
    cout << "It took " << duration.count() / 1000.0f << " seconds" << endl;
    return 0;
}

