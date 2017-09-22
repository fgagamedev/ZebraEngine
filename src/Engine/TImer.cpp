/*
    @file Timer.cpp
    @brief Class responsible for managing time.
    @copyright LGPL. MIT License.
*/
#include "Engine/Timer.hpp"

/*
    @brief Start time.
*/
Timer::Timer() {
	time = 0;
}

/*
    @brief Update time.
    @param[in] detectiontTime.
*/
void Timer::Update(float detectiontTime){
	time = time + detectiontTime;
}

/*
    @brief Restart time from zero.
*/
void Timer::Restart(){
	time = 0;
}

/*
    @brief Take the time and add to the variable time.
    @return time In minutes.
*/
float Timer::GetTime(){
	return time;
}
