/*
 * Utilities.cpp
 *
 *  Created on: Mar 24, 2018
 *      Author: justin
 */


#include <iostream>
#include <regex>
#include "Utilities.h"

using namespace std;

std::string getUserName() {
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

std::string getPassword() {
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

std::string getDate(std::string dateType) {
    bool validated = false;
    std::string input;
    while(!validated){
        if(!dateType.compare("OLD")){
            std::cout << "Please enter old appointment date in the format mm/dd/yyyy\n";
        }else if(!dateType.compare("UPDATE")){
            std::cout << "Please enter updated new appointment date in the format mm/dd/yyyy\n";
        }else if(!dateType.compare("START")){
            std::cout << "Please enter the starting date in the format mm/dd/yyyy\n";
        }else if(!dateType.compare("END")){
            std::cout << "Please enter the ending date in the format mm/dd/yyyy\n";
        }else {
            std::cout << "Please enter new appointment date in the format mm/dd/yyyy\n";
        }
        std::getline(std::cin, input);
        std::regex pattern("^\\d{2}[\\/]\\d{2}[\\/]\\d{4}$");
        if (!std::regex_match(input, pattern)) {
            std::cout << "Date must be in mm/dd/yyyy format please try again" << '\n';
        }else{
            validated = true;
        }
    }
    return input;
}

std::string getTime(std::string timeType) {
    bool validated = false;
    std::string input;
    while(!validated){
        if(!timeType.compare("OLD")){
            std::cout << "Please enter old appointment time in the format hh:mm using the 24 hour clock\n";
        }else if(!timeType.compare("UPDATE")){
            std::cout << "Please enter updated appointment time in the format hh:mm using the 24 hour clock\n";
        }else if(!timeType.compare("START")){
            std::cout << "Please enter starting time in the format hh:mm using the 24 hour clock\n";
        }else if(!timeType.compare("END")){
            std::cout << "Please enter ending time in the format hh:mm using the 24 hour clock\n";
        }else {
            std::cout << "Please enter new appointment time in the format hh:mm using the 24 hour clock\n";
        }
        std::getline(std::cin, input);
        std::regex pattern("^\\d{2}[\\:]\\d{2}$");
        if (!std::regex_match(input, pattern)) {
            std::cout << "Date must be in mm/dd/yyyy format please try again" << '\n';
        }else{
            validated = true;
        }
    }
    return input;
}

std::string getReason(std::string dateType) {
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

std::string getEmail() {
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


std::string getPhone() {
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

