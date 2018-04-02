/*
 * MenuOptions.cpp
 *
 *  Created on: Mar 24, 2018
 *      Author: justin
 */


#include "MenuOptions.h"

#include <iostream>
#include <regex>


std::string MenuOptions::getUserName() {
    bool validated = false;
    std::string input;
    while(!validated){
        std::cout << "Please enter username\n";
        std::getline(std::cin, input);
        if (input.find(";") != std::string::npos) {
            std::cout << "Username cannot contain the ; character" << '\n';
        }else{
            validated = true;
        }
    }
    return input;
}

std::string MenuOptions::getPassword() {
    bool validated = false;
    std::string input;
    while(!validated){
        std::cout << "Please enter password\n";
        std::getline(std::cin, input);
        if (input.find(";") != std::string::npos) {
            std::cout << "Password cannot contain the ; character" << '\n';
        }else{
            validated = true;
        }
    }
    return input;
}

std::string MenuOptions::getTimeDate(std::string dateType) {
    bool validated = false;
    std::string input;
    while(!validated){
        if(!dateType.compare("OLD")){
            std::cout << "Please enter old appointment time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
        }else if(!dateType.compare("UPDATE")){
            std::cout << "Please enter updated new appointment time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
        }else if(!dateType.compare("START")){
            std::cout << "Please enter the starting time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
        }else if(!dateType.compare("END")){
            std::cout << "Please enter the ending time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
        }else {
            std::cout << "Please enter new appointment time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
        }
        std::getline(std::cin, input);
        std::regex pattern("^\\d{2}[\\:]\\d{2}[[:space:]]\\d{2}[\\/]\\d{2}[\\/]\\d{4}$");
        if (!std::regex_match(input, pattern)) {
            std::cout << "Time & date must be in hh:mm mm/dd/yyyy format please try again" << '\n';
        }else{
            validated = true;
        }
    }
    return input;
}

std::string MenuOptions::getMemo(std::string dateType) {
    bool validated = false;
    std::string input;
    while(!validated){
        if(!dateType.compare("OLD")){
            std::cout << "Please enter old appointment reason\n";
        }else if(!dateType.compare("UPDATE")){
            std::cout << "Please enter updated appointment reason\n";
        }else {
            std::cout << "Please enter new appointment reason\n";
        }
        std::getline(std::cin, input);
        if (input.find(";") != std::string::npos) {
            std::cout << "Your appointment reason cannot contain the ; character" << '\n';
        }else{
            validated = true;
        }
    }
    return input;
}

std::string MenuOptions::getPlace(std::string dateType) {
    bool validated = false;
    std::string input;
    while(!validated){
        if(!dateType.compare("OLD")){
            std::cout << "Please enter old appointment place\n";
        }else if(!dateType.compare("UPDATE")){
            std::cout << "Please enter updated appointment place\n";
        }else {
            std::cout << "Please enter new appointment place\n";
        }
        std::getline(std::cin, input);
        if (input.find(";") != std::string::npos) {
            std::cout << "Your appointment place cannot contain the ; character" << '\n';
        }else{
            validated = true;
        }
    }
    return input;
}


std::string getName() {
    bool validated = false;
    std::string input;
    while(!validated){
        std::cout << "Please enter name\n";
        std::getline(std::cin, input);
        if (input.find(";") != std::string::npos) {
            std::cout << "Your name cannot contain the ; character" << '\n';
        }else{
            validated = true;
        }
    }
    return input;
}

std::string MenuOptions::getEmail() {
    bool validated = false;
    std::string input;
    while(!validated){
        std::cout << "Please enter your email\n";
        std::getline(std::cin, input);
        if (input.find(";") != std::string::npos) {
            std::cout << "Your email cannot contain the ; character" << '\n';
        }else{
            validated = true;
        }
    }
    return input;
}


std::string MenuOptions::getPhone() {
    bool validated = false;
    std::string input;
    while(!validated){
        std::cout << "Please enter phone consisting of only 10 digits\n";
        std::getline(std::cin, input);
        std::regex pattern("^\\d{10}$");
        if (!std::regex_match(input, pattern)) {
            std::cout << "Your phone can only consist of 10 digits" << '\n';
        }else{
            validated = true;
        }
    }
    return input;
}

