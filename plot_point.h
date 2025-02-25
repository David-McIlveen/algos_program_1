#ifndef PLOT_POINT
#define PLOT_POINT

const double line_check_precision = .000001;

enum point_status{
    greater,
    equal,
    less
};

class point{
    public:
        point();
        point(double x, double y);
        bool operator==(const point &other);
        double getX();
        double getY();
    private:
        double _x;
        double _y;
};

class line{
    public:
        //Creates a line based on points A and B
        line(point a, point b);

        // Determines if the lone point is on one side of the line and otherA and otherB on are on the other.
        // True if A and B are on the otherside of the line of L
        // False if A or B is equal to the line or on the same side as L
        bool isAlone(point lone, point otherA, point otherB);
    private:
        point_status getPointStatus(point a);
        // Is A less, greater or equal to be within a given precision ?
        point_status getPresisionStatus(double d, double b, double precision);
        bool _isVert;
        double _slope;
        double _intercept;
};

#endif