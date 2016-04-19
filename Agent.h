#ifndef Agent_H
#define Agent_H

/* Class Agent
    Requires 
    radius,
    position_x,
    position_y,
    velocity_x,
    velocity_y,
    average_mass,
*/
class Agent {
private:
    int mass;
    int radius;
public:
    Agent(int r, int m) {
        radius = r;
        mass  = m;
    }
    struct {
        int x;
        int y;
    } position;
    struct {
        float x;
        float y;
    } velocity;
};
#endif
