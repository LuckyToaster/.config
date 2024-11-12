using glm::vec3;

class Camera {
    vec3 pos;
    vec3 orientation;
    static Camera getDefault();
};

// Function to strafe the camera left or right ==> wtf?
void strafe(Camera &camera, double distance) {
    camera.pos.x += distance * sin(camera.orientation.x);
    camera.pos.y -= distance * cos(camera.orientation.x);
}
