#include <point_loader.h>
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

// Gets a point from a string
// Two numbers sepreated by white space.
point get_point(string str);

// Splits a string up by whitespace
// Returns a pointer to a vector or substrings.
vector<string>* split_on_whitespace(string str);

polygon_batch* getPolygons(){
    fs::path current_path = fs::current_path();
    fs::path polygons_dir = current_path / "polygons";
    if(!fs::is_directory(polygons_dir)){
        throw "The dir \'polygons\' does not exist in the current context, please add it.";
    }

    vector<polygon> polygon_heap;

    for (const auto & entry : fs::directory_iterator(polygons_dir)){
        fs::path file_path = entry.path();   
        std::ifstream text_to_process;
        text_to_process.open(file_path);
        polygon polygon_m;
        string line;
        if(std::getline(text_to_process, line)){
            polygon_m.name = line;
        } else {
            continue; // Empty File, don't process
        }
        vector<point> points_to_process;
        // From https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
        while(std::getline(text_to_process, line)){
            std::istringstream iss(line);
            double a, b;
            if (!(iss >> a >> b)) { break; } // error
            points_to_process.push_back(point(a, b));
        }

        int points_array_size = points_to_process.size();
        polygon_m.points = new point[points_array_size];
        for (int i = 0; i < points_array_size; i++){
            polygon_m.points[i] = points_to_process.at(i);
        }
        polygon_m.count = points_array_size;
        polygon_heap.push_back(polygon_m);

    }
    polygon_batch* to_return = new polygon_batch;
    to_return->count = polygon_heap.size();
    to_return->polygons = new polygon[to_return->count];
    for (int i = 0; i < to_return->count; i++){
        to_return->polygons[i] = polygon_heap.at(i);
    }
    
    return to_return; // Temp
}

