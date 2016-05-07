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
    float mass;
    float radius;
    struct position { float x; float y;};
    struct velocity { float x; float y;};
public:
    Agent(){};
    ~Agent(){};
    int set_values();
};

int Agent::set_values(int x, int y, float vx, float vy, float m, float r) {
    mass = m; radius = r; position.x = x; position.y = y; velocity.x = vx; velocity.y = vy;
    return 0;
}
#endif
