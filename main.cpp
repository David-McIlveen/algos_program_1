#include <plot_point.h>
#include <point_loader.h>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

// Goes from 0 to max, where if it's negative it loops back
// If max = 30 and value = -3, it would output 27
int bounded_mod_negative(int value, int max);
void print_polygon_status(string name, int i, string status);

// Our Algorithm, independed of any setup.
void algorithm(point* points, int point_count, int polygon_num, string polygon_name);
void smoke_test();

main (int argc, char *args []){
    polygon_batch* polygons = nullptr;
    try{
        polygons = getPolygons();
    } catch (const char* error) {
        cerr << "There was an error: " << string(error) << endl;
    }
    smoke_test();
    if(polygons == nullptr) exit(0); // Something happened and loading the file failed.

    ofstream benchmark_data;
    benchmark_data.open("time_data.csv");

    // For each polygon in the polygon batch...
    for (int i = 0; i < polygons->count; i++){
        polygon current_polygon = polygons->polygons[i];
        // Pull out nessary data
        point* points = current_polygon.points;
        int point_count = current_polygon.count;
        string polygon_name = current_polygon.name;
        // Get start time
        auto start = std::chrono::high_resolution_clock::now();
        // Run the Algo!
        algorithm(points, point_count, i, polygon_name);
        //Get end time
        auto end = std::chrono::high_resolution_clock::now();
        // From https://stackoverflow.com/questions/12937963/get-local-time-in-nanoseconds
        //Output Time
        benchmark_data << current_polygon.name << "," << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << endl;
        //Cleanup
        delete [] points;
        points = nullptr;
        current_polygon.points = nullptr;
    }
    delete [] polygons->polygons;
    delete [] polygons;

    benchmark_data.close();
    return 0;
}

void smoke_test(){
    cout << "Running Smoke Tests..." << endl;
    point a = point(0, 0);
    point b = point(1, 0);
    point c = point(1, 1);
    point d = point(0, 1);
    point e = point(0, .5);
    point* convex_poly_test = new point[5]{a, b, c, d, e};
    algorithm(convex_poly_test, 5, -1, "Smoke Test # 1");
    // Delete and remove pointer
    delete [] convex_poly_test; 
    convex_poly_test = nullptr; 

    point f = point(0, 0);
    point g = point(3, 0);
    point h = point(1, 1);
    point i = point(0, 3);
    point* concave_poly_test = new point[4]{f, g, h, i};
    algorithm(concave_poly_test, 4, -2, "Smoke Test # 2");
    // Delete and remove pointer
    delete [] concave_poly_test;
    concave_poly_test = nullptr;
}

void algorithm(point* points, int point_count, int polygon_num, string polygon_name){
    bool is_convex = true;
    if(point_count <= 2){ // Less than two points means it's a line, or a point. We can't work with those
        print_polygon_status(polygon_name, polygon_num, "does not contain enough data to run tests.");
        return; // Skip algo
    }
    if(point_count == 3){ // Triangles are always convex and the algorithm is not set up to handle them
        print_polygon_status(polygon_name, polygon_num, "is a Triangle, which is always convex.");
        return; // Skip algo
    }

    // For each point in the polygon...
    for (int i = 0; i < point_count && is_convex; i++){
        point one_plus = points[bounded_mod_negative(i + 1, point_count)];
        point lone_point = points[bounded_mod_negative(i, point_count)];
        point one_minus = points[bounded_mod_negative(i - 1, point_count)];
        line check = line(one_plus, one_minus);
        is_convex = check.isAlone(lone_point, points, point_count, i, bounded_mod_negative(i - 1, point_count), bounded_mod_negative(i + 1, point_count));
        // cout << " - For " << polygon_name << " at point [" << i << "] it is determined to be convex? :" << is_convex << endl;
    }

    if(is_convex){
        print_polygon_status(polygon_name, polygon_num, "is convex.");
    } else {
        print_polygon_status(polygon_name, polygon_num, "is concave.");
    }
}

inline int bounded_mod_negative(int value, int max){
    value = value % max;
    if(value < 0){
        value += max;
    }
    return value;
}

void print_polygon_status(string name, int i, string status){
    cout << "The Polygon : " << name << " (#" << i << ") " << status << endl;
}