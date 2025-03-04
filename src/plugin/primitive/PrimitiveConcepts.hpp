/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** PrimitiveConcepts
*/

#ifndef PRIMITIVECONCEPTS_HPP_
#define PRIMITIVECONCEPTS_HPP_

#include "Ellipse.hpp"
#include "Line2D.hpp"
#include "Point2D.hpp"
#include "Polygon.hpp"
#include "Primitive.hpp"
#include "Rectangle.hpp"

#include <type_traits>

#if __cplusplus >= 201703L
template <typename T>
concept IsPoint2D = std::is_base_of_v<plugin::primitive::Point2D, T>;

template <typename T>
concept IsLine2D = std::is_base_of_v<plugin::primitive::Line2D, T>;

template <typename T>
concept IsRectangle = std::is_base_of_v<plugin::primitive::Rectangle, T>;

template <typename T>
concept IsEllipse = std::is_base_of_v<plugin::primitive::Ellipse, T>;

template <typename T>
concept IsPolygon = std::is_base_of_v<plugin::primitive::Polygon, T>;
#endif

#endif /* !PRIMITIVECONCEPTS_HPP_ */
