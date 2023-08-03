#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <random>
#include <cmath>
#include <map>
#include <set>
#include <sstream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "Car.h"

using std::ofstream;
using std::ifstream;
using std::fstream;
using namespace std;

// https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
// Function to split a line based on commas, accounting for quoted fields
vector<string> split_CSV_line(const string& line) {
    vector<string> fields;
    size_t pos = 0;
    bool inQuote = false;
    string field;

    while (pos < line.length()) {
        char ch = line[pos];

        if (ch == '"') {
            inQuote = !inQuote;
        } else if (ch == ',' && !inQuote) {
            fields.push_back(field);
            field.clear();
        } else {
            field += ch;
        }

        ++pos;
    }
    fields.push_back(field); // Add the last field

    return fields;
}

// https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
// Function to read and parse a CSV file
vector< vector<string> > parse_CSV(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }

    // Read the header row
    if (getline(file, line)) {
        // Skip the header, assuming the first line is the header
    }

    // Read data rows
    while (getline(file, line)) {
        vector<string> fields;
        size_t start = 0;
        size_t pos = 0;
        bool in_quote = false;

        while (pos < line.length()) {
            char ch = line[pos];

            if (ch == '"') {
                in_quote = !in_quote;
            } else if (ch == ',' && !in_quote) {
                fields.push_back(line.substr(start, pos - start));
                start = pos + 1;
            }

            ++pos;
        }

        fields.push_back(line.substr(start)); // Add the last field
        data.push_back(fields);
    }

    file.close();
    return data;
}


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
    auto start = chrono::high_resolution_clock::now(); // start time
    // vector to hold objects that represent the individual cars.
    vector<Car> car_objects;
    // vector to hold vector of car param read for csv
    vector< vector<string> > car_param;

    car_param = parse_CSV("vehicles.csv");

    for( auto i : car_param ) {
        string barrels08 = i[0];
        string barrelsA08 = i[1];
        string charge120 = i[2];
        string charge240 = i[3];
        string city08 = i[4];
        string city08U = i[5];
        string cityA08 = i[6];
        string cityA08U = i[7];
        string cityCD = i[8];
        string cityE = i[9];
        string cityUF = i[10];
        string co2 = i[11];
        string co2A = i[12];
        string co2TailpipeAGpm = i[13];
        string co2TailpipeGpm = i[14];
        string comb08 = i[15];
        string comb08U = i[16];
        string combA08 = i[17];
        string combA08U = i[18];
        string combE = i[19];
        string combinedCD = i[20];
        string combinedUF = i[21];
        string cylinders = i[22];
        string displ = i[23];
        string drive = i[24];
        string engId = i[25];
        string eng_dscr = i[26];
        string feScore = i[27];
        string fuelCost08 = i[28];
        string fuelCostA08 = i[29];
        string fuelType = i[30];
        string fuelType1 = i[31];
        string ghgScore = i[32];
        string ghgScoreA = i[33];
        string highway08 = i[34];
        string highway08U = i[35];
        string highwayA08 = i[36];
        string highwayA08U = i[37];
        string highwayCD = i[38];
        string highwayE = i[39];
        string highwayUF = i[40];
        string hlv = i[41];
        string hpv = i[42];
        string id = i[43];
        string lv2 = i[44];
        string lv4 = i[45];
        string make = i[46];
        string model = i[47];
        string mpgData = i[48];
        string phevBlended = i[49];
        string pv2 = i[50];
        string pv4 = i[51];
        string range = i[52];
        string rangeCity = i[53];
        string rangeCityA = i[54];
        string rangeHwy = i[55];
        string rangeHwyA = i[56];
        string trany = i[57];
        string UCity = i[58];
        string UCityA = i[59];
        string UHighway = i[60];
        string UHighwayA = i[61];
        string VClass = i[62];
        string year = i[63];
        string youSaveSpend = i[64];
        string baseModel = i[65];
        string guzzler = i[66];
        string trans_dscr = i[67];
        string tCharger = i[68];
        string sCharger = i[69];
        string atvType = i[70];
        string fuelType2 = i[71];
        string rangeA = i[72];
        string evMotor = i[73];
        string mfrCode = i[74];
        string c240Dscr = i[75];
        string charge240b = i[76];
        string c240bDscr = i[77];
        string createdOn = i[78];
        string modifiedOn = i[79];
        string startStop = i[80];
        string phevCity = i[81];
        string phevHwy = i[82];
        string phevComb = i[83];

        Car temp_car(barrels08,barrelsA08,charge120,charge240,city08,city08U,cityA08,cityA08U,cityCD,cityE,cityUF,co2,co2A,co2TailpipeAGpm,co2TailpipeGpm,comb08,comb08U,combA08,combA08U,combE,combinedCD,combinedUF,cylinders,displ,drive,engId,eng_dscr,feScore,fuelCost08,fuelCostA08,fuelType,fuelType1,ghgScore,ghgScoreA,highway08,highway08U,highwayA08,highwayA08U,highwayCD,highwayE,highwayUF,hlv,hpv,id,lv2,lv4,make,model,mpgData,phevBlended,pv2,pv4,range,rangeCity,rangeCityA,rangeHwy,rangeHwyA,trany,UCity,UCityA,UHighway,UHighwayA,VClass,year,youSaveSpend,baseModel,guzzler,trans_dscr,tCharger,sCharger,atvType,fuelType2,rangeA,evMotor,mfrCode,c240Dscr,charge240b,c240bDscr,createdOn,modifiedOn,startStop,phevCity,phevHwy,phevComb);

        car_objects.push_back(temp_car);
    }


    /*

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
    */

    cout << car_objects.size() << endl;



    // comment out when testing shell sort
    // merge_sort(car_objects, 0, car_objects.size()-1);  // 3.08, 2.962, 2.989, 2.966, 3.029

    // comment out when testing merge sort
    // shell_sort(car_objects); // 2.307, 2.209, 2.151, 2.223, 2.178

    set<string> types; // diff types of cars
    // Vans, Minicompact Cars, Compact Cars, Subcompact Cars, Midsize Cars, Large Cars, Station Wagons, Minivan,
    // Pickup Trucks, Sport Utility Vehicle, Two Seaters
    for(auto car : car_objects) {  // populate vehicle types
        types.insert(car.VClass);
    }

    set<string> mpgs; // diff mpgs of cars
    // low of 1, high of 200
    for(auto car : car_objects) {
        mpgs.insert(car.city08);
    }

    set<string> drive_type; // diff drives of cars
    // 2-Wheel Drive, 4-Wheel Drive, 4-Wheel-Drive or All-Wheel Drive, All-Wheel Drive, Front-Wheel Drive,
    // Part-time 4-Wheel Drive, Rear-Wheel Drive
    for(auto car : car_objects) {
        drive_type.insert(car.drive);
    }

    /*
    for (auto i : car_objects) {
        string year = i.year

        string make = i.make;

        string model= i.model;

        string yearmakemodel = year + " " + make + " " + model;

        string mpg= i.city08;

        string type= i.VClass;

        string car_electric;
        if(stoi(i.charge120) > 0 || stoi(i.charge240) > 0) {
            car_electric = "electric";
        } else {
            car_electric = "gas";
        }

        string drive = i.drive;

        // (year make model), mpg, type, electric, and drive type
        cout << yearmakemodel << ", " << mpg << ", " << type << ", " << car_electric << ", " << drive << endl;
    }
// */


    vector<string> acceptable_types = {"Vans", "Minicompact Cars", "Compact Cars", "Subcompact Cars", "Midsize Cars", "Large Cars", "Station Wagons", "Minivan", "Pickup Trucks", "Sport Utility Vehicle", "Two Seaters"};
    vector<string> acceptable_drives = {"2-Wheel Drive", "4-Wheel Drive", "4-Wheel-Drive or All-Wheel Drive", "All-Wheel Drive", "Front-Wheel Drive", "Part-time 4-Wheel Drive", "Rear-Wheel Drive"};

    cout << "What type of car do you want? (i.e. Van, SUV, Compact)";
    string user_type;
    cin >> user_type;
    if(find(acceptable_types.begin(), acceptable_types.end(), user_type) == acceptable_types.end()) {
        cout << "invalid input" << endl;
        return 0;
    }

    cout << "What's the minimum mpg do you want? (i.e. highest is 150)";
    string user_mpg;
    cin >> user_mpg;

    cout << "Do you want electric? [y/n]";
    string user_electric;
    cin >> user_electric;

    cout << "What drive type do you want? (i.e. 4WD, AWD)";
    string user_drive;
    cin >> user_drive;
    if(find(acceptable_drives.begin(), acceptable_drives.end(), user_drive) == acceptable_drives.end()) {
        cout << "invalid input" << endl;
        return 0;
    }

    vector<Car> user_cars;  // vector to hold the cars of users preferences
    // loop through all cars and add cars that match users preferences
    for(auto car : car_objects) {
        string car_electric;
        if(stoi(car.charge120) > 0 || stoi(car.charge240) > 0) {
            car_electric = "y";
        } else {
            car_electric = "n";
        }
        if( ((car.VClass).find(user_type) != string::npos) && (stoi(car.city08) >= stoi(user_mpg)) && (user_drive == car.drive) && (user_electric == car_electric) ) {
            user_cars.push_back(car);
        }
    }

    merge_sort(user_cars, 0, user_cars.size()-1);

    // end time
    auto stop = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::milliseconds>(stop - start);
    // To get the value of duration use the count() member function on the duration object
    cout << "It took " << duration.count() / 1000.0f << " seconds" << endl;
    return 0;
}

