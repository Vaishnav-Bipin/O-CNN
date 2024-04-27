#include "points.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

//using namespace std;
// ...
// Specify the filename of the points
int main() {

    // string infilename_pts = "tweezer_1.stp_p.xyz";
    string infilename_pts = "../../../../PC_files/construction/test/Newport - FP-1A.stp_p.xyz";
    std::cout << infilename_pts << "\n";
    // string infilename_nrms = "tweezer_1.stp_n.xyz";
    string infilename_nrms = "../../../../PC_files/construction/test/Newport - FP-1A.stp_n.xyz";
    std::cout << infilename_nrms << "\n";

    Points points;


    vector<float> pts;
    vector<float> normals;
    vector<float> features;
    vector<float> labels;

    
    std::ifstream source;                    // build a read-Stream
    source.open(infilename_pts, std::ios_base::in);

    int i = 0;
    for(std::string line; std::getline(source, line); )   //read stream line by line
    {
        std::istringstream in(line);      //make a stream for the line itself

        float x, y, z;
        in >> x >> y >> z;       //now read the whitespace-separated floats

        std::cout << x << " " << y << " " << z << "\n";

        i += 1;
        pts.push_back(x);
        pts.push_back(y);
        pts.push_back(z);
    }

    std::ifstream source1; 
    source1.open(infilename_nrms, std::ios_base::in);

    // int i = 0;
    for(std::string line; std::getline(source1, line); )   //read stream line by line
    {
        std::istringstream in(line);      //make a stream for the line itself

        float x, y, z;
        in >> x >> y >> z;       //now read the whitespace-separated floats

        std::cout << x << " " << y << " " << z << "\n";

        i += 1;
        normals.push_back(x);
        normals.push_back(y);
        normals.push_back(z);
    }

    points.set_points(pts, normals, features, labels); 
    points.write_points("tweezer_1.stp.points");


    // vector<char> buffer = points.get_buffer();
    // std::cout << buffer[0];
    
    return 0;
}
