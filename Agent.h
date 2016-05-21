#ifndef Agent_H
#define Agent_H

#include "Floor.h"

class Agent {

public:
    bool active;
    float mass;
    float radius;
    Floor current_floor;
    Floor::Tile position;
    float speed;
    struct Velocity { float x; float y;} velocity;
    struct Acceleration { float x; float y;} acceleration;
    struct Repulsion_force { float x; float y;} repulsion_force;
public:
    Agent():active{1}{};
    ~Agent(){};
    int set_values(Floor&, int, int, float, float, float, float);
    int calculate_repulsion(int);
    int update_acceleration();
    int update_velocity();
    int update_position();
};

int Agent::set_values(Floor& f, int x, int y, float vx, float vy, float m, float r) {
    current_floor = f;  position = f.get_tile(y, x); velocity.x = vx; velocity.y=vy; mass = m; radius = r;  
    return 0;
}

int Agent::calculate_repulsion(int agent) {
    return 0;
}

int Agent::update_position() {
    position = current_floor.get_tile( position.row + velocity.y /* *time_step */ , position.col + velocity.x/* *time_step */);
    return 0;
}
int Agent::update_velocity() {
    velocity.x = acceleration.x /* multiply by timeStep -> assumed 1s for now */;
    velocity.y = acceleration.y /* multiply by timeStep -> assumed 1s for now */;
    return 0;
}
int Agent::update_acceleration() {
    acceleration.x = position.desired_direction_in_x;
    acceleration.y = position.desired_direction_in_y;
    return 0;
}

#endif
