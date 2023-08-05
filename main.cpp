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
// Function to read and parse a CSV file
// This function is O(n), where n is number of char in csv file
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
// Merge two subarrays from arr, sorts the car vector based on cars combined mpgs
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
        if (stoi(X[i].comb08) <= stoi(Y[j].comb08)) {  // stoi bc everything is saved as strings
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
// O(nlogn)  , sorts cars vector based on mpgs
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

    // basic algorithm for lectur slide
    while (gap > 0) {
        for (int i = gap; i < n; ++i) {
            Car temp = cars[i];
            int j = i;
            while (j >= gap && stoi(cars[j - gap].comb08) > stoi(temp.comb08)) {
                cars[j] = cars[j - gap];
                j -= gap;
            }
            cars[j] = temp;
        }
        gap = (gap - 1) / 2; // Move to the next gap in the sequence
    }
}

// Function to set the pos of text, sets origin to center instead of top left
// Taken from Minesweeper project for Cop3503, credit Laura Cruz
void setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

// change the alpha value of sprite to change its transperency
// O(1)
void swap_transperency(int &alpha, sf::Sprite &sprite) {
    if (alpha == 255) {
        alpha = 0;
    } else {
        alpha = 255;
    }
    sprite.setColor(sf::Color(255, 255, 255, alpha));
}

