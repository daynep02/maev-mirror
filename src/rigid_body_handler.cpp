#include "rigid_body_handler.h"
#include "SFML/System/Vector2.hpp"
#include "common_helpers.h"
#include "longobject.h"
#include "object.h"
#include "rigid_body.h"
#include <algorithm>
#include <chrono>
#include <limits>
#include <vector>
#include <iostream>

sf::RenderWindow *rigid_window;

std::chrono::_V2::steady_clock::time_point current_time;
std::chrono::_V2::steady_clock::time_point previous_time;
std::chrono::duration<double> delta_time;

std::vector<RigidBody *> rigid_bodies;
std::vector<long> free_rigid_bodies;

static sf::Vector2f gravity = {0.0f, 0.0f};
static sf::Vector2f terminalVelo = {std::numeric_limits<float>::max(),
                                    std::numeric_limits<float>::max()};

RigidBodyHandler::RigidBodyHandler(sf::RenderWindow *window) {
  rigid_window = window;
}

RigidBodyHandler::~RigidBodyHandler() {
  std::for_each(rigid_bodies.begin(), rigid_bodies.end(), delete_ptr());
  rigid_bodies.clear();
}

void RigidBodyHandler::UpdateCurrentAndTimeDelta() {
  using namespace std::chrono;
  current_time = steady_clock::now();
  // we don't want the first frame to teleport items
  delta_time = current_time - previous_time;
}

void RigidBodyHandler::UpdatePreviousTime() { previous_time = current_time; }

void RigidBodyHandler::UpdateAllBodies() {
  for (const auto& body : rigid_bodies) {
    body->ApplyGravity(gravity);
    body->UpdateByVelocity(gravity, delta_time.count());
  }
}

void RigidBodyHandler::CollideBodies() {

  // check for collisions
  //  bug: suffers from a "too fast" problem where a collision won't be dfloat ,
  //  float yetected
  //       if a body is going so fast that it basically teleports across a body
  //       inbetween frames
  //  fix: move it one pixel from it's previous position every step to check for
  //  a collision,
  //       too tired to implement it rn
  for (int i = 0; i < rigid_bodies.size(); i++) {
    RigidBody *body_i = rigid_bodies.at(i);
    // checking other rigid bodies
    for (int j = i + 1; j < rigid_bodies.size(); j++) {
      RigidBody *body_j = rigid_bodies.at(j);
      if (body_i->CollidesWith(body_j)) {
        body_i->Collide(body_j, gravity, delta_time.count());
        if(body_i->GetCallback()!=NULL) {
          PyObject* args = PyTuple_New(2);
          PyTuple_SetItem(args,0,PyLong_FromLong(i));
          PyTuple_SetItem(args,1,PyLong_FromLong(j));
          PyObject_Call(body_i->GetCallback(),args,NULL);
          Py_DecRef(args);
        }
        if(body_j->GetCallback()!=NULL) {
          PyObject* args = PyTuple_New(2);
          PyTuple_SetItem(args,0,PyLong_FromLong(j));
          PyTuple_SetItem(args,1,PyLong_FromLong(i));
          PyObject_Call(body_j->GetCallback(),args,NULL);
          Py_DecRef(args);
        }
        //continue;
      }
    }
    //checking box colliders that are active triggers
    std::vector<BoxCollider*>*boxes = BoxColliderHandler::GetBoxVector();
    for (int b = 0; b < boxes->size(); b++) {
      BoxCollider *box = boxes->at(b);
      if (box->isTrigger) {
        if (body_i->CollidesWith(box)) {
          if(box->GetCallback()!= NULL) {
            PyTuple_Pack(2, PyLong_FromLong(b), PyLong_FromLong(i));
            PyObject* args1 = PyTuple_Pack(2, PyLong_FromLong(b), PyLong_FromLong(i));
            PyObject_Call(box->GetCallback(),args1,NULL);
            Py_DecRef(args1);
          }
        }
      }
    }
  }
}

void RigidBodyHandler::UpdateSim() {
  UpdateAllBodies();
  CollideBodies();
}

void RigidBodyHandler::SetTerminalVelo(RigidBody *body,
                                       const sf::Vector2f &velo) {
  body->SetTerminalVelo(velo);
}

