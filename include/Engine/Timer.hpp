/*
    @file Timer.hpp
    @brief Class responsible for managing time.
    @copyright LGPL. MIT License.
*/
#ifndef __TIMER_H__
#define __TIMER_H__

    class Timer{
        public:
            Timer();
            void Update(float detectiontTime);
            void Restart();
            float GetTime();

        private:
            float time;
    };

#endif