int main() {
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


    set<string> types; // diff types of cars
    // Vans, Minicompact Cars, Compact Cars, Subcompact Cars, Midsize Cars, Large Cars, Station Wagons, Minivan,
    // Pickup Trucks, Sport Utility Vehicle, Two Seaters
    for(auto car : car_objects) {  // populate vehicle types
        types.insert(car.VClass);
    }

    set<int> mpgs; // diff mpgs of cars
    for(auto car : car_objects) {
        mpgs.insert(stoi(car.comb08));
    }

    set<string> drive_type; // diff drives of cars
    // 2-Wheel Drive, 4-Wheel Drive, 4-Wheel-Drive or All-Wheel Drive, All-Wheel Drive, Front-Wheel Drive,
    // Part-time 4-Wheel Drive, Rear-Wheel Drive
    for(auto car : car_objects) {
        drive_type.insert(car.drive);
    }




    // //////////////////////////////////// SFML /////////////////////////////////////////////////////////////////
    // ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    float WIDTH = 390;
    float HEIGHT = 750;

    sf::Font font;
    if (!font.loadFromFile("files/Arial.ttf")) {
        return 1;
    }

    bool pref_window_looping = true;
    bool like_window_looping = false;
    bool message_window_looping = false;
    // Create the window
    sf::RenderWindow pref_window(sf::VideoMode(WIDTH, HEIGHT), "CaRinge", sf::Style::Close);
    sf::RenderWindow like_window(sf::VideoMode(WIDTH, HEIGHT), "CaRinge", sf::Style::Close);
    like_window.setVisible(false);  // make window hidden until ready
    sf::RenderWindow message_window(sf::VideoMode(WIDTH, HEIGHT), "CaRinge", sf::Style::Close);
    message_window.setVisible(false);  // make window hidden until ready


    // create background png for preference page
    sf::Texture pref_texture;
    pref_texture.loadFromFile("files/caringe_pref_page.png");
    sf::Sprite pref_page;
    pref_page.setTexture(pref_texture);

    // create texture for checkbox
    sf::Texture checked_box_texture;
    checked_box_texture.loadFromFile("files/caringe_checked_box.png");
    // create all check box sprites
    sf::Sprite vans_checked_box;
    sf::Sprite compact_checked_box;
    sf::Sprite midsize_checked_box;
    sf::Sprite large_checked_box;
    sf::Sprite stationwagon_checked_box;
    sf::Sprite minivan_checked_box;
    sf::Sprite pickup_checked_box;
    sf::Sprite suv_checked_box;
    sf::Sprite twoseater_checked_box;
    sf::Sprite twowheel_checked_box;
    sf::Sprite fourwheel_checked_box;
    sf::Sprite allwheel_checked_box;
    sf::Sprite frontwheel_checked_box;
    sf::Sprite rearwheel_checked_box;
    sf::Sprite electric_checked_box;
    // set all checkbox textures
    vans_checked_box.setTexture(checked_box_texture);
    compact_checked_box.setTexture(checked_box_texture);
    midsize_checked_box.setTexture(checked_box_texture);
    large_checked_box.setTexture(checked_box_texture);
    stationwagon_checked_box.setTexture(checked_box_texture);
    minivan_checked_box.setTexture(checked_box_texture);
    pickup_checked_box.setTexture(checked_box_texture);
    suv_checked_box.setTexture(checked_box_texture);
    twoseater_checked_box.setTexture(checked_box_texture);
    twowheel_checked_box.setTexture(checked_box_texture);
    fourwheel_checked_box.setTexture(checked_box_texture);
    allwheel_checked_box.setTexture(checked_box_texture);
    frontwheel_checked_box.setTexture(checked_box_texture);
    rearwheel_checked_box.setTexture(checked_box_texture);
    electric_checked_box.setTexture(checked_box_texture);
    // set position for all boxes
    vans_checked_box.setPosition(353.8, 131.4);
    compact_checked_box.setPosition(353.8, 156.5);
    midsize_checked_box.setPosition(353.8, 181.6);
    large_checked_box.setPosition(353.8, 206.7);
    stationwagon_checked_box.setPosition(353.8, 231.8);
    minivan_checked_box.setPosition(353.8, 259.6);
    pickup_checked_box.setPosition(353.8, 282);
    suv_checked_box.setPosition(353.8, 307.1);
    twoseater_checked_box.setPosition(353.8, 332.3);
    twowheel_checked_box.setPosition(353.8, 402.9);
    fourwheel_checked_box.setPosition(353.8, 428);
    allwheel_checked_box.setPosition(353.8, 453.1);
    frontwheel_checked_box.setPosition(353.8, 478.2);
    rearwheel_checked_box.setPosition(353.8, 503.2);
    electric_checked_box.setPosition(353.8, 629.5);
    // set transperenceis of check boxes to zero so theyre hidden by defaul
    int vans_transperency = 0;
    vans_checked_box.setColor(sf::Color(255, 255, 255 ,vans_transperency));
    int compact_transperency = 0;
    compact_checked_box.setColor(sf::Color(255, 255, 255 ,compact_transperency));
    int mid_transperency = 0;
    midsize_checked_box.setColor(sf::Color(255, 255, 255 ,mid_transperency));
    int large_transperency = 0;
    large_checked_box.setColor(sf::Color(255, 255, 255 ,large_transperency));
    int stationwagon_transperency = 0;
    stationwagon_checked_box.setColor(sf::Color(255, 255, 255 ,stationwagon_transperency));
    int minivan_transperency = 0;
    minivan_checked_box.setColor(sf::Color(255, 255, 255 ,minivan_transperency));
    int pickup_transperency = 0;
    pickup_checked_box.setColor(sf::Color(255, 255, 255 ,pickup_transperency));
    int suv_transperency = 0;
    suv_checked_box.setColor(sf::Color(255, 255, 255 ,suv_transperency));
    int twoseat_transperency = 0;
    twoseater_checked_box.setColor(sf::Color(255, 255, 255 ,twoseat_transperency));
    int twowheel_transperency = 0;
    twowheel_checked_box.setColor(sf::Color(255, 255, 255 ,twowheel_transperency));
    int fourwheel_transperency = 0;
    fourwheel_checked_box.setColor(sf::Color(255, 255, 255 ,fourwheel_transperency));
    int allwheel_transperency = 0;
    allwheel_checked_box.setColor(sf::Color(255, 255, 255 ,allwheel_transperency));
    int frontwheel_transperency = 0;
    frontwheel_checked_box.setColor(sf::Color(255, 255, 255 ,frontwheel_transperency));
    int rearwheel_transperency = 0;
    rearwheel_checked_box.setColor(sf::Color(255, 255, 255 ,rearwheel_transperency));
    int electric_transperency = 0;
    electric_checked_box.setColor(sf::Color(255, 255, 255 ,electric_transperency));

    // text value for slider
    int max_mpg = *mpgs.rbegin();
    string user_mpg = "0";  // max value is going to be 111
    sf::Text mpg_text(user_mpg, font, 12);
    mpg_text.setPosition(19, 568);
    mpg_text.setColor(sf::Color(0, 0, 0 ,255));
    // slider circle for mpg
    sf::CircleShape slider(6.f);
    slider.setFillColor(sf::Color(113, 63, 108 ,255));
    slider.setPosition(17, 583);

    bool dragging = false;

    // Main loop
    while (pref_window.isOpen() && pref_window_looping) {
        // Process events
        sf::Event event;
        while (pref_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                pref_window.close();
                pref_window_looping = false;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                if (event.mouseButton.button == sf::Mouse::Right) {
                    // do nothing
                }
                if (event.mouseButton.button == sf::Mouse::Left) {  // if left click

                    // If 'X' button clicked or CR button clicked, do stuff
                    if ( ((x <= 362.1+11.8) && (x >= 362.1) && (y <= 15.7+11.8) && (y >= 15.7)) || ((x <= 36.2+79) && (x >= 36.2) && (y <= 697.4+44.4) && (y >= 697.4))) {
                        // make preferences window hidden and open like window
                        pref_window.close();
                        pref_window_looping = false;
                        like_window.setVisible(true);
                        like_window_looping = true;
                    }

                    // if in slider area activate dragging
                    if ( (x <= 361) && (x >= 17) && (y <= 583+12) && (y >= 583)) {
                        dragging = !dragging;
                    }

                    // if in check box area, change transperency
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 131.4+19) && (y >= 131.4)) {
                        swap_transperency(vans_transperency, vans_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 156.5+19) && (y >= 156.5)) {
                        swap_transperency(compact_transperency, compact_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 181.6+19) && (y >= 181.6)) {
                        swap_transperency(mid_transperency, midsize_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 206.7+19) && (y >= 206.7)) {
                        swap_transperency(large_transperency, large_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 236.8+19) && (y >= 236.8)) {
                        swap_transperency(stationwagon_transperency, stationwagon_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 259.6+19) && (y >= 259.6)) {
                        swap_transperency(minivan_transperency, minivan_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 282+19) && (y >= 282)) {
                        swap_transperency(pickup_transperency, pickup_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 307.1+19) && (y >= 307.1)) {
                        swap_transperency(suv_transperency, suv_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 332.2+19) && (y >= 332.2)) {
                        swap_transperency(twoseat_transperency, twoseater_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 402.9+19) && (y >= 402.9)) {
                        swap_transperency(twowheel_transperency, twowheel_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 428+19) && (y >= 428)) {
                        swap_transperency(fourwheel_transperency, fourwheel_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 453.1+19) && (y >= 453.1)) {
                        swap_transperency(allwheel_transperency, allwheel_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 478.2+19) && (y >= 478.2)) {
                        swap_transperency(frontwheel_transperency, frontwheel_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 503.3+19) && (y >= 503.3)) {
                        swap_transperency(rearwheel_transperency, rearwheel_checked_box);
                    }
                    if ( (x <= 353.8+19) && (x >= 353.8) && (y <= 629.5+19) && (y >= 629.5)) {
                        swap_transperency(electric_transperency, electric_checked_box);
                    }
                }
            }



            // dynamically move the slider
            if (event.type == sf::Event::MouseMoved) {
                if (dragging) {
                    // if within slider area, move
                    int xmove = event.mouseMove.x;
                    int ymove = event.mouseMove.y;
                    if ( (xmove <= 367) && (xmove >= 23) && (ymove <= 613) && (ymove >= 563)) {
                        slider.setPosition(xmove - 6, 583);
                        mpg_text.setPosition(xmove - 4, 568);

                        user_mpg = to_string(max_mpg * (xmove-23) / (367-23));
                        mpg_text.setString(user_mpg);
                    } else {
                        dragging = false;
                    }
                }
            }
        }

        // Clear the screen
        pref_window.clear();

        // Draw //
        // draw background
        pref_window.draw(pref_page);
        // draw checkboxes
        pref_window.draw(vans_checked_box);
        pref_window.draw(compact_checked_box);
        pref_window.draw(midsize_checked_box);
        pref_window.draw(large_checked_box);
        pref_window.draw(stationwagon_checked_box);
        pref_window.draw(minivan_checked_box);
        pref_window.draw(pickup_checked_box);
        pref_window.draw(suv_checked_box);
        pref_window.draw(twoseater_checked_box);
        pref_window.draw(twowheel_checked_box);
        pref_window.draw(fourwheel_checked_box);
        pref_window.draw(allwheel_checked_box);
        pref_window.draw(frontwheel_checked_box);
        pref_window.draw(rearwheel_checked_box);
        pref_window.draw(electric_checked_box);
        // draw slider
        pref_window.draw(slider);
        pref_window.draw(mpg_text);


        // Display the window
        pref_window.display();
    }

    // make vectors to hold users preferences
    vector<string> user_types;
    vector<string> user_drives;
    string user_electric;
    // populate user_types with user chosen car types based on csv
    if(vans_transperency == 255) {
        user_types.push_back("Vans");
        user_types.push_back("Vans Passenger");
        user_types.push_back("Vans, Cargo Type");
        user_types.push_back("Vans, Passenger Type");
    }
    if(compact_transperency == 255) {
        user_types.push_back("Compact Cars");
        user_types.push_back("Minicompact Cars");
        user_types.push_back("Subcompact Cars");
    }
    if(mid_transperency == 255) {
        user_types.push_back("Midsize Cars");
    }
    if(large_transperency == 255) {
        user_types.push_back("Large Cars");
    }
    if(stationwagon_transperency == 255) {
        user_types.push_back("Small Station Wagons");
        user_types.push_back("Midsize Station Wagons");
        user_types.push_back("Midsize-Large Station Wagons");
    }
    if(minivan_transperency == 255) {
        user_types.push_back("Minivan - 2WD");
        user_types.push_back("Minivan - 4WD");
    }
    if(pickup_transperency == 255) {
        user_types.push_back("Small Pickup Trucks");
        user_types.push_back("Small Pickup Trucks 2WD");
        user_types.push_back("Small Pickup Trucks 4WD");
        user_types.push_back("Standard Pickup Trucks 2WD");
        user_types.push_back("Standard Pickup Trucks 4WD");
        user_types.push_back("Standard Pickup Trucks/2wd");
        user_types.push_back("Standard Pickup Trucks");
    }
    if(suv_transperency == 255) {
        user_types.push_back("Small Sport Utility Vehicle 2WD");
        user_types.push_back("Small Sport Utility Vehicle 4WD");
        user_types.push_back("Sport Utility Vehicle - 2WD");
        user_types.push_back("Sport Utility Vehicle - 4WD");
        user_types.push_back("Standard Sport Utility Vehicle 2WD");
        user_types.push_back("Standard Sport Utility Vehicle 4WD");
    }
    if(twoseat_transperency == 255) {
        user_types.push_back("Two Seaters");
    }

    // populate user_drives with user chosen drive types same as vClass
    if(twowheel_transperency == 255) {
        user_drives.push_back("2-Wheel Drive");
    }
    if(fourwheel_transperency == 255) {
        user_drives.push_back("4-Wheel Drive");
        user_drives.push_back("4-Wheel or All-Wheel Drive");
        user_drives.push_back("Part-time 4-Wheel Drive");

    }
    if(allwheel_transperency == 255) {
        user_drives.push_back("All-Wheel Drive");
        user_drives.push_back("4-Wheel or All-Wheel Drive");

    }
    if(frontwheel_transperency == 255) {
        user_drives.push_back("Front-Wheel Drive");
    }
    if(rearwheel_transperency == 255) {
        user_drives.push_back("Rear-Wheel Drive");
    }

    if(electric_transperency == 255) {
        user_electric = "Electric";
    }

    // create vector to hold potential matches for user
    vector<Car> picks_for_user;
    // loop through to find cars that match preferences
    for(auto car : car_objects) {
        if(user_electric == "Electric") {  // if user wants electric cars
            if( find(user_types.begin(), user_types.end(),car.VClass) != user_types.end() &&
                find(user_drives.begin(), user_drives.end(), car.drive) != user_drives.end() && (stoi(car.comb08) >= stoi(user_mpg)) && car.fuelType == "Electricity") {
                picks_for_user.push_back(car);  // add car to vector
            }
        } else {  // if they don't want electric
            if( find(user_types.begin(), user_types.end(),car.VClass) != user_types.end() &&
                find(user_drives.begin(), user_drives.end(), car.drive) != user_drives.end() && (stoi(car.comb08) >= stoi(user_mpg)) && car.fuelType != "Electricity") {
                picks_for_user.push_back(car);  // add car to vector
            }
        }
    }

    // ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Main project purpose, compare sortings below
    // ////////////////////////////////////////////////////////////////////////////////////////////////////
    // ////////////////////////////////////////////////////////////////////////////////////////////////////
    auto start = chrono::high_resolution_clock::now(); // start time

    // comment out when testing shell sort
    // merge_sort(picks_for_user, 0, picks_for_user.size()-1);  // 3.08, 2.962, 2.989, 2.966, 3.029
    // 41,486 inputs: 1.192, 1.196
    // 22,542 inputs: 0.575, 0.579
    // 6514 inputs: 0.152, 0.149
    // 278 inputs: 0.003, 0.004

    // comment out when testing merge sort
    shell_sort(picks_for_user); // 2.307, 2.209, 2.151, 2.223, 2.178
    // 41,486 inputs: 0.429, 0.436
    // 22,542 inputs: 0.22, 0.22
    // 6514 inputs: 0.052, 0.052
    // 278 inputs: 0.001, 0.001

    auto stop = chrono::high_resolution_clock::now();
    // we chose to stick with shell sort bc it consistently performed better
    // ////////////////////////////////////////////////////////////////////////////////////////////////////



    // Like window stuff /////////////////////////////////////////////////////////////////
    vector<Car> matched_cars;  // vector to hold cars user likes
    int num_likes = 0; // num of likes done, max 10
    // create background png for preference page
    sf::Texture like_texture;
    like_texture.loadFromFile("files/caringe_like_page.png");
    sf::Sprite like_page;
    like_page.setTexture(like_texture);
    // total number of cars in pickx vector
    int index = picks_for_user.size() - 1;  // to iterate through picked cars
    sf::Text total_count(to_string(index+1), font, 14);
    total_count.setPosition(316.3, 24.4);
    total_count.setColor(sf::Color(157,157,157,255));
    // start making text items for each car


    sf::Text out_of_picks("No More Picks", font, 24);
    out_of_picks.setStyle(sf::Text::Bold);
    setText(out_of_picks, WIDTH/2, HEIGHT/2 - 50);
    sf::Text out_of_picks2("Re-run the program with different preferences", font, 16);
    out_of_picks2.setStyle(sf::Text::Bold);
    setText(out_of_picks2, WIDTH/2, HEIGHT/2-10);
    int out_picks_transperency = 0;
    out_of_picks.setColor(sf::Color(0, 0, 0, out_picks_transperency));
    out_of_picks2.setColor(sf::Color(0, 0, 0, out_picks_transperency));

    // make text for year and make
    sf::Text year_make("", font, 24);
    year_make.setStyle(sf::Text::Bold);
    year_make.setPosition(21, 75.7);
    year_make.setColor(sf::Color::Black);
    // make text for model right below
    sf::Text model("", font, 24);
    model.setStyle(sf::Text::Bold);
    model.setPosition(21, 100.7);
    model.setColor(sf::Color::Black);

    int sub_font_size = 18;
    sf::Text fuelcost("", font, sub_font_size);
    fuelcost.setPosition(21, 150.7);
    fuelcost.setColor(sf::Color::Black);

    sf::Text type("", font, sub_font_size);
    type.setPosition(21, 200.7);
    type.setColor(sf::Color::Black);

    sf::Text drive("", font, sub_font_size);
    drive.setPosition(21, 250.7);
    drive.setColor(sf::Color::Black);

    sf::Text combmpg("", font, sub_font_size);
    combmpg.setPosition(21, 300.7);
    combmpg.setColor(sf::Color::Black);

    sf::Text citympg("", font, sub_font_size);
    citympg.setPosition(21, 350.7);
    citympg.setColor(sf::Color::Black);

    sf::Text highmpg("", font, sub_font_size);
    highmpg.setPosition(21, 400.7);
    highmpg.setColor(sf::Color::Black);

    sf::Text cylinders("", font, sub_font_size);
    cylinders.setPosition(21, 450.7);
    cylinders.setColor(sf::Color::Black);

    sf::Text displacement("", font, sub_font_size);
    displacement.setPosition(21, 500.7);
    displacement.setColor(sf::Color::Black);

    // match ajax stuff
    // background
    sf::Texture match_texture;
    match_texture.loadFromFile("files/caringe_matches_page.png");
    sf::Sprite match_page;
    match_page.setTexture(match_texture);
    bool match_showing = false;  // bool to know if matches should be showing or not
    // make 10 sf::text objects
    int match_font_size = 20;
    sf::Text match1("", font, match_font_size);
    match1.setPosition(26.6, 104);
    match1.setColor(sf::Color::Black);

    sf::Text match2("", font, match_font_size);
    match2.setPosition(26.6, 162);
    match2.setColor(sf::Color::Black);

    sf::Text match3("", font, match_font_size);
    match3.setPosition(26.6, 221);
    match3.setColor(sf::Color::Black);

    sf::Text match4("", font, match_font_size);
    match4.setPosition(26.6, 279);
    match4.setColor(sf::Color::Black);

    sf::Text match5("", font, match_font_size);
    match5.setPosition(26.6, 337);
    match5.setColor(sf::Color::Black);

    sf::Text match6("", font, match_font_size);
    match6.setPosition(26.6, 396);
    match6.setColor(sf::Color::Black);

    sf::Text match7("", font, match_font_size);
    match7.setPosition(26.6, 454);
    match7.setColor(sf::Color::Black);

    sf::Text match8("", font, match_font_size);
    match8.setPosition(26.6, 512);
    match8.setColor(sf::Color::Black);

    sf::Text match9("", font, match_font_size);
    match9.setPosition(26.6, 571);
    match9.setColor(sf::Color::Black);

    sf::Text match10("", font, match_font_size);
    match10.setPosition(26.6, 625);
    match10.setColor(sf::Color::Black);

    // out of likes text only displays when out of likes
    sf::Text no_likes("Out of Likes", font, 22);
    no_likes.setStyle(sf::Text::Bold);
    no_likes.setPosition(178, 625);
    no_likes.setColor(sf::Color(206, 182, 171, 255));


    bool no_picks = false;
    if (picks_for_user.empty()) {  // if vector empty
        no_picks = true;
        out_picks_transperency = 255;
        out_of_picks.setColor(sf::Color(0, 0, 0, out_picks_transperency));
        out_of_picks2.setColor(sf::Color(0, 0, 0, out_picks_transperency));
    } else {
        // set strings of sf:Text objects to Car member values
        string test = picks_for_user[index].year + " " + picks_for_user[index].make;
        year_make.setString(test);
        model.setString(picks_for_user[index].model);

        string fuelcost_string = "Annual Fuel Cost: $" + picks_for_user[index].fuelCost08;
        string class_string = "Vehicle Class: " + picks_for_user[index].VClass;
        string drive_string = "Drive Type: " + picks_for_user[index].drive;
        string combmpg_string = "Combined MPG: " + picks_for_user[index].comb08;
        string citympg_string = "City MPG: " + picks_for_user[index].city08;
        string highmpg_string = "Highway MPG: " + picks_for_user[index].highway08;
        string cylinders_string = "Number of Cylinders: " + picks_for_user[index].cylinders;
        string displacement_string = "Engine Displacement (litres): " + picks_for_user[index].displ;

        fuelcost.setString(fuelcost_string);
        type.setString(class_string);
        drive.setString(drive_string);
        combmpg.setString(combmpg_string);
        citympg.setString(citympg_string);
        highmpg.setString(highmpg_string);
        cylinders.setString(cylinders_string);
        displacement.setString(displacement_string);
    }


    while (like_window.isOpen() && like_window_looping) {
        // Process events
        sf::Event event;
        while (like_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                like_window.close();
                like_window_looping = false;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                if (event.mouseButton.button == sf::Mouse::Right) {
                    // do nothing
                }
                if (event.mouseButton.button == sf::Mouse::Left) {  // if left click

                    // if clicked 'X' or heart go to next car, also check if there are cars to go to, if match page showing do nothing
                    if ( !match_showing && !no_picks && (((x <= 11+64.7) && (x >= 11) && (y <= 604+64.7) && (y >= 604)) || ( (num_likes < 10) && (x <= 314+64.7) && (x >= 314) && (y <= 604+64.7) && (y >= 604))) ) {
                        index -= 1;  // increase the index so the screen can move to the next car
                        if(index == 0) {  // no more cars left so break the loop and show screen
                            no_picks = true;
                        }
                        // change the text on screen to show next car
                        total_count.setString(to_string(index+1));
                        string test = picks_for_user[index].year + " " + picks_for_user[index].make;
                        year_make.setString(test);
                        model.setString(picks_for_user[index].model);
                        string fuelcost_string = "Annual Fuel Cost: $" + picks_for_user[index].fuelCost08;
                        string class_string = "Vehicle Class: " + picks_for_user[index].VClass;
                        string drive_string = "Drive Type: " + picks_for_user[index].drive;
                        string combmpg_string = "Combined MPG: " + picks_for_user[index].comb08;
                        string citympg_string = "City MPG: " + picks_for_user[index].city08;
                        string highmpg_string = "Highway MPG: " + picks_for_user[index].highway08;
                        string cylinders_string = "Number of Cylinders: " + picks_for_user[index].cylinders;
                        string displacement_string = "Engine Displacement (litres): " + picks_for_user[index].displ;

                        fuelcost.setString(fuelcost_string);
                        type.setString(class_string);
                        drive.setString(drive_string);
                        combmpg.setString(combmpg_string);
                        citympg.setString(citympg_string);
                        highmpg.setString(highmpg_string);
                        cylinders.setString(cylinders_string);
                        displacement.setString(displacement_string);
                    }
                    // if user clicks on heart, add to liked list, max 10 likes
                    if ( !match_showing && (num_likes < 10) && !no_picks && ((x <= 314+64.7) && (x >= 314) && (y <= 604+64.7) && (y >= 604)) ) {
                        matched_cars.push_back(picks_for_user[index]);  // add car to matched list
                        string match_year_make_model = picks_for_user[index].year + " " + picks_for_user[index].make + " " + picks_for_user[index].model;
                        // for some reason a vector isn't working so I'm using 10 if statements since i'm lazy, same diff rlly
                        if (num_likes == 0) {
                            match1.setString(match_year_make_model);
                        } else if (num_likes == 1) {
                            match2.setString(match_year_make_model);
                        } else if (num_likes == 2) {
                            match3.setString(match_year_make_model);
                        } else if (num_likes == 3) {
                            match4.setString(match_year_make_model);
                        } else if (num_likes == 4) {
                            match5.setString(match_year_make_model);
                        } else if (num_likes == 5) {
                            match6.setString(match_year_make_model);
                        } else if (num_likes == 6) {
                            match7.setString(match_year_make_model);
                        } else if (num_likes == 7) {
                            match8.setString(match_year_make_model);
                        } else if (num_likes == 8) {
                            match9.setString(match_year_make_model);
                        } else if (num_likes == 9) {
                            match10.setString(match_year_make_model);
                        } else {
                            // do nothing
                        }
                        num_likes += 1;  // decrement num of likes left
                    }

                    // if user clicks matches button
                    if ( ((x <= 173.8+42) && (x >= 173.8) && (y <= 697.4+40) && (y >= 697.4)) ) {
                        match_showing = true;
                    }

                    // if user clicks CR button
                    if ( ((x <= 36.2+79) && (x >= 36.2) && (y <= 699.1+39) && (y >= 699.1)) ) {
                        match_showing = false;
                    }
                }
            }
        }

        // Clear the screen
        like_window.clear();


        // Draw //
        // draw background
        like_window.draw(like_page);
        // draw text
        like_window.draw(out_of_picks);
        like_window.draw(out_of_picks2);
        like_window.draw(total_count);
        like_window.draw(year_make);
        like_window.draw(model);
        like_window.draw(fuelcost);
        like_window.draw(type);
        like_window.draw(drive);
        like_window.draw(combmpg);
        like_window.draw(citympg);
        like_window.draw(highmpg);
        like_window.draw(cylinders);
        like_window.draw(displacement);
        // only display if like counter is 10>
        if (num_likes >= 10) {
            like_window.draw(no_likes);
        }

        // match page
        if(match_showing) {  // draw at end so it covers everything else
            like_window.draw(match_page);
            like_window.draw(match1);
            like_window.draw(match2);
            like_window.draw(match3);
            like_window.draw(match4);
            like_window.draw(match5);
            like_window.draw(match6);
            like_window.draw(match7);
            like_window.draw(match8);
            like_window.draw(match9);
            like_window.draw(match10);
        }
        // Display the window
        like_window.display();
    }


    // end time
    auto duration = duration_cast<chrono::milliseconds>(stop - start);
    // To get the value of duration use the count() member function on the duration object
    cout << "It took " << duration.count() / 1000.0f << " seconds" << endl;
    return 0;
}