/*static*/ PyObject *RigidBodyHandler::GetCurrentTime(PyObject *self,
                                                      PyObject *args) {
  auto time = std::chrono::duration_cast<std::chrono::duration<double>>(
      current_time.time_since_epoch());
  return PyFloat_FromDouble(time.count());
}

/*static*/ PyObject *RigidBodyHandler::GetDeltaTime(PyObject *self,
                                                    PyObject *args) {
  return PyFloat_FromDouble(delta_time.count());
}

/*static*/ PyObject *RigidBodyHandler::CreateRigidBody(PyObject *self,
                                                       PyObject *args) {
  long loc; // address in array to store box collider

  // parse python arguments
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.create_rigid_body expects a two tuples of size 2 as an "
           "argument\n");
    PyErr_BadArgument();
  }

  PyObject *pPos = PyTuple_GetItem(args, 0);
  Py_ssize_t pPos_nargs = PyTuple_GET_SIZE(pPos);
  if (pPos_nargs != 2) {
    printf("engine.create_rigid_body expects a two tuples of size 2 as an "
           "argument\n");
    PyErr_BadArgument();
  }

  PyObject *pSize = PyTuple_GetItem(args, 1);
  Py_ssize_t pSize_nargs = PyTuple_GET_SIZE(pSize);
  if (pPos_nargs != 2) {
    printf("engine.create_rigid_body expects a two tuples of size 2 as an "
           "argument\n");
    PyErr_BadArgument();
  }

  PyObject *pX = PyTuple_GetItem(pPos, 0);
  PyObject *pY = PyTuple_GetItem(pPos, 1);
  PyObject *pWidth = PyTuple_GetItem(pSize, 0);
  PyObject *pHeight = PyTuple_GetItem(pSize, 1);

  double x = PyFloat_AsDouble(pX);
  double y = PyFloat_AsDouble(pY);
  double width = PyFloat_AsDouble(pWidth);
  double height = PyFloat_AsDouble(pHeight);

  if (!free_rigid_bodies.empty()) {
    loc = free_rigid_bodies.back();
    printf("engine.create_rigid_body: Using Free Rigid Bodies\n");
    free_rigid_bodies.pop_back();
    printf("engine.create_rigid_body: Adding to Vector\n");
    RigidBody *body =
        new RigidBody(sf::Vector2f(x, y), sf::Vector2f(width, height));
    delete rigid_bodies.at(loc);
    rigid_bodies.at(loc) = body;
  } else {
    RigidBody *body =
        new RigidBody(sf::Vector2f(x, y), sf::Vector2f(width, height));
    rigid_bodies.push_back(body);
    loc = rigid_bodies.size() - 1;
  }

  printf("engine.create_rigid_body: Returning ID %lu\n", loc);

  // Py_XDECREF(pName);

  return PyLong_FromLong(loc);
}

