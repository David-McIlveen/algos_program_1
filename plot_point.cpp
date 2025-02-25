#include <plot_point.h>

point::point() : point(0, 0) {}

point::point(double x, double y){_x = x; _y = y;}

bool point::operator==(const point &other){
    return other._x == _x && other._y == _y;
}

double point::getX(){
    return _x;
}

double point::getY(){
    return _y;
}

line::line(point a, point b){
    //We cannot make a line from two points of the same value
    if(a == b) throw "A and B cannot be the same value!";

    //Check if the line is a horizontal line
    _isVert = a.getX() == b.getX();

    //If not, solve for slope and intercept
    if(!_isVert){
        // Point Slope Form: y = m*x - m*x1 + y1 
        // Slope = (y1 - y2) / (x1 - x2)
        // Intercept = -m*x1 + y1
        _slope = (a.getY() - b.getY()) / (a.getX() - b.getX());
        _intercept = _slope * -1 * a.getX() + a.getY();
    } else {
        _slope = 0; // We won't use the slope, but we don't want to divide by 0.
        _intercept = a.getX(); // Set the intercept to X value to check later
    }
}

bool line::isAlone(point lone, point* others, int n, int ignore, int igorePlus, int ignoreMinus){
    point_status lone_status = getPointStatus(lone);
    if(lone_status == equal) return true;

    point_status value = equal;
    for (int i = 0; i < n; i++){
        if(i == ignore || i == igorePlus || i == ignoreMinus) continue;
        point_status this_status = getPointStatus(others[i]);
        if(this_status == equal) continue;
        if(lone_status == this_status) return false;
    }
    return true;
}

point_status line::getPointStatus(point a){
    // Point Slope Form: y = m*x - m*x1 + y1 
    if(_isVert){
        // If the line is horizontal, check the y values only
        // _intercept should store where the line crosses the X Axis
        return getPresisionStatus(a.getX(), _intercept, line_check_precision);
    } else {
        // y = m*x + b
        double expected_y = _slope * a.getX() + _intercept;
        return getPresisionStatus(a.getY(), expected_y, line_check_precision);
    }

}

point_status line::getPresisionStatus(double a, double b, double precision){
    double diff = a - b;
    if(diff * diff <= precision * precision) return equal;
    if(diff < 0) return less;
    return greater;
}