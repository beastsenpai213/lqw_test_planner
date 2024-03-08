#ifndef LQW_TEST_PLANNER_HPP_
#define LQW_TEST_PLANNER_HPP_

//一般需要的头文件
#include <cmath>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

//姿势消息包 
#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
//nav2包
#include "nav2_core/global_planner.hpp"
#include "nav_msgs/msg/path.hpp"
#include "nav2_util/robot_utils.hpp"
#include "nav2_util/lifecycle_node.hpp"
#include "nav2_costmap_2d/costmap_2d_ros.hpp"


namespace lqw_test_planner
{

class LqwTestPlanner : public nav2_core::GlobalPlanner//继承这个类来写路径规划,有五个虚寒暑需要命名
{
    public:
        LqwTestPlanner() = default;
        ~LqwTestPlanner() = default;
  // 插件初始化
  void configure(
        const rclcpp_lifecycle::LifecycleNode::WeakPtr & parent,
        std::string name, std::shared_ptr<tf2_ros::Buffer> tf,
        std::shared_ptr<nav2_costmap_2d::Costmap2DROS> costmap_ros
    ) override;

  // plugin cleanup
  void cleanup() override;

  // plugin activate
  void activate() override;

  // plugin deactivate
  void deactivate() override;

    // 创建路径,输入start,输出
  nav_msgs::msg::Path createPlan(
    const geometry_msgs::msg::PoseStamped & start,
    const geometry_msgs::msg::PoseStamped & goal) override;

    private:
  // TF buffer
  std::shared_ptr<tf2_ros::Buffer> tf_;

  // node ptr
  nav2_util::LifecycleNode::SharedPtr node_;

  // Global Costmap
  nav2_costmap_2d::Costmap2D * costmap_;

  // The global frame of the costmap
  std::string global_frame_, name_;

  double interpolation_resolution_;
};


}//namespace lqw_test_planner

#endif