#ifndef _CAMERA_HANDLER_HPP_
#define _CAMERA_HANDLER_HPP_


#include <Python.h>
#include <SFML/Graphics.hpp>
#include <vector>

class CameraHandler {
    private:
    
    public:
        CameraHandler(sf::RenderWindow* window);
        ~CameraHandler();

        static PyObject* SetPosition(PyObject* self, PyObject* arg);
        static PyObject* SetSize(PyObject* self, PyObject* arg);

};

PyDoc_STRVAR(
    engine_set_camera_position_doc,
    ".. function:: set_camera_position(tuple (x, y))\n"
    "\n"
    "Sets the center of the camera to the location at x and y."
    "\n"
    ":return: none"
);

PyDoc_STRVAR(
    engine_set_camera_size_doc,
    ".. function:: set_camera_size(tuple (w, h))\n"
    "\n"
    "Sets the size of the camera to the size with the dimensions w and h."
    "\n"
    ":return: none"
);

#endif