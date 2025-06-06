#ifndef _RIGID_BODY_HANDLER_H_
#define _RIGID_BODY_HANDLER_H_

#include "Python.h"
#include "SFML/System/Vector2.hpp"
#include "methodobject.h"
#include "rigid_body.h"
#include "box_collider_handler.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class RigidBodyHandler {
public:
  RigidBodyHandler(sf::RenderWindow *window);
  ~RigidBodyHandler();
  void UpdateCurrentAndTimeDelta();
  void UpdatePreviousTime();
  void UpdateForces();
  void UpdatePositions();
  void UpdateAllBodies();
  void CollideBodies();
  void UpdateConstraints();
  void UpdateSim();

  // python Api helper func
  static void SetTerminalVelo(RigidBody *body, const sf::Vector2f &velo);

  //// PYTHON API ////

  // Time specific
  static PyObject *GetCurrentTime(PyObject *self, PyObject *args);
  static PyObject *GetDeltaTime(PyObject *self, PyObject *args);

  // RigidBody specific
  static PyObject *CreateRigidBody(PyObject *self, PyObject *args);

  static PyObject *IsRigidBodyStatic(PyObject *self, PyObject *args);
  static PyObject *SetRigidBodyStatic(PyObject *self, PyObject *args);
  static PyObject *IsRigidBodyGravity(PyObject *self, PyObject *args);
  static PyObject *SetRigidBodyGravity(PyObject *self, PyObject *args);

  static PyObject *GetRigidBodyLayer(PyObject *self, PyObject *args);
  static PyObject *SetRigidBodyLayer(PyObject *self, PyObject *args);

  static PyObject *GetRigidBodyVelocity(PyObject *self, PyObject *args);
  static PyObject *SetRigidBodyVelocity(PyObject *self, PyObject *args);

  static PyObject *GetRigidBodyPosition(PyObject *self, PyObject *args);
  static PyObject *SetRigidBodyPosition(PyObject *self, PyObject *args);

  static PyObject *SetRigidBodySize(PyObject *self, PyObject *args);
  static PyObject *GetRigidBodySize(PyObject *self, PyObject *args);

  static PyObject *SetRigidBodyCallback(PyObject *self, PyObject *args);

  static PyObject *DrawRigidBodyCollider(PyObject *self, PyObject *args);
  static PyObject *FreeRigidBody(PyObject *self, PyObject *args);

  static PyObject *SetGravity(PyObject *self, PyObject *args);
  static PyObject *SetTerminalVelo(PyObject *self, PyObject *args);

  static PyObject* RigidBodyCollidesWith(PyObject* self, PyObject* args);

  /**
   * @param self required for python api functions
   * @paarm args a tuple containing the arguments for the function. Should
   * contain a long as id for the body and 2 floats
   * @brief The API for applying a force to a rigid body
   */
  static PyObject *ApplyForce(PyObject *self, PyObject *args);

  

private:
  /**
   *  @brief A helper function to the python API
   *  @param body The body to apply the force to
   *  @param force The force to apply to the body
   *  @return True if function succeded, false otherwise
   */
  static bool ApplyForce(RigidBody *body, const sf::Vector2f &force);

  /**
   *  @brief A helper function to the python API
   *  @param body The body to apply the force to
   *  @param x The x component of the force to be applied
   *  @param The y component of the force to be applied
   *  @return True if function succeded, false otherwise
   */
  static bool ApplyForce(RigidBody *body, float x, float y);
  //  static sf::Vector2f gravity;
};

//// PYTHON DOCS ////
// corresponding documentation for engine_delta_time
PyDoc_STRVAR(engine_delta_time_doc,
             ".. function:: delta_time()\n"
             "\n"
             "  Returns the delta time (essentially how many seconds has "
             "passed since the last frame) of the engine.\n"
             "\n"
             "  :return: a float representing the delta time in seconds.\n");

// corresponding documentation for engine_current_time
PyDoc_STRVAR(engine_current_time_doc,
             ".. function:: current_time()\n"
             "\n"
             "  Returns the current time (relevant to the engine) in seconds.\n"
             "\n"
             "  :return: a float representing the current time in seconds.\n");

// corresponding documentation for engine_create_sprite
PyDoc_STRVAR(engine_create_rigid_body_doc,
             ".. function:: create_rigid_body((posx,posy),(width,height))\n"
             "\n"
             "  Creates a rigid body with the specified position (first arg) "
             "and size (second arg).\n"
             "\n"
             "  :return: an integer representing the rigid body's id.\n");

// corresponding documentation for engine_is_rigid_body_static
PyDoc_STRVAR(engine_is_rigid_body_static_doc,
             ".. function:: is_rigid_body_static(id)\n"
             "\n"
             "  Checks if the rigid body with the specified id is static.\n"
             "\n"
             "  :return: A boolean.\n");

