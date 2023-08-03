//
// Created by Zain Balkhi on 8/2/23.
//

#ifndef CARINGE_CAR_H
#define CARINGE_CAR_H

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

using namespace std;

struct Car {
    std::string barrels08;
    std::string barrelsA08;
    std::string charge120;
    std::string charge240;
    std::string city08;
    std::string city08U;
    std::string cityA08;
    std::string cityA08U;
    std::string cityCD;
    std::string cityE;
    std::string cityUF;
    std::string co2;
    std::string co2A;
    std::string co2TailpipeAGpm;
    std::string co2TailpipeGpm;
    std::string comb08;
    std::string comb08U;
    std::string combA08;
    std::string combA08U;
    std::string combE;
    std::string combinedCD;
    std::string combinedUF;
    std::string cylinders;
    std::string displ;
    std::string drive;
    std::string engId;
    std::string eng_dscr;
    std::string feScore;
    std::string fuelCost08;
    std::string fuelCostA08;
    std::string fuelType;
    std::string fuelType1;
    std::string ghgScore;
    std::string ghgScoreA;
    std::string highway08;
    std::string highway08U;
    std::string highwayA08;
    std::string highwayA08U;
    std::string highwayCD;
    std::string highwayE;
    std::string highwayUF;
    std::string hlv;
    std::string hpv;
    std::string id;
    std::string lv2;
    std::string lv4;
    std::string make;
    std::string model;
    std::string mpgData;
    std::string phevBlended;
    std::string pv2;
    std::string pv4;
    std::string range;
    std::string rangeCity;
    std::string rangeCityA;
    std::string rangeHwy;
    std::string rangeHwyA;
    std::string trany;
    std::string UCity;
    std::string UCityA;
    std::string UHighway;
    std::string UHighwayA;
    std::string VClass;
    std::string year;
    std::string youSaveSpend;
    std::string baseModel;
    std::string guzzler;
    std::string trans_dscr;
    std::string tCharger;
    std::string sCharger;
    std::string atvType;
    std::string fuelType2;
    std::string rangeA;
    std::string evMotor;
    std::string mfrCode;
    std::string c240Dscr;
    std::string charge240b;
    std::string c240bDscr;
    std::string createdOn;
    std::string modifiedOn;
    std::string startStop;
    std::string phevCity;
    std::string phevHwy;
    std::string phevComb;

    // Default constructor
    Car(){}

