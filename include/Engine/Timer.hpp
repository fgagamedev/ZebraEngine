#ifndef TIMER_H
#define TIMER_H

class Timer{

public:
  Timer();
  void Update(float dt);
  void Restart();
  float GetTime();

private:
  float time;
};

#endif //TIMER_H
