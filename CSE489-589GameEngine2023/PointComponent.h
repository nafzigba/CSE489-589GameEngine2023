#pragma once
#include "component.h"
class PointComponent
{
public:
    static int score;
    static int getScore() { return score; };
    static void setScore(int pts) {
        score += pts;
        cout <<"Your Score is: " << score << endl;
    };
protected:
};

