//
// -*- Mode: c++; tab-width: 4; -*-
// -*- ex: ts=4 -*-
//

//
// main.cpp (Vadym Drozd)
// BaseClassDifferTypes/main.cpp
//

//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
// EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//


////////////////////////////////////////////////////////////////////////////////
// include section

#include "BaseClass.h"

////////////////////////////////////////////////////////////////////////////////
// Point Class

class Point : public BaseClass{
public:
    int x;
    int y;
    int z;

    SAVE(Point)
        REG_MEMBER(id_int, x);
        REG_MEMBER(id_int, y);
    ENDSAVE;
};

////////////////////////////////////////////////////////////////////////////////
// Point4D Class
class Point4D : public Point
{
public:
    int v;

    SAVE_PARENT(Point4D, Point)
        REG_MEMBER(id_int, v);
    ENDSAVE;
};

////////////////////////////////////////////////////////////////////////////////
// Point4D_v2 Class
class Point4D_v2 : public BaseClass
{
public:
    Point p;
    float v;

    SAVE(Point4D_v2)
        REG_MEMBER(id_baseClass, p);
        REG_MEMBER(id_float, v);
    ENDSAVE;
};

////////////////////////////////////////////////////////////////////////////////
// Point10D Class
class Point10D : public BaseClass
{
public:
    Point points[2];
    double coords[6];

    SAVE(Point10D)
        REG_MEMBER_ARR(id_baseClass, points);
        REG_MEMBER_ARR(id_double, coords);
    ENDSAVE;
};

////////////////////////////////////////////////////////////////////////////////
// Main

int main()
{
    std::cout << "Test class Point\n";
    Point p;
    p.Load("");
    p.Save("");

    std::cout << "Test Point::Point(Point &)\n";
    Point p2 = p;
    p2.x = 2;
    p2.y = 2;
    p2.Save("");

    std::cout << "Test Point::operator=(Point &)\n";
    Point p3;
    p3 = p;
    p3.x = 3;
    p3.Save("");

    std::cout << "Test class Point4D\n";
    Point4D p4;
    p4.Load("");
    p4.Save("");

    std::cout << "Test class Point4D::(Point4D &)\n";
    Point4D p4_copy = p4;
    p4_copy.x = 2222;
    p4_copy.Save("");

    std::cout << "Test class Point4D_v2\n";
    Point4D_v2 p4_v2;
    p4_v2.Load("");
    p4_v2.Save("");

    std::cout << "Test class Point10D\n";
    Point10D p10d;
    p10d.Load("");
    p10d.Save("");

    return 0;
}

//
//
//
