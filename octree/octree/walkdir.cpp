#include "points.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <filesystem>

// #include <string>
// #include <vector>

// using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int main() {
    string base_new = "../../pytorch/projects/data/GrabCad67L/GrabCad67L.points";
    string base_old = "../../../../PC_files_67_level";
    int l1 = base_old.length();
    int l2 = base_new.length();

    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(base_old)) {
        
        string pth_old = dirEntry.path().string();

        int p_xyz = 0;
        if (pth_old.substr(pth_old.length()-6, 6) == "_p.xyz")
            p_xyz = 1;
        
        if (p_xyz) {
            string pth_old_p = pth_old;
            string pth_old_n = pth_old.substr(0, pth_old.length() -6) + "_n.xyz"; 
            string pth_new = base_new + "/" + pth_old.substr(l1+1, pth_old.length()-l1-6) + ".points";
            // string pth_new = "abc.points";
            // string pth_new = "Newport - FP-1A.stp.points";

            // string pth_old_p = "../../../../PC_files/construction/test/Newport - FP-1A.stp_p.xyz";
            // string pth_old_n = "../../../../PC_files/construction/test/Newport - FP-1A.stp_n.xyz";
            // string pth_new = "../../pytorch/projects/data/GrabCad100K/GrabCad100K/construction/test/Newport - FP-1A.stp.points";

            // -----------------------------------------------------------------------------
            vector<float> pts;
            vector<float> normals;
            vector<float> features;
            vector<float> labels;

            
            std::ifstream source;                    // build a read-Stream
            source.open(pth_old_p, std::ios_base::in);

            // int i = 0;
            for(std::string line; std::getline(source, line); )   //read stream line by line
            {
                std::istringstream in(line);      //make a stream for the line itself

                float x, y, z;
                in >> x >> y >> z;       //now read the whitespace-separated floats

                // std::cout << x << " " << y << " " << z << "\n";

                // i += 1;
                pts.push_back(x);
                pts.push_back(y);
                pts.push_back(z);
            }

            std::ifstream source1; 
            source1.open(pth_old_n, std::ios_base::in);

            // int i = 0;
            for(std::string line; std::getline(source1, line); )   //read stream line by line
            {
                std::istringstream in(line);      //make a stream for the line itself

                float x, y, z;
                in >> x >> y >> z;       //now read the whitespace-separated floats

                // std::cout << x << " " << y << " " << z << "\n";

                // i += 1;
                normals.push_back(x);
                normals.push_back(y);
                normals.push_back(z);
            }

            Points points;
            points.set_points(pts, normals, features, labels); 
            bool b = points.write_points(pth_new);
            // std::cout << b << "\n";

            // -----------------------------------------------------------------------------






            // std::cout << pth_old << " " << pth_new  << " " << std::endl;

            // break;
        }
        
    }
    return 0;
}
