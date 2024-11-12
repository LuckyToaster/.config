//using arma::vec;

using glm::vec3;



struct Camera {
    vec3 pos;
    vec3 orientation;
};

// Function to strafe the camera left or right ==> wtf?
void strafe(Camera &camera, double distance) {
    // Assuming orientation[0] is the yaw angle
    camera.pos(0) += distance * sin(camera.orientation(0));
    camera.pos(1) -= distance * cos(camera.orientation(0));
}
