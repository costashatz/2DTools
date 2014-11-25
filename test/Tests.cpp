#include <gtest/gtest.h>
#include <2DTools/Vector2D.hpp>
#include <2DTools/Matrix2D.hpp>
#include <2DTools/Polygons.hpp>
#include <2DTools/Distances2D.hpp>
using namespace Tools2D;

TEST(Vector2DTest, DefaultConstructor) {
    Vector2D<double> d;
    EXPECT_EQ(d.X(), 0.0);
    EXPECT_EQ(d.Y(), 0.0);
}

TEST(Vector2DTest, Constructor) {
    Vector2D<double> d(3.0, 4.0);
    EXPECT_EQ(d.X(), 3.0);
    EXPECT_EQ(d.Y(), 4.0);
}

TEST(Vector2DTest, CopyConstructor) {
    Vector2D<double> x(1.0, 2.0);
    Vector2D<double> d(x);
    EXPECT_EQ(d.X(), 1.0);
    EXPECT_EQ(d.Y(), 2.0);
}

TEST(Vector2DTest, Zero) {
    Vector2D<double> d(3.0, 4.0);
    d.Zero();
    EXPECT_EQ(d.X(), 0.0);
    EXPECT_EQ(d.Y(), 0.0);
}

TEST(Vector2DTest, Zero2) {
    Vector2D<double> d(3.0, 4.0);
    d.Zero();
    EXPECT_EQ(d.IsZero(), true);
}

TEST(Vector2DTest, Normalize) {
    Vector2D<double> d(3.0, 4.0);
    d.Normalize();
    EXPECT_EQ(d.X(), 3.0/5.0);
    EXPECT_EQ(d.Y(), 4.0/5.0);
}

TEST(Vector2DTest, Perp) {
    Vector2D<double> d(3.0, 4.0);
    Vector2D<double> x = d.Perp();
    EXPECT_EQ(d.Dot(x), 0.0);
}

TEST(Vector2DTest, Perp2) {
    Vector2D<double> d(3.0, 4.0);
    Vector2D<double> x = d.Perp2();
    EXPECT_EQ(d.Dot(x), 0.0);
}

TEST(Matrix2DTest, DefaultConstructor) {
    Matrix2D<double> tmp;
    double** d = tmp.getData();
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(i==j)
                EXPECT_EQ(d[i][j], 1.0);
            else
                EXPECT_EQ(d[i][j], 0.0);
        }
    }
}

TEST(Matrix2DTest, Identity) {
    Matrix2D<double> tmp;
    Matrix2D<double> tr = tmp.Transpose();
    Matrix2D<double> inv = tmp.Inverse();
    double** d1 = tmp.getData();
    double** d2 = tmp.getData();
    double** d3 = tmp.getData();
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            EXPECT_EQ(d1[i][j], d2[i][j]);
            EXPECT_EQ(d3[i][j], d2[i][j]);
        }
    }
}

TEST(Matrix2DTest, Multiplication) {
    Matrix2D<double> tmp;
    tmp(0,1) = 2;
    tmp(0,2) = 3;
    Matrix2D<double> tmp2;
    tmp2(1,0) = 1;
    tmp2(2,0) = 2;
    Matrix2D<double> t = tmp*tmp2;
    EXPECT_EQ(t(0,0), 9);
    EXPECT_EQ(t(0,1), 2);
    EXPECT_EQ(t(0,2), 3);
    EXPECT_EQ(t(1,0), 1);
    EXPECT_EQ(t(1,1), 1);
    EXPECT_EQ(t(1,2), 0);
    EXPECT_EQ(t(2,0), 2);
    EXPECT_EQ(t(2,1), 0);
    EXPECT_EQ(t(2,2), 1);
}

TEST(PolygonsTest, Polyline) {
    Polyline2D<double> poly;
    poly.AddPoint(Vector2D<double>(2.0,3.0));
    poly.AddPoint(Vector2D<double>(4.0,3.0));
    poly.AddPoint(Vector2D<double>(4.0,6.0));

    vector<Vector2D<double> > v = poly.Vertices();
    EXPECT_EQ(v[0].X(), 2.0);
    EXPECT_EQ(v[0].Y(), 3.0);
    EXPECT_EQ(v[1].X(), 4.0);
    EXPECT_EQ(v[1].Y(), 3.0);
    EXPECT_EQ(v[2].X(), 4.0);
    EXPECT_EQ(v[2].Y(), 6.0);
}

TEST(PolygonsTest, Polygon) {
    Polygon2D<double> poly;
    poly.AddPoint(Vector2D<double>(2.0,3.0));
    poly.AddPoint(Vector2D<double>(2.0,6.0));
    poly.AddPoint(Vector2D<double>(4.0,6.0));
    poly.AddPoint(Vector2D<double>(4.0,3.0));

    EXPECT_EQ(poly.Area(), 6.0);
}

TEST(PolygonsTest, Triangle) {
    Triangle2D<double> tr(Vector2D<double>(0.0, 0.0), Vector2D<double>(0.0, 1.0), Vector2D<double>(1.0, 0.0));

    EXPECT_EQ(tr.Area(), 0.5);
}

TEST(DistancesTest, PointLine) {
    Line<double> l(2.0, 3.0, 1.0);
    Vector2D<double> p(0.0, 0.0);

    EXPECT_EQ(Distance(p, l), 1/sqrt(13.0));
}

TEST(DistancesTest, PointLineTypedef) {
    Lined l(2.0, 3.0, 1.0);
    Vector2Dd p(0.0, 0.0);

    EXPECT_EQ(Distance(p, l), 1/sqrt(13.0));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