// corresponding documentation for engine_set_rigid_body_static
PyDoc_STRVAR(engine_set_rigid_body_static_doc,
             ".. function:: set_rigid_body_static(id, bool)\n"
             "\n"
             "  Sets the rigid body to be static or not with the specified id "
             "the passed bool.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_is_rigid_body_gravity
PyDoc_STRVAR(engine_is_rigid_body_gravity_doc,
             ".. function:: is_rigid_body_gravity(id)\n"
             "\n"
             "  Checks if the rigid body with the specified id has gravity.\n"
             "\n"
             "  :return: A boolean.\n");

// corresponding documentation for engine_set_rigid_body_gravity
PyDoc_STRVAR(engine_set_rigid_body_gravity_doc,
             ".. function:: set_rigid_body_gravity(id, bool)\n"
             "\n"
             "  Sets the rigid body to have gravity or not with the specified "
             "id the passed bool.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_get_rigid_body_layer
PyDoc_STRVAR(engine_get_rigid_body_layer_doc,
             ".. function:: get_rigid_body_layer(id)\n"
             "\n"
             "  Gets and returns the rigid body's collision layer.\n"
             "\n"
             "  :return: A long.\n");

// corresponding documentation for engine_set_rigid_body_layer
PyDoc_STRVAR(engine_set_rigid_body_layer_doc,
             ".. function:: set_rigid_body_layer(id, layer)\n"
             "\n"
             "  Sets the rigid body to be on the provided collision layer"
             "  , a long in the range 0-7 inclusive.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_set_rigid_body_velocity
PyDoc_STRVAR(engine_set_rigid_body_velocity_doc,
             ".. function:: set_rigid_body_velocity(id, tuple(float "
             "x, float y)))\n"
             "\n"
             "  Sets the rigid body to have the speicified velocity.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_get_rigid_body_position
PyDoc_STRVAR(engine_get_rigid_body_position_doc,
             ".. function:: get_rigid_body_position(id)\n"
             "\n"
             "  Gets the position of the a rigid body with the specified id.\n"
             "\n"
             "  :return: A tuple of floats (x,y).\n");

// corresponding documentation for engine_set_rigid_body_position
PyDoc_STRVAR(engine_set_rigid_body_position_doc,
             ".. function:: set_rigid_body_position(id,(x,y))\n"
             "\n"
             "  Sets the position of the a rigid body with the specified id to "
             "the new x and y.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_set_rigid_body_size
PyDoc_STRVAR(engine_get_rigid_body_size_doc,
             ".. function:: get_rigid_body_size(id)\n"
             "\n"
             "  Gets the size of the a rigid body with the specified id.\n"
             "\n"
             "  :return: A tuple of floats (width,height).\n");

// corresponding documentation for engine_set_rigid_body_size
PyDoc_STRVAR(engine_set_rigid_body_size_doc,
             ".. function:: set_rigid_body_size(id,(width,height))\n"
             "\n"
             "  Sets the size of the a rigid body with the specified id to the "
             "new width and height.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_set_rigid_body_callback
PyDoc_STRVAR(engine_set_rigid_body_callback_doc,
             ".. function:: set_rigid_body_callback(id, callback)\n"
             "\n"
             "  Sets a function callback to be called upon the specified object"
             "  colliding with another rigid body.\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_draw_rigid_body_collider
PyDoc_STRVAR(engine_draw_rigid_body_collider_doc,
             ".. function:: draw_rigid_body_collider(id)\n"
             "\n"
             "  Given an id of a rigid body, draw a neon green box outline of "
             "the box collider\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_free_rigid_body
PyDoc_STRVAR(engine_free_rigid_body_doc,
             ".. function:: free_rigid_body(id)\n"
             "\n"
             "  Given an id of a rigid body, free the memory being used, and "
             "allow the id to be used for a new rigid body\n"
             "\n"
             "  :return: Nothing.\n");

// corresponding documentation for engine_set_gravity
PyDoc_STRVAR(engine_set_gravity_doc,
             ".. function:: set_gravity(x, y)\n"
             "\n"
             " set the x and y component of engines gravity\n"
             "\n"
             "  :return: Nothing.\n");

/* This will likely need to be reworked into each rigid body, since it make
 * more sense there. */
// corresponding documentation for engine_set_gravity
PyDoc_STRVAR(engine_set_terminal_velo_doc,
             ".. function:: set_terminal_velo(x, y)\n"
             "\n"
             " set the x and y component of engines terminal velocity\n"
             "\n"
             "  :return: Nothing.\n");

PyDoc_STRVAR(engine_apply_force_doc, ".. function:: apply_force(x, y)\n"
                                     "\n"
                                     " apply a force to an object\n"
                                     "\n"
                                     "  :return: Nothing.\n");

// corresponding documentation for get_rigid_body_velocity
PyDoc_STRVAR(engine_get_rigid_body_velocity_doc,
             ".. function:: get_rigid_body_velocity(id)\n"
             "\n"
             "  Gets the velocity of the a rigid body with the specified id.\n"
             "\n"
             "  :return: A tuple of floats (x,y).\n");

PyDoc_STRVAR(engine_rigid_body_collides_with_doc, 
  "function:: rigid_body_collides_with(id1,id2)\n"
  "\n"
  " check if a rigid body is colliding with anything\n"
  "\n"
  "::return bool"
);

static PyMethodDef set_gravity = {"set_gravity", RigidBodyHandler::SetGravity,
                                  METH_VARARGS, engine_set_gravity_doc};
static PyMethodDef set_terminal_velo = {
    "set_terminal_velo", RigidBodyHandler::SetTerminalVelo, METH_VARARGS,
    engine_set_terminal_velo_doc};

static PyMethodDef apply_force = {"apply_force", RigidBodyHandler::ApplyForce,
                                  METH_VARARGS, engine_apply_force_doc};

static PyMethodDef get_velocity = {
    "get_rigid_body_velocity", RigidBodyHandler::GetRigidBodyVelocity,
    METH_VARARGS, engine_get_rigid_body_velocity_doc};

#endif //_RIGID_BODY_HANDLER_H_