/*static*/ PyObject *RigidBodyHandler::IsRigidBodyStatic(PyObject *self,
                                                         PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf(
        "engine.is_rigid_body_static expects a single long as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf(
        "engine.is_rigid_body_static expects a single long as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.is_rigid_body_static got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  // Py_XDECREF(pId);

  if (rigid_bodies.at(id)->IsStatic()) {
    Py_RETURN_TRUE;
  }

  Py_RETURN_FALSE;
}

/*static*/ PyObject *RigidBodyHandler::SetRigidBodyStatic(PyObject *self,
                                                          PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_rigid_body_static expects a single long and a bool as "
           "arguments\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_rigid_body_static expects a single long and a bool as "
           "arguments\n");
    PyErr_BadArgument();
  }
  PyObject *pB = PyTuple_GetItem(args, 1);
  if (!PyBool_Check(pB)) {
    Py_XDECREF(pB);
    printf("engine.set_rigid_body_static expects a single long and a bool as "
           "arguments\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);
  long b = PyLong_AsLong(pB);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    Py_XDECREF(pB);
    printf("engine.set_rigid_body_static got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  rigid_bodies.at(id)->SetStatic(b);

  Py_RETURN_NONE;
}

/*static*/ PyObject *RigidBodyHandler::IsRigidBodyGravity(PyObject *self,
                                                          PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf(
        "engine.is_rigid_body_gravity expects a single long as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf(
        "engine.is_rigid_body_gravity expects a single long as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.is_rigid_body_gravity got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  if (rigid_bodies.at(id)->IsGravity()) {
    Py_RETURN_TRUE;
  }

  Py_RETURN_FALSE;
}

/*static*/ PyObject *RigidBodyHandler::SetRigidBodyGravity(PyObject *self,
                                                           PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_rigid_body_gravity expects a single long and a bool as "
           "arguments\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_rigid_body_gravity expects a single long and a bool as "
           "arguments\n");
    PyErr_BadArgument();
  }
  PyObject *pB = PyTuple_GetItem(args, 1);
  if (!PyBool_Check(pB)) {
    Py_XDECREF(pB);
    printf("engine.set_rigid_body_gravity expects a single long and a bool as "
           "arguments\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);
  long b = PyLong_AsLong(pB);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    Py_XDECREF(pB);
    printf("engine.set_rigid_body_static got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  rigid_bodies.at(id)->SetGravity(b);

  Py_RETURN_NONE;
}

PyObject *RigidBodyHandler::SetRigidBodyVelocity(PyObject *self,
                                                 PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_rigid_body_velocity expects a long and a tuple of "
           "length two as arguments\n");
    PyErr_BadArgument();
  }

  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_rigid_body_velocity expects a long and a tuple of "
           "length two as arguments\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.set_rigid_body_velocity got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  // Parse the velocity tuple //should be changed to vectors later
  PyObject *pVel = PyTuple_GetItem(args, 1);
  Py_ssize_t nargs_vel = PyTuple_GET_SIZE(pVel);
  if (nargs_vel != 2) {
    printf("engine.set_rigid_body_velocity expects a long and a tuple of "
           "length two as arguments\n");
    PyErr_BadArgument();
  }

  PyObject *pVelX = PyTuple_GetItem(pVel, 0);
  if (!PyFloat_Check(pVelX)) {
    Py_XDECREF(pVelX);
    printf(
        "engine.set_rigid_body_velocity expects a long and a tuple of length "
        "two as arguments - the first argument of the tuple is not a float\n");
    PyErr_BadArgument();
  }

  PyObject *pVelY = PyTuple_GetItem(pVel, 1);
  if (!PyFloat_Check(pVelY)) {
    Py_XDECREF(pVelY);
    printf(
        "engine.set_rigid_body_velocity expects a long and a tuple of length "
        "two as arguments - the second argument of the tuple is not a float\n");
    PyErr_BadArgument();
  }

  double x = PyFloat_AsDouble(pVelX);
  double y = PyFloat_AsDouble(pVelY);

  rigid_bodies[id]->SetVelocity(x, y);

  Py_RETURN_NONE;
}

/*static*/ PyObject *RigidBodyHandler::GetRigidBodyPosition(PyObject *self,
                                                            PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.get_rigid_body_position expects a single long as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.get_rigid_body_position expects a single long as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.get_rigid_body_position got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  // printf("engine.draw_rigid_body_collider: Drawing Collider %lu\n",id);

  sf::Vector2f position = rigid_bodies.at(id)->GetPosition();

  PyObject *x = PyFloat_FromDouble(position.x);
  PyObject *y = PyFloat_FromDouble(position.y);

  PyObject *pPos = PyTuple_Pack(2, x, y);

  // Py_XDECREF(pId);
  // printf("engine.draw_rigid_body_collider: Returning\n");

  return pPos;
}

/*static*/ PyObject *RigidBodyHandler::GetRigidBodyVelocity(PyObject *self,
                                                            PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.get_rigid_body_velocity expects a single long as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.get_rigid_body_velocity expects a single long as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.get_rigid_body_velocity got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  const sf::Vector2f &velo = rigid_bodies.at(id)->GetVelocity();

  PyObject *x = PyFloat_FromDouble(velo.x);
  PyObject *y = PyFloat_FromDouble(velo.y);

  PyObject *pPos = PyTuple_Pack(2, x, y);

  return pPos;
}

/*static*/ PyObject *RigidBodyHandler::SetRigidBodyPosition(PyObject *self,
                                                            PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_rigid_body_position expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_rigid_body_position expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.set_rigid_body_position got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pPosition = PyTuple_GetItem(args, 1);
  PyObject *pX = PyTuple_GetItem(pPosition, 0);
  PyObject *pY = PyTuple_GetItem(pPosition, 1);

  double x = PyFloat_AsDouble(pX);
  double y = PyFloat_AsDouble(pY);

  rigid_bodies.at(id)->SetPosition(sf::Vector2f(x, y));

  Py_RETURN_NONE;
}

/*static*/ PyObject *RigidBodyHandler::GetRigidBodySize(PyObject *self,
                                                        PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.get_rigid_body_size expects a single long as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.get_rigid_body_size expects a single long as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.get_rigid_body_size got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  sf::Vector2f position = rigid_bodies.at(id)->GetSize();

  PyObject *w = PyFloat_FromDouble(position.x);
  PyObject *h = PyFloat_FromDouble(position.y);

  PyObject *pSize = PyTuple_Pack(2, w, h);

  return pSize;
}

/*static*/ PyObject *RigidBodyHandler::SetRigidBodySize(PyObject *self,
                                                        PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_rigid_body_size expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_rigid_body_size expects a long and a tuple as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.set_rigid_body_size got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  PyObject *pPosition = PyTuple_GetItem(args, 0);
  PyObject *pX = PyTuple_GetItem(pPosition, 0);
  PyObject *pY = PyTuple_GetItem(pPosition, 1);

  double x = PyFloat_AsDouble(pX);
  double y = PyFloat_AsDouble(pY);

  rigid_bodies.at(id)->SetSize(sf::Vector2f(x, y));

  Py_RETURN_NONE;
}

/*static*/ PyObject* RigidBodyHandler::SetRigidBodyCallback(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 2)
	{
		printf("engine.set_rigid_body_callback expects a long and a function reference as "
			   "arguments\n");
		PyErr_BadArgument();
	}
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.set_rigid_body_callback expects a long and a function reference as "
           "arguments\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.set_rigid_body_callback got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

	PyObject *pCallback = PyTuple_GetItem(args, 1);
	if (!PyCallable_Check(pCallback))
	{
		Py_XDECREF(pCallback);
		printf("engine.set_rigid_body_callback expects a long and a function reference as "
           "arguments\n");
		PyErr_BadArgument();
	}

  rigid_bodies.at(id)->SetCallback(pCallback);

	Py_RETURN_NONE;
}

