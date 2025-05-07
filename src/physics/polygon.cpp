/**
 * @file polygon.hpp
 * @brief a test class for a polgon
 * @author Dayne Pefley
 *
 */

#ifndef POLYGON_CPP
#define POLYGON_CPP
#include "polygon.hpp"
#include "System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <limits>
#include <stack>
#include <vector>

/**
 * @param vertices the verticise to make up the polygon
 * @param edges the edges that make up the polygon
 * @param size the number of vertices/edges
 */
Polygon::Polygon(sf::Vector2f *vertices, vertexPairs *edges, int size)
    : vertices(vertices), edges(edges), size(size) {}

/**
 * @param other the other object to collide with
 * @return true if the objects collide, false otherwise
 */
bool Polygon::Collide(const Polygon *other) const {
  float dot = 0;

  sf::Vector2f currentEdge;
  std::vector<sf::Vector2f> perpStack;

  for (int i = 0; i < size; i++) {
    currentEdge = edges[i].getVector(this);
    perpStack.emplace_back(-currentEdge.y, currentEdge.x);
  }

  for (int i = 0; i < other->size; i++) {

    currentEdge = other->edges[i].getVector(other);

    perpStack.emplace_back(-currentEdge.y, currentEdge.x);
  }

  for (int i = 0; i < perpStack.size(); i++) {

    float amax = std::numeric_limits<float>::min();
    float amin = std::numeric_limits<float>::max();

    float bmax = std::numeric_limits<float>::min();
    float bmin = std::numeric_limits<float>::max();

    for (int j = 1; j < size; j++) {
      dot = vertices[j].dot(perpStack[i]);
      if (amax == std::numeric_limits<float>::min() || dot > amax) {
        amax = dot;
      }
      if (amin == std::numeric_limits<float>::max() || dot < amin) {
        amin = dot;
      }
    }

    for (int j = 1; j < other->size; j++) {
      dot = other->vertices[j].dot(perpStack[i]);
      if (bmax == std::numeric_limits<float>::min() || dot > bmax) {
        bmax = dot;
      }
      if (bmin == std::numeric_limits<float>::max() || dot < bmin) {
        bmin = dot;
      }
    }

    if ((amin < bmax && amin > bmin) || bmin < amax && bmin > amin)
      continue;
    return false;

  }

  return true;
}

sf::Vector2f Polygon::vertexPairs::getVector(const Polygon *p) const {
  return p->vertices[index0] - p->vertices[index1];
}

#endif // POLYGON_HPP
