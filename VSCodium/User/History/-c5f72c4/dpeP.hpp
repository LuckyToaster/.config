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

        static mat<double> getXRotationMat(double angle);
        static mat<double> getYRotationMat(double angle);
        static mat<double> getZRotationMat(double angle);
        static mat<double> getXYZRotationMat(double x_angle, double y_angle, double z_angle);

        static mat<double> rotateX(mat<double> m, double angle);
        static mat<double> rotateY(mat<double> m, double angle);
        static mat<double> rotateZ(mat<double> m, double angle);
        static mat<double> rotateXYZ(mat<double> m, double x_angle, double y_angle, double z_angle);
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


vec<double> Projector::project(vec<double> point, vec<double> camera, vec<double> orientation, vec<double> surface) {
    if (point.size() < 3 || camera.size() < 3 || orientation.size() < 3 || surface.size() < 3)
        cerr << "please give points in 3D (vecs of size 3)" << endl;

    vec<double> res(2);

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


mat<double> Projector::getXRotationMat(double angle) {
    mat<double> res = {
        {1.0, 0.0, 0.0},
        {0.0, cos(angle), -sin(angle)},
        {0.0, sin(angle), cos(angle)}
    };
    return res;
}


mat<double Projector::getYRotationMat(double angle) {
    mat<double> res = {
        {cos(angle), 0.0, sin(angle)},
        {0.0, 1.0, 0.0},
        {-sin(angle), 0.0, cos(angle)}
    };
    return res;
}


mat<double> Projector::getZRotationMat(double angle) {
    mat<double> res = {
        {cos(angle), -sin(angle), 0.0},
        {sin(angle), cos(angle), 0.0},
        {0.0, 0.0, 1.0}
    };
    return res;
}


mat<double> Projector::getXYZRotationMat(double x_angle, double y_angle, double z_angle) {
    return getXRotationMat(x_angle) * getYRotationMat(y_angle) * getZRotationMat(z_angle);
}

mat<double> Projector::rotateX(mat<double> m, double angle ) {
    return m * getXRotationMat(angle);
}

mat<double> Projector::rotateY(mat<double> m, double angle) {
    return m * getYRotationMat(angle);
}

mat<double> Projector::rotateZ(mat<double> m, double angle) {
    return m * getZRotationMat(angle);
}

mat<double> Projector::rotateXYZ(mat<double> m, double x_angle, double y_angle, double z_angle) {
    return m * getXRotationMat(x_angle) * getYRotationMat(y_angle) * getZRotationMat(z_angle);
}