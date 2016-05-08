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
    bool active;
    float mass;
    float radius;
    struct position { float x; float y;};
    struct velocity { float x; float y;};
    struct repulsion_force { float x; float y;};
public:
    Agent():active{1}{};
    ~Agent(){};
    int set_values(float, float, float, float, float, float);
    // int calculate_repulsion();
};

int Agent::set_values(float x, float y, float vx, float vy, float m, float r) {
    position{x,y}; velocity{vx, vy}; mass = m; radius = r; 
    return 0;
}
#endif