/*static*/ PyObject *RigidBodyHandler::DrawRigidBodyCollider(PyObject *self,
                                                             PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.draw_rigid_body_collider expects a single long as an "
           "argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.draw_rigid_body_collider expects a single long as an "
           "argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf(
        "engine.draw_rigid_body_collider got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  rigid_bodies.at(id)->DrawOutline(rigid_window, sf::Color::Green);

  Py_RETURN_NONE;
}

/*static*/ PyObject *RigidBodyHandler::FreeRigidBody(PyObject *self,
                                                     PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 1) {
    printf("engine.free_rigid_body expects a single long as an argument\n");
    PyErr_BadArgument();
  }
  PyObject *pId = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf("engine.free_rigid_body expects a single long as an argument\n");
    PyErr_BadArgument();
  }

  long id = PyLong_AsLong(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.free_rigid_body got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  free_rigid_bodies.push_back(id);

  // Py_XDECREF(pId);

  Py_RETURN_NONE;
}

/*static*/ PyObject *RigidBodyHandler::SetGravity(PyObject *self,
                                                  PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    printf("engine.set_gravity expects two floats as argument\n");
    PyErr_BadArgument();
  }

  PyObject *pX = PyTuple_GET_ITEM(args, 0);
  PyObject *pY = PyTuple_GET_ITEM(args, 1);

  if (!PyFloat_Check(pX) || !PyFloat_Check(pY)) {
    printf("engine.set_gravity expects two floats as argument\n");
    PyErr_BadArgument();
  }

  float x = (float)PyFloat_AS_DOUBLE(pX);
  float y = (float)PyFloat_AS_DOUBLE(pY);
  gravity = {x, y};
  Py_RETURN_NONE;
}

