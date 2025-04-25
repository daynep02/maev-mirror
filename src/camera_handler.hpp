#ifndef _CAMERA_HANDLER_HPP_
#define _CAMERA_HANDLER_HPP_


#include <Python.h>
#include <SFML/Graphics.hpp>
#include <vector>

class CameraHandler {
    private:
        // constexpr static sf::View g_camera = sf::View();
    
    public:
        CameraHandler();
        ~CameraHandler();

        static PyObject* SetPosition(PyObject* self, PyObject* arg);

};

PyDoc_STRVAR(
    engine_set_camera_position_doc,
    ".. function:: set_camera_position(tuple (x y))\n"
    "\n"
    ""
    "\n"
    ":return: none"
);

#endif