#include "cslam/front_end/map_manager.h"
#include "cslam/front_end/stereo_handler.h"

template <class DataHandlerType>
MapManager<DataHandlerType>::MapManager(std::shared_ptr<rclcpp::Node> &node): node_(node),
  local_data_handler_(node) {

  node_->get_parameter("nb_robots", nb_robots_);
  node_->get_parameter("robot_id", robot_id_);
  node_->get_parameter("map_manager_process_period_ms", map_manager_process_period_ms_);

  std::chrono::milliseconds period(map_manager_process_period_ms_);

  process_timer_ = node_->create_wall_timer(
      std::chrono::milliseconds(period), std::bind(&MapManager<DataHandlerType>::process_new_keyframes, this));

  RCLCPP_INFO(node_->get_logger(), "Initialization done.");
}

template <class DataHandlerType>
void MapManager<DataHandlerType>::process_new_keyframes() {
  local_data_handler_.process_new_keyframe();
}
// TODO: intra-robot loop closures