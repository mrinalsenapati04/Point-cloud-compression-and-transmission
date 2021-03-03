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
  //reading file
int i=0;
while (true)
{
std::ifstream file;

std::stringstream s;
s << i;
std::string txtfpath = "/home/bhaskar/exp_results/txtfiles/"+s.str();
txtfpath=txtfpath+".txt";
file.open(txtfpath.c_str(), ios::out);
if (file.is_open())
{
std::stringstream buffer;
buffer << file.rdbuf();
file.close();

//decoder
 pcl::io::OctreePointCloudCompression<pcl::PointXYZ>* PointCloudDecoder;
// for a full list of profiles see: /io/include/pcl/compression/compression_profiles.h
    pcl::io::compression_Profiles_e compressionProfile = pcl::io::HIGH_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;

    // instantiate point cloud compression for encoding and decoding
   
    PointCloudDecoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZ> ();

  // output pointcloud
      pcl::PointCloud<pcl::PointXYZ>::Ptr cloudOut (new pcl::PointCloud<pcl::PointXYZ>);
     



 // decompress point cloud
        PointCloudDecoder->decodePointCloud (buffer, cloudOut);
        std::string location = "/home/bhaskar/exp_results/pcd/";
	location.append(boost::lexical_cast<std::string>(i));
	location.append(".pcd");
        std::cout<<location<<std::endl;
	pcl::io::savePCDFileASCII(location,*cloudOut); 
        i++;
	}
else
	break;
}

  return (0);
}
