/**
 * @file engine.cpp
 * @author Dr. Denning, Dawson Ochs, Sterling Davis, Dayne Pefley, and Ethan
 * Hoyt
 * @brief Defines and makes available the APIs for the engine.
 */

#include "audio_handler.h"
#include "box_collider_handler.hpp"
#include "keyboard.h"
#include "object_handler.h"
#include "pyerrors.h"
#include "rigid_body_handler.h"
#include "vector.h"
#include <Python.h>
#include <SFML/Graphics.hpp>

sf::RenderWindow *g_window;
ObjectHandler *g_object_handler;
BoxColliderHandler *g_box_collider_handler;
RigidBodyHandler *g_rigid_body_handler;
float g_gravity = 50.0f;

/**
 * @brief The methods that are available to the engine
 */
static PyMethodDef EngineMethods[] = {
    {"create_sprite", ObjectHandler::CreateSprite, METH_VARARGS,
     engine_create_sprite_doc},
    {"set_sprite_position", ObjectHandler::SetSpritePosition, METH_VARARGS,
     engine_set_sprite_position_doc},
    {"set_sprite_scale", ObjectHandler::SetSpriteScale, METH_VARARGS,
     engine_set_sprite_scale_doc},
    {"draw_sprite", ObjectHandler::DrawSprite, METH_VARARGS,
     engine_draw_sprite_doc},
    {"free_sprite", ObjectHandler::FreeSprite, METH_VARARGS,
     engine_free_sprite_doc},
    {"create_circle", ObjectHandler::CreateCircle, METH_VARARGS,
     engine_create_circle_doc},
    {"set_circle_fill_color", ObjectHandler::SetCircleFillColor, METH_VARARGS,
     engine_set_circle_fill_color_doc},
    {"set_circle_position", ObjectHandler::SetCirclePosition, METH_VARARGS,
     engine_set_circle_position_doc},
    {"set_circle_scale", ObjectHandler::SetCircleScale, METH_VARARGS,
     engine_set_circle_scale_doc},
    {"draw_circle", ObjectHandler::DrawCircle, METH_VARARGS,
     engine_draw_circle_doc},
    {"collides_with", ObjectHandler::CollidesWith, METH_VARARGS,
     engine_collides_with_doc},
    keyPressed,
    {"create_box_collider", BoxColliderHandler::createBoxCollider, METH_VARARGS,
     engine_create_box_collider_doc},
    {"free_box_collider", BoxColliderHandler::freeBoxCollider, METH_VARARGS,
     engine_free_box_collider_doc},
    {"current_time", RigidBodyHandler::GetCurrentTime, METH_VARARGS,
     engine_current_time_doc},
    {"delta_time", RigidBodyHandler::GetDeltaTime, METH_VARARGS,
     engine_delta_time_doc},
    {"create_rigid_body", RigidBodyHandler::CreateRigidBody, METH_VARARGS,
     engine_create_rigid_body_doc},
    {"is_rigid_body_static", RigidBodyHandler::IsRigidBodyStatic, METH_VARARGS,
     engine_is_rigid_body_static_doc},
    {"set_rigid_body_static", RigidBodyHandler::SetRigidBodyStatic,
     METH_VARARGS, engine_set_rigid_body_static_doc},
    {"is_rigid_body_gravity", RigidBodyHandler::IsRigidBodyGravity,
     METH_VARARGS, engine_is_rigid_body_gravity_doc},
    {"set_rigid_body_gravity", RigidBodyHandler::SetRigidBodyGravity,
     METH_VARARGS, engine_set_rigid_body_gravity_doc},
    {"set_rigid_body_velocity", RigidBodyHandler::SetRigidBodyVelocity,
     METH_VARARGS, engine_set_rigid_body_gravity_doc},
    {"get_rigid_body_position", RigidBodyHandler::GetRigidBodyPosition,
     METH_VARARGS, engine_get_rigid_body_position_doc},
    {"set_rigid_body_position", RigidBodyHandler::SetRigidBodyPosition,
     METH_VARARGS, engine_set_rigid_body_position_doc},
    {"set_rigid_body_position", RigidBodyHandler::SetRigidBodyPosition,
     METH_VARARGS, engine_set_rigid_body_position_doc},
    {"get_rigid_body_size", RigidBodyHandler::GetRigidBodySize, METH_VARARGS,
     engine_get_rigid_body_size_doc},
    {"set_rigid_body_size", RigidBodyHandler::SetRigidBodySize, METH_VARARGS,
     engine_set_rigid_body_size_doc},
    {"draw_rigid_body_collider", RigidBodyHandler::DrawRigidBodyCollider,
     METH_VARARGS, engine_draw_rigid_body_collider_doc},
    {"free_rigid_body", RigidBodyHandler::FreeRigidBody, METH_VARARGS,
     engine_free_rigid_body_doc},

    {"create_sound", AudioHandler::CreateSound, METH_VARARGS,
     engine_create_sound_doc},
    {"free_sound", AudioHandler::FreeSound, METH_VARARGS,
     engine_free_sound_doc},
    {"play_sound", AudioHandler::PlaySound, METH_VARARGS,
     engine_play_sound_doc},
    {"pause_sound", AudioHandler::PauseSound, METH_VARARGS,
     engine_pause_sound_doc},
    {"set_sound_pitch", AudioHandler::SetSoundPitch, METH_VARARGS,
     engine_set_sound_pitch_doc},
    {"set_sound_volume", AudioHandler::SetSoundVolume, METH_VARARGS,
     engine_set_sound_volume_doc},
    {"set_sound_loop", AudioHandler::SetSoundLoop, METH_VARARGS,
     engine_set_sound_loop_doc},
    {"create_music", AudioHandler::CreateMusic, METH_VARARGS,
     engine_create_music_doc},
    {"free_music", AudioHandler::FreeMusic, METH_VARARGS,
     engine_free_music_doc},
    {"play_music", AudioHandler::PlayMusic, METH_VARARGS,
     engine_play_music_doc},
    {"pause_music", AudioHandler::PauseMusic, METH_VARARGS,
     engine_pause_music_doc},
    {"set_music_pitch", AudioHandler::SetMusicPitch, METH_VARARGS,
     engine_set_music_pitch_doc},
    {"set_music_volume", AudioHandler::SetMusicVolume, METH_VARARGS,
     engine_set_music_volume_doc},
    {"set_music_loop", AudioHandler::SetMusicLoop, METH_VARARGS,
     engine_set_music_loop_doc},
    createVector,
    length,
    normalize,
    dot,
    cross,
    set_gravity,
    set_terminal_velo,
    apply_force,
    {NULL, NULL, 0, NULL}};

