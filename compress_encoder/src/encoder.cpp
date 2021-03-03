#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>

#include <pcl/compression/octree_pointcloud_compression.h>

#include <stdio.h>
#include <sstream>
#include <stdlib.h>


main (int argc, char** argv)
{
  int i=0;
  while(true)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  std::string location = "/home/bhaskar/exp_results/ab/";
	location.append(boost::lexical_cast<std::string>(i));
	location.append(".pcd");

  if (pcl::io::loadPCDFile<pcl::PointXYZ> (location, *cloud) == -1) //* load the file
  {
    std::cout << "Couldn't read file";
    break;
  }
  std::cout << "Loaded "
            << cloud->width * cloud->height
            << " data points from test_pcd.pcd with the following fields: "
            << std::endl;
 pcl::io::OctreePointCloudCompression<pcl::PointXYZ>* PointCloudEncoder;

// for a full list of profiles see: /io/include/pcl/compression/compression_profiles.h
    pcl::io::compression_Profiles_e compressionProfile = pcl::io::HIGH_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;

    // instantiate point cloud compression for encoding and decoding
    PointCloudEncoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZ> (compressionProfile, true);

 
// stringstream to store compressed point cloud
 std::stringstream compressedData;


// compress point cloud
 PointCloudEncoder->encodePointCloud (cloud, compressedData);


//writing to  file
std::ofstream  myfile;

std::stringstream s;
s << i;
std::string txtfpath = "/home/bhaskar/exp_results/txtfiles/"+s.str();
txtfpath=txtfpath+".txt";
myfile.open(txtfpath.c_str(), ios::out);
myfile<< compressedData.str();
myfile.close();

i++;

}

  return (0);
}