/*static*/ PyObject *RigidBodyHandler::SetTerminalVelo(PyObject *self,
                                                       PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 3) {
    printf("engine.set_terminal_velo expects one long and two floats as "
           "argument\n");
    PyErr_BadArgument();
  }

  PyObject *pId = PyTuple_GetItem(args, 0);

  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);
    printf(
        "engine.set_terminal_velo expectis one long and two floats as argument"
        "arguments\n");
    PyErr_BadArgument();
  }

  PyObject *pX = PyTuple_GET_ITEM(args, 1);
  PyObject *pY = PyTuple_GET_ITEM(args, 2);

  if (!PyFloat_Check(pX) || !PyFloat_Check(pY)) {
    printf("engine.set_terminal_velo expects one long and two floats as "
           "argument\n");
    PyErr_BadArgument();
  }

  int id = PyLong_AS_LONG(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    Py_XDECREF(pX);
    Py_XDECREF(pY);
    printf("engine.set_terminal_velo got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  float x = (float)PyFloat_AS_DOUBLE(pX);
  float y = (float)PyFloat_AS_DOUBLE(pY);

  SetTerminalVelo(rigid_bodies.at(id), {x, y});
  Py_RETURN_NONE;
}

/*static*/ PyObject *RigidBodyHandler::ApplyForce(PyObject *self,
                                                  PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2 && nargs != 3) {
    printf("engine.ApplyForce expects 2 longs or 1 long and 2 floats as "
           "argument\n"
           "Got %ld args\n",
           nargs);
    PyErr_BadArgument();
  }

  PyObject *pId = PyTuple_GetItem(args, 0);

  if (!PyLong_Check(pId)) {
    Py_XDECREF(pId);

    printf("engine.ApplyForce expects at least one long as"
           "arguments\n");
    PyErr_BadArgument();
  }
  bool succ = false;

  int id = PyLong_AS_LONG(pId);

  if (rigid_bodies.size() <= id || 0 > id) {
    Py_XDECREF(pId);
    printf("engine.ApplyForce got a rigid body id out of range\n");
    PyErr_BadArgument();
  }

  if (nargs == 2) {
    printf("Not Implemented!\n");
    Py_RETURN_NONE;
  }

  PyObject *pX = PyTuple_GET_ITEM(args, 1);
  PyObject *pY = PyTuple_GET_ITEM(args, 2);

  if (!PyFloat_Check(pX) || !PyFloat_Check(pY)) {

    printf("engine.ApplyForce expects one long and two floats as "
           "argument\n");
    PyErr_BadArgument();
  }

  float x = (float)PyFloat_AS_DOUBLE(pX);
  float y = (float)PyFloat_AS_DOUBLE(pY);

  ApplyForce(rigid_bodies.at(id), {x, y});
  Py_RETURN_NONE;
}

PyObject* RigidBodyHandler::RigidBodyCollidesWith(PyObject* self, PyObject* args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if (nargs != 2) {
    std::cerr << "rigid_body_collides_with: expects 2 araguments" << std::endl;
    PyErr_BadArgument();
  }

  PyObject* pId1 = PyTuple_GET_ITEM(args, 0);
  PyObject* pId2 = PyTuple_GET_ITEM(args, 1);

  if (!PyLong_Check(pId1)) {
    std::cerr << "rigid_body_collides_with: expects a rigidbody id as the first argument" << std::endl;
    PyErr_BadArgument();
  } 
  
  if (!PyLong_Check(pId2)) {
    std::cerr << "rigid_body_collides_with: expects a box collider id as the second argument" << std::endl;
    PyErr_BadArgument();
  }

  long rid = PyLong_AS_LONG(pId1);
  long bcid = PyLong_AS_LONG(pId2);

  if (rigid_bodies.size() <= rid || 0 > rid) {
    std::cerr << "rigid_body_collides_with: argument 1 id is out of range" << std::endl;
    PyErr_BadArgument();
  }

  if (rigid_bodies.size() <= rid || 0 > rid) {
    std::cerr << "rigid_body_collides_with: argument 1 id is out of range" << std::endl;
    PyErr_BadArgument();
  }

  // std::cout << rigid_bodies.at(rid) << std::endl;
  // std::cout << bc << std::endl;
  BoxCollider* bc = BoxColliderHandler::getBoxCollider(bcid);
  if (rigid_bodies[rid]->CollidesWith(bc)) {
    // std::cout << "They are colliding" << std::endl;
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

bool RigidBodyHandler::ApplyForce(RigidBody *body, const sf::Vector2f &force) {
  // printf("Called This function\n");
  body->ApplyForce(force);
  return true;
}

bool RigidBodyHandler::ApplyForce(RigidBody *body, float x, float y) {
  ApplyForce(body, {x, y});
  return true;
}