/**
 * @brief definiton of the engine module available in python
 */
static PyModuleDef EngineModule = {PyModuleDef_HEAD_INIT,
                                   "engine",
                                   NULL,
                                   -1,
                                   EngineMethods,
                                   NULL,
                                   NULL,
                                   NULL,
                                   NULL};

/**
 * @brief the init function for the python intepreter
 */
PyMODINIT_FUNC PyInit_engine(void) { return PyModule_Create(&EngineModule); }

int main(int argc, char *argv[]) {
  // Setup
  PyObject *pName, *pModule, *pFuncInit, *pFuncUpdate, *pFuncDraw;
  PyObject *pArgs, *pValue;
  PyObject *pErr;
  int i;

  if (argc != 3) {
    fprintf(stderr,
            "Usage: engine /full/path/to/pythongame/dir pythongame.py\n");
    return 1;
  }

  // Engine initialization
  PyImport_AppendInittab("engine", PyInit_engine);

  // obtain Python game
  Py_Initialize();
  char *module_path = argv[1];
  char simple_str[1024];
  sprintf(simple_str,
          "import sys\n"
          "sys.path.insert(0, \"%s\")\n"
          "sys.path.insert(0, \".\")",
          module_path);

  char *pythonfilename = argv[2];
  char *extension = strstr(pythonfilename, ".py\0");

  // normalize filename by removing file extension
  if (extension) {
    strncpy(extension, "\0", 1);
  }
  pName = PyUnicode_DecodeFSDefault(pythonfilename);

  // PyRun_SimpleString("import sys\n"            "import os");
  // PyRun_SimpleString("sys.path.append( os.path.dirname(os.getcwd())
  // +'/project_name/')");
  PyRun_SimpleString(simple_str);

  // load local instance of pName
  pModule = PyImport_Import(pName);
  Py_DECREF(pName); // dereferences object, thus no longer using it

  if (pModule == NULL) {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", argv[2]);
    return 1;
  }

  // Look for Key Functions in Python Game
  // Init
  pFuncInit = PyObject_GetAttrString(pModule, "init");
  if (!pFuncInit || !PyCallable_Check(pFuncInit)) {
    if (PyErr_Occurred()) { // doesn't exist
      PyErr_Print();
    }
    fprintf(stderr, "Cannot find function \"init\"\n");
    return 1;
  }

  // Update
  pFuncUpdate = PyObject_GetAttrString(pModule, "update");
  if (!pFuncUpdate || !PyCallable_Check(pFuncUpdate)) {
    if (PyErr_Occurred()) { // doesn't exist
      PyErr_Print();
    }
    fprintf(stderr, "Cannot find function \"update\"\n");
    return 1;
  }

  // Draw
  pFuncDraw = PyObject_GetAttrString(pModule, "draw");
  if (!pFuncDraw || !PyCallable_Check(pFuncDraw)) {
    if (PyErr_Occurred()) { // doesn't exist
      PyErr_Print();
    }
    fprintf(stderr, "Cannot find function \"draw\"\n");
    return 1;
  }

  // assign globals
  g_window = new sf::RenderWindow(sf::VideoMode({1024, 640}), "Engine!");

  // create object handlers
  g_object_handler = new ObjectHandler(g_window);
  g_box_collider_handler = new BoxColliderHandler(g_window);
  g_rigid_body_handler = new RigidBodyHandler(g_window);

  // Doing this so things don't fly off the screen in the first frame
  g_rigid_body_handler->UpdateCurrentAndTimeDelta();
  g_rigid_body_handler->UpdatePreviousTime();

  // loads in the init Key Function of Python Game
  pValue = PyObject_CallNoArgs(pFuncInit);
  if (!pValue) {
    PyErr_Occurred();
    PyErr_Print();
  }
  Py_DECREF(pValue);

  // SFML loop (ver. 3.0.0)
  while (g_window->isOpen()) {
    while (std::optional event = g_window->pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        g_window->close();
        break;
      }
    }

    if (!g_window->isOpen()) {
      break;
    }

    // Update the rigid bodies and time delta
    g_rigid_body_handler->UpdateCurrentAndTimeDelta();
    g_rigid_body_handler->UpdateSim();

    // loads in update Key Function of Python Game
    pValue = PyObject_CallNoArgs(pFuncUpdate);
    pErr = PyErr_Occurred();
    // catch-all for errors that game causes
    if (pErr) {
      printf("An error occurred!\n");
      g_window->close();
      break;
    }
    Py_XDECREF(pValue); // dereferences, but pValue can already be NULL

    // Update previous time before drawing, for an iOS friendly delta time
    g_rigid_body_handler->UpdatePreviousTime();

    g_window->clear();

    // loads in draw Key Function of Python Game
    pValue = PyObject_CallNoArgs(pFuncDraw);
    pErr = PyErr_Occurred();
    // catch-all for errors that game causes
    if (pErr) {
      printf("An error has occurred\n");
      g_window->close();
      break;
    }
    Py_XDECREF(pValue); // dereferences, but pValue can already be NULL

    g_window->display();
  }

  delete g_window;
  delete g_object_handler;
  delete g_box_collider_handler;
  delete g_rigid_body_handler;

  printf("engine: Tearing Down\n");

  // Teardown
  Py_XDECREF(pFuncDraw);
  Py_XDECREF(pFuncUpdate);
  Py_XDECREF(pFuncInit);
  Py_XDECREF(pModule);

  // printf("engine: Finished Tearing Down\n");

  if (Py_FinalizeEx() < 0) {
    return 120;
  }

  printf("engine: Finished Tearing Down\n");

  return 0;
}
