#ifndef _RIGID_BODY_H_
#define _RIGID_BODY_H_

#include "box_collider.hpp"

class RigidBody {
    public:
    RigidBody(sf::Vector2f new_position, sf::Vector2f new_size);
    RigidBody(sf::Vector2f new_position, sf::Vector2f new_size, bool new_static);
    RigidBody(sf::Vector2f new_position, sf::Vector2f new_size, bool new_static, bool gravity_);
    ~RigidBody();
    
    bool IsStatic();
    void SetStatic(bool new_static);
    bool IsGravity();
    void SetGravity(bool new_gravity);

    sf::Vector2f GetVelocity();
    void SetVelocity(float x, float y);
    void SetVelocity(sf::Vector2f new_velocity);
    void ModifyVelocity(float x, float y);
    void ModifyVelocity(sf::Vector2f new_velocity);
    void UpdateByVelocity(float gravity_const, double delta);

    sf::Vector2f GetPosition();
    void SetPosition(sf::Vector2f new_position);

    sf::Vector2f GetSize();
    void SetSize(sf::Vector2f new_size);

    void DrawOutline(sf::RenderWindow* window, sf::Color color);

    bool CollidesWith(RigidBody* other);
    bool CollidesWith(BoxCollider* other);

    private:
    bool static_ = false;
    bool gravity = true;
    sf::Vector2f velocity = {0,0};
    
    BoxCollider* box;
};

#endif //_RIGID_BODY_H_