    // Parameterized constructor
    Car(const std::string& b08, const std::string& bA08, const std::string& c120, const std::string& c240,
        const std::string& c08, const std::string& c08U, const std::string& cA08, const std::string& cA08U,
        const std::string& cCD, const std::string& cE, const std::string& cUF, const std::string& co2Val,
        const std::string& co2AVal, const std::string& co2Tagpm, const std::string& co2Tgpm,
        const std::string& comb08Val, const std::string& comb08UVal, const std::string& combA08Val,
        const std::string& combA08UVal, const std::string& combEVal, const std::string& combinedCDVal,
        const std::string& combinedUFVal, const std::string& cylindersVal, const std::string& displVal,
        const std::string& driveVal, const std::string& engIdVal, const std::string& eng_dscrVal,
        const std::string& feScoreVal, const std::string& fuelCost08Val, const std::string& fuelCostA08Val,
        const std::string& fuelTypeVal, const std::string& fuelType1Val, const std::string& ghgScoreVal,
        const std::string& ghgScoreAVal, const std::string& highway08Val, const std::string& highway08UVal,
        const std::string& highwayA08Val, const std::string& highwayA08UVal, const std::string& highwayCDVal,
        const std::string& highwayEVal, const std::string& highwayUFVal, const std::string& hlvVal,
        const std::string& hpvVal, const std::string& idVal, const std::string& lv2Val, const std::string& lv4Val,
        const std::string& makeVal, const std::string& modelVal, const std::string& mpgDataVal,
        const std::string& phevBlendedVal, const std::string& pv2Val, const std::string& pv4Val,
        const std::string& rangeVal, const std::string& rangeCityVal, const std::string& rangeCityAVal,
        const std::string& rangeHwyVal, const std::string& rangeHwyAVal, const std::string& tranyVal,
        const std::string& UCityVal, const std::string& UCityAVal, const std::string& UHighwayVal,
        const std::string& UHighwayAVal, const std::string& VClassVal, const std::string& yearVal,
        const std::string& youSaveSpendVal, const std::string& baseModelVal, const std::string& guzzlerVal,
        const std::string& trans_dscrVal, const std::string& tChargerVal, const std::string& sChargerVal,
        const std::string& atvTypeVal, const std::string& fuelType2Val, const std::string& rangeAVal,
        const std::string& evMotorVal, const std::string& mfrCodeVal, const std::string& c240DscrVal,
        const std::string& charge240bVal, const std::string& c240bDscrVal, const std::string& createdOnVal,
        const std::string& modifiedOnVal, const std::string& startStopVal, const std::string& phevCityVal,
        const std::string& phevHwyVal, const std::string& phevCombVal)
            : barrels08(b08), barrelsA08(bA08), charge120(c120), charge240(c240), city08(c08), city08U(c08U),
              cityA08(cA08), cityA08U(cA08U), cityCD(cCD), cityE(cE), cityUF(cUF), co2(co2Val), co2A(co2AVal),
              co2TailpipeAGpm(co2Tagpm), co2TailpipeGpm(co2Tgpm), comb08(comb08Val), comb08U(comb08UVal),
              combA08(combA08Val), combA08U(combA08UVal), combE(combEVal), combinedCD(combinedCDVal),
              combinedUF(combinedUFVal), cylinders(cylindersVal), displ(displVal), drive(driveVal),
              engId(engIdVal), eng_dscr(eng_dscrVal), feScore(feScoreVal), fuelCost08(fuelCost08Val),
              fuelCostA08(fuelCostA08Val), fuelType(fuelTypeVal), fuelType1(fuelType1Val), ghgScore(ghgScoreVal),
              ghgScoreA(ghgScoreAVal), highway08(highway08Val), highway08U(highway08UVal),
              highwayA08(highwayA08Val), highwayA08U(highwayA08UVal), highwayCD(highwayCDVal),
              highwayE(highwayEVal), highwayUF(highwayUFVal), hlv(hlvVal), hpv(hpvVal), id(idVal),
              lv2(lv2Val), lv4(lv4Val), make(makeVal), model(modelVal), mpgData(mpgDataVal),
              phevBlended(phevBlendedVal), pv2(pv2Val), pv4(pv4Val), range(rangeVal),
              rangeCity(rangeCityVal), rangeCityA(rangeCityAVal), rangeHwy(rangeHwyVal),
              rangeHwyA(rangeHwyAVal), trany(tranyVal), UCity(UCityVal), UCityA(UCityAVal),
              UHighway(UHighwayVal), UHighwayA(UHighwayAVal), VClass(VClassVal), year(yearVal),
              youSaveSpend(youSaveSpendVal), baseModel(baseModelVal), guzzler(guzzlerVal),
              trans_dscr(trans_dscrVal), tCharger(tChargerVal), sCharger(sChargerVal), atvType(atvTypeVal),
              fuelType2(fuelType2Val), rangeA(rangeAVal), evMotor(evMotorVal), mfrCode(mfrCodeVal),
              c240Dscr(c240DscrVal), charge240b(charge240bVal), c240bDscr(c240bDscrVal),
              createdOn(createdOnVal), modifiedOn(modifiedOnVal), startStop(startStopVal),
              phevCity(phevCityVal), phevHwy(phevHwyVal), phevComb(phevCombVal) {
    }

    // Copy constructor
    Car(const Car& other)
            : barrels08(other.barrels08), barrelsA08(other.barrelsA08), charge120(other.charge120), charge240(other.charge240),
              city08(other.city08), city08U(other.city08U), cityA08(other.cityA08), cityA08U(other.cityA08U),
              cityCD(other.cityCD), cityE(other.cityE), cityUF(other.cityUF), co2(other.co2), co2A(other.co2A),
              co2TailpipeAGpm(other.co2TailpipeAGpm), co2TailpipeGpm(other.co2TailpipeGpm),
              comb08(other.comb08), comb08U(other.comb08U), combA08(other.combA08), combA08U(other.combA08U),
              combE(other.combE), combinedCD(other.combinedCD), combinedUF(other.combinedUF),
              cylinders(other.cylinders), displ(other.displ), drive(other.drive),
              engId(other.engId), eng_dscr(other.eng_dscr), feScore(other.feScore), fuelCost08(other.fuelCost08),
              fuelCostA08(other.fuelCostA08), fuelType(other.fuelType), fuelType1(other.fuelType1),
              ghgScore(other.ghgScore), ghgScoreA(other.ghgScoreA), highway08(other.highway08),
              highway08U(other.highway08U), highwayA08(other.highwayA08), highwayA08U(other.highwayA08U),
              highwayCD(other.highwayCD), highwayE(other.highwayE), highwayUF(other.highwayUF),
              hlv(other.hlv), hpv(other.hpv), id(other.id), lv2(other.lv2), lv4(other.lv4),
              make(other.make), model(other.model), mpgData(other.mpgData),
              phevBlended(other.phevBlended), pv2(other.pv2), pv4(other.pv4),
              range(other.range), rangeCity(other.rangeCity), rangeCityA(other.rangeCityA),
              rangeHwy(other.rangeHwy), rangeHwyA(other.rangeHwyA), trany(other.trany),
              UCity(other.UCity), UCityA(other.UCityA), UHighway(other.UHighway),
              UHighwayA(other.UHighwayA), VClass(other.VClass), year(other.year),
              youSaveSpend(other.youSaveSpend), baseModel(other.baseModel), guzzler(other.guzzler),
              trans_dscr(other.trans_dscr), tCharger(other.tCharger), sCharger(other.sCharger),
              atvType(other.atvType), fuelType2(other.fuelType2), rangeA(other.rangeA),
              evMotor(other.evMotor), mfrCode(other.mfrCode), c240Dscr(other.c240Dscr),
              charge240b(other.charge240b), c240bDscr(other.c240bDscr),
              createdOn(other.createdOn), modifiedOn(other.modifiedOn), startStop(other.startStop),
              phevCity(other.phevCity), phevHwy(other.phevHwy), phevComb(other.phevComb) {
    }

