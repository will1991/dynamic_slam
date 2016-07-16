#ifndef GRAPH_SLAM_UK_POINT_CLOUD_TOOLS
#define GRAPH_SLAM_UK_POINT_CLOUD_TOOLS

#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vector>

namespace pcl
{
template <typename PointType, typename Scalar>
void getMinMax2D(const pcl::PointCloud<PointType> &pcl, Scalar &minx,
                 Scalar &miny, Scalar &maxx, Scalar &maxy);

template <typename CellType, typename Scalar>
void getMinMaxNDT2D(const std::vector<CellType> &cells, Scalar &minx,
                    Scalar &miny, Scalar &maxx, Scalar &maxy);

template <typename PointType>
void visualizePcl(const typename PointCloud<PointType>::ConstPtr &pcl);

template <typename PointType>
void visualizePcl(const typename PointCloud<PointType>::ConstPtr &pcl1,
                  const typename PointCloud<PointType>::ConstPtr &pcl2);

////////////////////IMPLEMENTATION ///////////////
template <typename PointType, typename Scalar>
void getMinMax2D(const pcl::PointCloud<PointType> &pcl, Scalar &minx,
                 Scalar &miny, Scalar &maxx, Scalar &maxy)
{
  minx = miny = maxx = maxy = 0;
  for (size_t i = 0; i < pcl.size(); ++i) {
    if (pcl.points[i].x < minx)
      minx = pcl.points[i].x;
    if (pcl.points[i].x > maxx)
      maxx = pcl.points[i].x;
    if (pcl.points[i].y < miny)
      miny = pcl.points[i].y;
    if (pcl.points[i].y > maxy)
      maxy = pcl.points[i].y;
  }
}

template <typename CellType, typename Scalar>
void getMinMaxNDT2D(const std::vector<CellType> &cells, Scalar &minx,
                    Scalar &miny, Scalar &maxx, Scalar &maxy)
{
  minx = miny = maxx = maxy = 0;
  for (auto &&cell : cells) {
    auto mean = cell.getMean();
    if (mean(0) < minx)
      minx = mean(0);
    if (mean(0) > maxx)
      maxx = mean(0);
    if (mean(1) < miny)
      miny = mean(1);
    if (mean(1) > maxy)
      maxy = mean(1);
  }
}

template <typename PointType>
void visualizePcl(const typename PointCloud<PointType>::ConstPtr &pcl)
{
  // Initializing point cloud visualizer
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(
      new pcl::visualization::PCLVisualizer("3D Viewer"));
  viewer->setBackgroundColor(0, 0, 0);

  pcl::visualization::PointCloudColorHandlerCustom<PointType> target_color(
      pcl, 255, 0, 0);
  viewer->addPointCloud<PointType>(pcl, target_color, "vis cloud");
  viewer->setPointCloudRenderingProperties(
      pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "vis cloud");
  viewer->addCoordinateSystem(1.0, "global");
  // Wait until visualizer window is closed.
  while (!viewer->wasStopped()) {
    viewer->spinOnce(100);
    boost::this_thread::sleep(boost::posix_time::microseconds(100000));
  }
  viewer->close();
}

template <typename PointType>
void visualizePcl(const typename PointCloud<PointType>::ConstPtr &pcl1,
                  const typename PointCloud<PointType>::ConstPtr &pcl2)
{
  // Initializing point cloud visualizer
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(
      new pcl::visualization::PCLVisualizer("3D Viewer"));
  viewer->setBackgroundColor(0, 0, 0);
  // visualize firs cloud
  pcl::visualization::PointCloudColorHandlerCustom<PointType> first_color(
      pcl1, 255, 0, 0);
  viewer->addPointCloud<PointType>(pcl1, first_color, "first cloud");
  viewer->setPointCloudRenderingProperties(
      pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "first cloud");
  // visualize second cloud
  pcl::visualization::PointCloudColorHandlerCustom<PointType> second_color(
      pcl2, 0, 255, 0);
  viewer->addPointCloud<PointType>(pcl2, second_color, "second cloud");
  viewer->setPointCloudRenderingProperties(
      pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "second cloud");
  viewer->addCoordinateSystem(1.0, "global");
  // Wait until visualizer window is closed.
  while (!viewer->wasStopped()) {
    viewer->spinOnce(100);
    boost::this_thread::sleep(boost::posix_time::microseconds(100000));
  }
  viewer->close();
}
}

#endif