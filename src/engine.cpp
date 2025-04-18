#include "keyboard.h"
#include <Python.h>
#include <SFML/Graphics.hpp>

#include "keyboard.h"
#include "object_handler.h"

#include "box_collider.hpp"
#include "box_collider_handler.hpp"

#include <iostream>

sf::RenderWindow *window;

ObjectHandler *g_object_handler;

// Python methods built into engine
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
    {"create_box_collider", BoxColliderHandler::createBoxCollider, METH_VARARGS, engine_create_box_collider_doc},
    {"free_box_collider", BoxColliderHandler::freeBoxCollider, METH_VARARGS, engine_free_box_collider_doc},
    {NULL, NULL, 0, NULL}};

// initialization values
static PyModuleDef EngineModule = {PyModuleDef_HEAD_INIT,
                                   "engine",
                                   NULL,
                                   -1,
                                   EngineMethods,
                                   NULL,
                                   NULL,
                                   NULL,
                                   NULL};

// init function
PyMODINIT_FUNC PyInit_engine(void) { return PyModule_Create(&EngineModule); }

int main(int argc, char *argv[]) {
  // Setup
  PyObject *pName, *pModule, *pFuncInit, *pFuncUpdate, *pFuncDraw;
  PyObject *pArgs, *pValue;
  PyObject *pErr;
  int i;

  if (argc != 3) {
    fprintf(stderr, "Usage: engine /full/path/to/pythongame/dir pythongame.py\n");
    return 1;
  }

  // Engine initialization
  PyImport_AppendInittab("engine", PyInit_engine);

  // obtain Python game
  Py_Initialize();
  char *module_path = argv[1];
  char simple_str[1024];
  sprintf(simple_str,"import sys\n"
                     "sys.path.insert(0, \"%s\")\n"
                     "sys.path.insert(0, \".\")",module_path);
                     

  char *pythonfilename = argv[2];
  char *extension = strstr(pythonfilename, ".py\0");

  // normalize filename by removing file extension
  if (extension) {
    strncpy(extension, "\0", 1);
  }
  pName = PyUnicode_DecodeFSDefault(pythonfilename);

  //PyRun_SimpleString("import sys\n"            "import os");
  //PyRun_SimpleString("sys.path.append( os.path.dirname(os.getcwd()) +'/project_name/')");
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
  window = new sf::RenderWindow(sf::VideoMode({1024, 640}), "Engine!");

  // create object handler
  g_object_handler = new ObjectHandler(window);

  // loads in the init Key Function of Python Game
  pValue = PyObject_CallNoArgs(pFuncInit);
  Py_DECREF(pValue);

  // SFML loop (ver. 3.0.0)
  while (window->isOpen()) {
    while (std::optional event = window->pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window->close();
        break;
      }
    }

    if (!window->isOpen()) {
      break;
    }

    // loads in update Key Function of Python Game
    pValue = PyObject_CallNoArgs(pFuncUpdate);
    pErr = PyErr_Occurred();
    // catch-all for errors that game causes
    if (pErr) {
      printf("An error occurred!\n");
      window->close();
      break;
    }
    Py_XDECREF(pValue); // dereferences, but pValue can already be NULL

    window->clear();

    // loads in draw Key Function of Python Game
    pValue = PyObject_CallNoArgs(pFuncDraw);
    pErr = PyErr_Occurred();
    // catch-all for errors that game causes
    if (pErr) {
      printf("An error has occurred\n");
      window->close();
      break;
    }
    Py_XDECREF(pValue); // dereferences, but pValue can already be NULL

    window->display();
  }

  delete g_object_handler;

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
