/**
 * @file polygon.hpp
 * @brief a test class for a polgon
 * @author Dayne Pefley
 *
 */

#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <SFML/Graphics.hpp>

class Polygon {
public:
  struct vertexPairs {
    int index0;
    int index1;
    sf::Vector2f getVector(const Polygon* p) const;
  };

  /**
   * @param vertices the verticise to make up the polygon
   * @param edges the edges that make up the polygon
   * @param size the number of vertices/edges
   */
  Polygon(sf::Vector2f *vertices, vertexPairs *edges, int size);

  /**
   * @param other the other object to collide with
   * @return true if the objects collide, false otherwise
   */
  bool Collide(const Polygon *other) const;

private:
  /**
   * @member the number of vertices/edges that make up the polygon
   */
  int size;

  /**
   * @member the vertices that define the shape
   */
  sf::Vector2f *vertices;

  /**
   * @member the edges that define the shape
   */
  struct vertexPairs *edges;

};

#endif // POLYGON_HPP
