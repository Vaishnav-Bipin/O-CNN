

#include "points.h"
#include <iostream>
#include <string>
#include <vector>

//using namespace std;
// ...
// Specify the filename of the points
int main() {
    float avg = 0;
    float c = 0;
    for (int i=627; i<= 627; i++) {
        string s = std::to_string(i);
        s.insert(0, 4 - s.length(), '0');
        string filename = "../../pytorch/projects/data/ModelNet40/ModelNet40.points/airplane/test/airplane_.upgrade.smp.points";
        filename.insert(57+9+5+9, s);
        std::cout << filename << " ";
// Load points
        Points points;
        points.read_points(filename);

        // Points points2;
        // points2.set_points(points.points(), points.normal(), points.feature(), points.label());

        points.write_points("here.points");

        

// Point number
        int n =  points.info().pt_num();
        std::cout << n << "\n";
        avg = avg + n;
        c = c + 1;

        const float* pts1 = points.normal();
        std::cout << pts1[0] << " " << pts1[1] << " " << pts1[2] << pts1[3] << " " << pts1[4] << " " << pts1[5] << "\n";

        vector<char> pts = points.get_buffer();
        char* buffer = pts.data();
        std::cout << buffer[0] << buffer[1] << buffer[2] << buffer[3] << buffer[4] << buffer[5] << buffer[6] << buffer[7] << "\n";

        // Whether does the file contain point coordinates?
        bool has_points = points.info().has_property(PointsInfo::kPoint);
        // Get the pointer to points: x_1, y_1, z_1, ..., x_n, y_n, z_n
        const float* ptr_points = points.ptr(PointsInfo::kPoint);

        // Whether does the file contain normals?
        bool has_normals = points.info().has_property(PointsInfo::kNormal);
        // Get the pointer to normals: nx_1, ny_1, nz_1, ..., nx_n, ny_n, nz_n
        // const float* ptr_normals = points.ptr(PointsInfo::kNormal);

        // Whether does the file contain per-point labels?
        bool has_labels = points.info().has_property(PointsInfo::kLabel);
        // Get the pointer to labels: label_1, label_2, ..., label_n
        const float* ptr_labels = points.ptr(PointsInfo::kLabel);

        std::cout << has_points << " " << has_normals << " " << has_labels << "\n";
    }
    // std::cout << "\n";
    // avg = avg / c;
    // std::cout << avg << "\n";

    return 0;
}
