#include "rigid_body.h"
#include <SFML/System.hpp>

RigidBody::RigidBody(sf::Vector2f new_position, sf::Vector2f new_size){
    box = new BoxCollider();
    box->setPosition(new_position.x,new_position.y);
    box->setSize(new_size.x,new_size.y);
}

RigidBody::RigidBody(sf::Vector2f new_position, sf::Vector2f new_size, bool new_static){
    static_ = new_static;
    box = new BoxCollider();
    box->setPosition(new_position.x,new_position.y);
    box->setSize(new_size.x,new_size.y);
}

RigidBody::RigidBody(sf::Vector2f new_position, sf::Vector2f new_size, bool new_static, bool gravity_) {
    static_ = new_static;
    gravity = gravity_;
    box = new BoxCollider();
    box->setPosition(new_position.x,new_position.y);
    box->setSize(new_size.x,new_size.y);
}

RigidBody::~RigidBody() {
    delete box;
}

bool RigidBody::IsStatic(){return static_;}
void RigidBody::SetStatic(bool new_static) {static_ = new_static;};
bool RigidBody::IsGravity() { return gravity;}
void RigidBody::SetGravity(bool new_gravity) {gravity = new_gravity;}

sf::Vector2f RigidBody::GetVelocity() {return velocity;}
void RigidBody::SetVelocity(float x, float y) {velocity.x = x; velocity.y = y;}
void RigidBody::SetVelocity(const sf::Vector2f &new_velocity) {velocity = new_velocity;}
void RigidBody::ModifyVelocity(float x, float y) {velocity.x += x; velocity.y += y;}
void RigidBody::ModifyVelocity(const sf::Vector2f &new_velocity) {velocity.x += new_velocity.x; velocity.y += new_velocity.y;}
void RigidBody::UpdateByVelocity(float gravity_const, double delta) {
    if (static_) return;

    //printf("Updating body by velocity, with gravity of %f\n",gravity_const);

    sf::Vector2f box_position = box->getPosition();

    //printf("Current Position: %f %f\n", box_position.x, box_position.y);

    if(!gravity) {
        SetPosition({box_position.x+velocity.x*delta,box_position.y+velocity.y*delta});
    }else {
        SetPosition({box_position.x+velocity.x*delta,box_position.y+(velocity.y+gravity_const)*delta});
    }
    box_position = box->getPosition();
    //printf("New Position: %f %f\n", box_position.x, box_position.y);
}

sf::Vector2f RigidBody::GetPosition() {return box->getPosition();}
void RigidBody::SetPosition(const sf::Vector2f &new_position) {box->setPosition(new_position.x,new_position.y);}

sf::Vector2f RigidBody::GetSize() {return box->getSize();}
void RigidBody::SetSize(const sf::Vector2f &new_size) {box->setSize(new_size.x,new_size.y);}

void RigidBody::DrawOutline(sf::RenderWindow* window, sf::Color color) {
    sf::RectangleShape outline;
    outline.setPosition(GetPosition());
    outline.setSize(GetSize());
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(color);
    outline.setOutlineThickness(2);
    window->draw(outline);
}

bool RigidBody::CollidesWith(RigidBody* other) {return box->CollidesWith(other->box);}
bool RigidBody::CollidesWith(BoxCollider* other) {return box->CollidesWith(other);}
