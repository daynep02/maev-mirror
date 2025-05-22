#ifndef _COLLISION_LAYERS_H_
#define _COLLISION_LAYERS_H_

#include <Python.h>
#include <string_view>

enum CollisionLayer {
    DEFAULT = 0,
    LAYER1 = 1,
    LAYER2 = 2,
    LAYER3 = 3,
    LAYER4 = 4,
    LAYER5 = 5,
    LAYER6 = 6,
    LAYER7 = 7,
};

constexpr std::string_view LayerStrings[] {
    "DEFAULT",
    "LAYER1",
    "LAYER2",
    "LAYER3",
    "LAYER4",
    "LAYER5",
    "LAYER6",
    "LAYER7"
};

void SetLayerAt(CollisionLayer first, CollisionLayer second, bool value);
bool GetLayerAt(CollisionLayer first, CollisionLayer second);

void EnableAllLayers();
void DisableAllLayers();
void PrintLayerMatrix();

// PYTHON API
class CollisionLayerHandler {
    public:
    static PyObject* SetCollisionLayerValue(PyObject* self, PyObject* args);
    static PyObject* GetCollisionLayerValue(PyObject* self, PyObject* args);

    static PyObject* EnableAllCollisionLayers(PyObject* self, PyObject* args);
    static PyObject* DisableAllCollisionLayers(PyObject* self, PyObject* args);
    static PyObject* PrintCollisionLayerMatrix(PyObject* self, PyObject* args);
};

// PYTHON DOCS

PyDoc_STRVAR(engine_set_collision_layer_value_doc,
             ".. function:: set_collision_layer_value(layer1, layer2, bool)\n"
             "\n"
             " set the value of the layer matrix where the layers intersect to the provided bool.\n"
             "\n"
             "  :return: Nothing.\n");

PyDoc_STRVAR(engine_get_collision_layer_value_doc,
             ".. function:: get_collision_layer_value(layer1, layer2)\n"
             "\n"
             " get the value of the layer matrix where the layers intersect.\n"
             "\n"
             "  :return: A long within the range 0-7 inclusive.\n");

PyDoc_STRVAR(engine_enable_all_collision_layers_doc,
             ".. function:: enable_all_collision_layers()\n"
             "\n"
             " Sets the entire layer matrix to be true.\n"
             "\n"
             "  :return: Nothing.\n");
 
PyDoc_STRVAR(engine_disable_all_collision_layers_doc,
             ".. function:: disable_all_collision_layers()\n"
             "\n"
             " Sets the entire layer matrix to be false.\n"
             "\n"
             "  :return: Nothing.\n");

PyDoc_STRVAR(engine_print_collision_layer_matrix_doc,
             ".. function:: print_collision_layer_matrix()\n"
             "\n"
             " Prints the collision layer matrix to the console and it's values.\n"
             "\n"
             "  :return: Nothing.\n");

#endif //_COLLISION_LAYERS_H_