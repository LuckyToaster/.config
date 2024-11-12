#include <armadillo>
#include <vector>

using arma::vec;
using std::vector;

struct Line {
    vec p1;
    vec p2;
};

struct Shape {
    vector<Line> lines;
};

const Shape CUBE = 
