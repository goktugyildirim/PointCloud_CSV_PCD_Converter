#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <iostream>
#include <pcl/io/pcd_io.h>
/*
 * A class to read data from a csv file.
 */
class CSVReader
{
    std::string fileName;
    std::string delimeter;
public:
    CSVReader(std::string filename, std::string delm = ",") :
            fileName(filename), delimeter(delm)
    { }
    // Function to fetch data from a CSV File
    std::vector<std::vector<std::string> > getData();
};
/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/
std::vector<std::vector<std::string> > CSVReader::getData()
{
    std::ifstream file(fileName);
    std::vector<std::vector<std::string> > dataList;
    std::string line = "";
    // Iterate through each line and split the content using delimeter
    while (getline(file, line))
    {
        std::vector<std::string> vec;
        boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
        dataList.push_back(vec);
    }
    // Close the File
    file.close();
    return dataList;
}
int main()
{
    int csv_count = 45;
    for(int i=0; i<csv_count; i++)
    {
        std::string csv_name = "/home/goktug/projects/csv_to_pcd_ws/dataset/Hokuyo_" + std::to_string(i) + ".csv";
        std::cout << csv_name << std::endl;
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
        // Creating an object of CSVWriter
        CSVReader reader(csv_name);
        int counter = 0;
        // Get the data from CSV File
        std::vector<std::vector<std::string> > dataList = reader.getData();
        // Print the content of row by row on screen
        for(std::vector<std::string> vec : dataList)
        {
            pcl::PointXYZ point;
            for(int i=0; i<vec.size(); i++){
                if(i==1)
                {
                    std::vector<char> vector;
                    for (auto a : vec[i])
                        vector.push_back(a);

                    if(vector[0] != 'x'){
                        std::string x_val_string(vector.begin(),vector.end());
                        //std::cout << "x: " << x_val_string << std::endl;
                        float x_val_float = std::stof(x_val_string);

                        point.x = x_val_float;
                    }
                }
                if(i==2)
                {
                    std::vector<char> vector;
                    for (auto a : vec[i])
                        vector.push_back(a);

                    if(vector[0] != 'y'){
                        std::string x_val_string(vector.begin(),vector.end());
                        //std::cout << "y: " << x_val_string << std::endl;
                        float x_val_float = std::stof(x_val_string);
                        point.y = x_val_float;
                    }

                }
                if(i==3)
                {
                    std::vector<char> vector;
                    for (auto a : vec[i])
                        vector.push_back(a);

                    if(vector[0] != 'z'){
                        std::string x_val_string(vector.begin(),vector.end());
                        //std::cout << "z: " << x_val_string << std::endl;
                        float x_val_float = std::stof(x_val_string);
                        point.z = x_val_float;
                    }
                }

            }
            //std::cout << "Point x: " << point.x << " " << point.y << " " << point.z << std::endl;
            //std::cout<<std::endl;
            cloud->points.push_back(point);
        }
        std::cout << "Cloud " <<std::to_string(i)  << " size: " << cloud->size() << std::endl;
        std::string output_name = "/output_folder/" + std::to_string(i) + ".pcd";
        pcl::io::savePCDFile( output_name, *cloud, true );
    }
    return 0;
}