    // Copy assignment operator
    Car& operator=(const Car& other) {
        if (this == &other) {
            return *this; // Check for self-assignment
        }

        barrels08 = other.barrels08;
        barrelsA08 = other.barrelsA08;
        charge120 = other.charge120;
        charge240 = other.charge240;
        city08 = other.city08;
        city08U = other.city08U;
        cityA08 = other.cityA08;
        cityA08U = other.cityA08U;
        cityCD = other.cityCD;
        cityE = other.cityE;
        cityUF = other.cityUF;
        co2 = other.co2;
        co2A = other.co2A;
        co2TailpipeAGpm = other.co2TailpipeAGpm;
        co2TailpipeGpm = other.co2TailpipeGpm;
        comb08 = other.comb08;
        comb08U = other.comb08U;
        combA08 = other.combA08;
        combA08U = other.combA08U;
        combE = other.combE;
        combinedCD = other.combinedCD;
        combinedUF = other.combinedUF;
        cylinders = other.cylinders;
        displ = other.displ;
        drive = other.drive;
        engId = other.engId;
        eng_dscr = other.eng_dscr;
        feScore = other.feScore;
        fuelCost08 = other.fuelCost08;
        fuelCostA08 = other.fuelCostA08;
        fuelType = other.fuelType;
        fuelType1 = other.fuelType1;
        ghgScore = other.ghgScore;
        ghgScoreA = other.ghgScoreA;
        highway08 = other.highway08;
        highway08U = other.highway08U;
        highwayA08 = other.highwayA08;
        highwayA08U = other.highwayA08U;
        highwayCD = other.highwayCD;
        highwayE = other.highwayE;
        highwayUF = other.highwayUF;
        hlv = other.hlv;
        hpv = other.hpv;
        id = other.id;
        lv2 = other.lv2;
        lv4 = other.lv4;
        make = other.make;
        model = other.model;
        mpgData = other.mpgData;
        phevBlended = other.phevBlended;
        pv2 = other.pv2;
        pv4 = other.pv4;
        range = other.range;
        rangeCity = other.rangeCity;
        rangeCityA = other.rangeCityA;
        rangeHwy = other.rangeHwy;
        rangeHwyA = other.rangeHwyA;
        trany = other.trany;
        UCity = other.UCity;
        UCityA = other.UCityA;
        UHighway = other.UHighway;
        UHighwayA = other.UHighwayA;
        VClass = other.VClass;
        year = other.year;
        youSaveSpend = other.youSaveSpend;
        baseModel = other.baseModel;
        guzzler = other.guzzler;
        trans_dscr = other.trans_dscr;
        tCharger = other.tCharger;
        sCharger = other.sCharger;
        atvType = other.atvType;
        fuelType2 = other.fuelType2;
        rangeA = other.rangeA;
        evMotor = other.evMotor;
        mfrCode = other.mfrCode;
        c240Dscr = other.c240Dscr;
        charge240b = other.charge240b;
        c240bDscr = other.c240bDscr;
        createdOn = other.createdOn;
        modifiedOn = other.modifiedOn;
        startStop = other.startStop;
        phevCity = other.phevCity;
        phevHwy = other.phevHwy;
        phevComb = other.phevComb;

        return *this;
    }

    void Print() {
        string car_electric;
        if(stoi(charge120) > 0 || stoi(charge240) > 0) {
            car_electric = "electric";
        } else {
            car_electric = "gas";
        }

        cout << year + " " + make + " " + model + ", " + ", " << city08 << ", " << VClass << ", " << car_electric << ", " << drive << endl;
    }
};


#endif //CARINGE_CAR_H
