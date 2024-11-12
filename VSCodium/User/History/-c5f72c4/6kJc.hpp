#include <iostream>
#include <cmath>
#include <armadillo>

using std::cerr;
using std::endl;
using std::cos;
using std::sin;
using arma::mat;
using arma::vec;


/* 
    see https://en.wikipedia.org/wiki/3D_projection -> mathematical formula
    see https://en.wikipedia.org//wiki/Rotation_matrix -> rotation matrices
    see https://en.wikipedia.org/wiki/Euler_angles#Tait%E2%80%93Bryan_angles 
        -> 3 angles (one for each axis)
        -> ORDER MATTERS: if we do XYZ rotation -> rot x, then rot y then rot z, (different order different result)
        -> to rotate point or 3x3 basis, we multiply it by its rotation matrices in the order we want
    maybe see quaternions? https://en.wikipedia.org/wiki/Rotation_formalisms_in_three_dimensions 
*/
class Projector {
    public:
        //vec point, camera, orientation, surface; 
        //Projector(vec p, vec c, vec c_orientation, vec s);
        static vec<float> project(vec<float point, vec<float> camera, vec<float> orientation, vec<float> surface);

        static mat<float> getXRotationMat(float angle);
        static mat<float> getYRotationMat(float angle);
        static mat<float> getZRotationMat(float angle);
        static mat<float> getXYZRotationMat(float x_angle, float y_angle, float z_angle);

        static mat<float> rotateX(mat<float> m, float angle);
        static mat<float> rotateY(mat<float> m, float angle);
        static mat<float> rotateZ(mat<float> m, float angle);
        static mat<float> rotateXYZ(mat<float> m, float x_angle, float y_angle, float z_angle);
};


//Projector::Projector(vec point, vec camera, vec c_orientation, vec surface) {
//    if (p.size() == 3 && c.size() == 3 && c_orient.size() == 3 && s.size() == 3) {
//        this->point = point;
//        this->camera = camera;
//        this->orientation = c_orientation;
//        this->surface = surface;
//
//    } else cerr << "please give valid parameters" << endl;
//}


vec<float> Projector::project(vec<float> point, vec<float> camera, vec<float> orientation, vec<float> surface) {
    if (point.size() < 3 || camera.size() < 3 || orientation.size() < 3 || surface.size() < 3)
        cerr << "please give points in 3D (vecs of size 3)" << endl;

    vec<float> res(2);

    if (point.is_zero() && camera.is_zero()) {
        res(0) = point(0);
        res(1) = point(1);
        return res;
    }

    vec d(3);
    if (orientation.is_zero()) d = point - camera;
    else d = getXYZRotationMat(orientation(0), orientation(1), orientation(2)) * (point - camera);

    res(0) = (surface(2) / d(2) * d(0)) + surface(0);
    res(1) = (surface(2) / d(2) * d(1)) + surface(1);
    return res;
}


mat<float> Projector::getXRotationMat(float angle) {
    mat<float> res = {
        {1.0, 0.0, 0.0},
        {0.0, cos(angle), -sin(angle)},
        {0.0, sin(angle), cos(angle)}
    };
    return res;
}


mat<float Projector::getYRotationMat(float angle) {
    mat<float> res = {
        {cos(angle), 0.0, sin(angle)},
        {0.0, 1.0, 0.0},
        {-sin(angle), 0.0, cos(angle)}
    };
    return res;
}


mat<float> Projector::getZRotationMat(float angle) {
    mat<float> res = {
        {cos(angle), -sin(angle), 0.0},
        {sin(angle), cos(angle), 0.0},
        {0.0, 0.0, 1.0}
    };
    return res;
}


mat<float> Projector::getXYZRotationMat(float x_angle, float y_angle, float z_angle) {
    return getXRotationMat(x_angle) * getYRotationMat(y_angle) * getZRotationMat(z_angle);
}

mat<float> Projector::rotateX(mat<float> m, float angle ) {
    return m * getXRotationMat(angle);
}

mat<float> Projector::rotateY(mat<float> m, float angle) {
    return m * getYRotationMat(angle);
}

mat<float> Projector::rotateZ(mat<float m, float angle) {
    return m * getZRotationMat(angle);
}

mat Projector::rotateXYZ(mat m, double x_angle, double y_angle, double z_angle) {
    return m * getXRotationMat(x_angle) * getYRotationMat(y_angle) * getZRotationMat(z_angle);
}