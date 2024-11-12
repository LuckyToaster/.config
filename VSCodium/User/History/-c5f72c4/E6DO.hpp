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
        static vec project(vec point, vec camera, vec orientation, vec surface);

        static mat getXRotationMat(double angle);
        static mat getYRotationMat(double angle);
        static mat getZRotationMat(double angle);
        static mat getXYZRotationMat(double x_angle, double y_angle, double z_angle);

        static mat rotateX(mat m, double angle);
        static mat rotateY(mat m, double angle);
        static mat rotateZ(mat m, double angle);
        static mat rotateXYZ(mat m, double x_angle, double y_angle, double z_angle);
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


vec Projector::project(vec point, vec camera, vec orientation, vec surface) {
    if (point.size() < 3 || camera.size() < 3 || orientation.size() < 3 || surface.size() < 3)
        cerr << "please give points in 3D (vecs of size 3)" << endl;

    vec res(2);

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


mat Projector::getXRotationMat(double angle) {
    mat res = {
        {1.0, 0.0, 0.0},
        {0.0, cos(angle), -sin(angle)},
        {0.0, sin(angle), cos(angle)}
    };
    return res;
}


mat<double Projector::getYRotationMat(double angle) {
    mat res = {
        {cos(angle), 0.0, sin(angle)},
        {0.0, 1.0, 0.0},
        {-sin(angle), 0.0, cos(angle)}
    };
    return res;
}


mat Projector::getZRotationMat(double angle) {
    mat res = {
        {cos(angle), -sin(angle), 0.0},
        {sin(angle), cos(angle), 0.0},
        {0.0, 0.0, 1.0}
    };
    return res;
}


mat Projector::getXYZRotationMat(double x_angle, double y_angle, double z_angle) {
    return getXRotationMat(x_angle) * getYRotationMat(y_angle) * getZRotationMat(z_angle);
}

mat Projector::rotateX(mat m, double angle ) {
    return m * getXRotationMat(angle);
}

mat Projector::rotateY(mat m, double angle) {
    return m * getYRotationMat(angle);
}

mat Projector::rotateZ(mat m, double angle) {
    return m * getZRotationMat(angle);
}

mat Projector::rotateXYZ(mat m, double x_angle, double y_angle, double z_angle) {
    return m * getXRotationMat(x_angle) * getYRotationMat(y_angle) * getZRotationMat(z_angle);
}