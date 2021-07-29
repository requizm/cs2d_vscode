#ifndef TIMER_H
#define TIMER_H
class Timer
{
   public:
    Timer() = default;
    ~Timer() = default;

    static float DeltaTime;
    static float timeSinceAppStart;
    static float timeSinceSceneStart;

    static void Update(float dt);
};

#endif  // TIMER_H
