#include "collision_layers.h"

#include <stdio.h>

//  DEFAULT  L1    L2    L3    L4    L5    L6    L7
bool layer_matrix[8][8] = {{true, true, true, true, true, true, true, true}, // LAYER7
                           {true, true, true, true, true, true, true},       // LAYER6
                           {true, true, true, true, true, true},             // LAYER5
                           {true, true, true, true, true},                   // LAYER4
                           {true, true, true, true},                         // LAYER3
                           {true, true, true},                               // LAYER2
                           {true, true},                                     // LAYER1
                           {true}};                                          // DEFAULT

void SetLayerAt(CollisionLayer first, CollisionLayer second, bool value)
{
    layer_matrix[7 - second][first] = value;
}

bool GetLayerAt(CollisionLayer first, CollisionLayer second)
{
    return layer_matrix[7 - second][first];
}

void EnableAllLayers()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8 - i; j++)
        {
            layer_matrix[i][j] = true;
        }
    }
}

void DisableAllLayers()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8 - i; j++)
        {
            layer_matrix[i][j] = false;
        }
    }
}

void PrintLayerMatrix()
{
    printf("Printing Collision Layer Matrix\n");

    printf("         ");
    for (int i = 0; i < 8; i++)
    {
        printf("%.*s ", static_cast<int>(LayerStrings[i].length()), LayerStrings[i].data());
        if (i != 0)
        {
            printf(" ");
        }
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%.*s  ", static_cast<int>(LayerStrings[7 - i].length()), LayerStrings[7 - i].data());
        if (7 - i != 0)
        {
            printf(" ");
        }
        for (int j = 0; j < 8 - i; j++)
        {
            if (layer_matrix[i][j] == false)
            {
                printf("False   ");
            }
            else
            {
                printf("True    ");
            }
        }
        printf("\n");
    }
}

// PYTHON API
PyObject *CollisionLayerHandler::SetCollisionLayerValue(PyObject *self, PyObject *args)
{
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 3)
    {
        printf("engine.set_collision_layer_value expects two longs and a bool as "
               "arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pLayer1 = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pLayer1))
    {
        Py_XDECREF(pLayer1);
        printf("engine.set_collision_layer_value expects two longs and a bool as "
               "arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pLayer2 = PyTuple_GetItem(args, 1);
    if (!PyLong_Check(pLayer2))
    {
        Py_XDECREF(pLayer2);
        printf("engine.set_collision_layer_value expects two longs and a bool as "
               "arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pB = PyTuple_GetItem(args, 2);
    if (!PyBool_Check(pB))
    {
        Py_XDECREF(pB);
        printf("engine.set_collision_layer_value expects two longs and a bool as "
               "arguments\n");
        PyErr_BadArgument();
    }

    long layer1 = PyLong_AsLong(pLayer1);
    long layer2 = PyLong_AsLong(pLayer2);
    bool b = PyLong_AsLong(pB);

    if (layer1 > 7 || layer1 <0) {
        printf("engine.set_rigid_body_layer got first layer out of range, returning...\n");
        PyErr_BadArgument();
        Py_RETURN_NONE;
    }
    if (layer2 > 7 || layer2 <0) {
        printf("engine.set_rigid_body_layer got second layer out of range, returning...\n");
        PyErr_BadArgument();
        Py_RETURN_NONE;
    }

    SetLayerAt((CollisionLayer)layer1, (CollisionLayer)layer2, b);

    Py_RETURN_NONE;
}

PyObject *CollisionLayerHandler::GetCollisionLayerValue(PyObject *self, PyObject *args)
{
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2)
    {
        printf("engine.get_collision_layer_value expects two longs as "
               "arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pLayer1 = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pLayer1))
    {
        Py_XDECREF(pLayer1);
        printf("engine.get_collision_layer_value expects two longs as "
               "arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pLayer2 = PyTuple_GetItem(args, 1);
    if (!PyLong_Check(pLayer2))
    {
        Py_XDECREF(pLayer2);
        printf("engine.get_collision_layer_value expects two longs as "
               "arguments\n");
        PyErr_BadArgument();
    }

    long layer1 = PyLong_AsLong(pLayer1);
    long layer2 = PyLong_AsLong(pLayer2);

    if (layer1 > 7 || layer1 <0) {
        printf("engine.get_collision_layer_value got first layer out of range, returning...\n");
        PyErr_BadArgument();
        Py_RETURN_FALSE;
    }
    if (layer2 > 7 || layer2 <0) {
        printf("engine.get_collision_layer_value got second layer out of range, returning...\n");
        PyErr_BadArgument();
        Py_RETURN_FALSE;
    }

    if (GetLayerAt((CollisionLayer)layer1, (CollisionLayer)layer2)) {
        Py_RETURN_TRUE;
    }

    Py_RETURN_FALSE;
}

PyObject *CollisionLayerHandler::EnableAllCollisionLayers(PyObject *self, PyObject *args)
{
    EnableAllLayers();
    Py_RETURN_NONE;
}

PyObject *CollisionLayerHandler::DisableAllCollisionLayers(PyObject *self, PyObject *args)
{
    DisableAllLayers();
    Py_RETURN_NONE;
}

PyObject *CollisionLayerHandler::PrintCollisionLayerMatrix(PyObject *self, PyObject *args)
{
    PrintLayerMatrix();
    Py_RETURN_NONE;
}