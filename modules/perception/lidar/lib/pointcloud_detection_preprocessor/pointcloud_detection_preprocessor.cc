/******************************************************************************
 * Copyright 2022 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/perception/lidar/lib/pointcloud_detection_preprocessor/pointcloud_detection_preprocessor.h"

#include "modules/perception/lidar/lib/pointcloud_detection_preprocessor/pointcloud_downsample/point_cloud_down_sample.h"
#include "modules/perception/pipeline/plugin_factory.h"

namespace apollo {
namespace perception {
namespace lidar {

bool PointCloudDetectionPreprocessor::Init(const StageConfig& stage_config) {
  if (!Initialize(stage_config)) {
    return false;
  }

  ACHECK(stage_config.has_pointcloud_detection_preprocessor());
  pointcloud_detection_preprocessor_config_ =
      stage_config.pointcloud_detection_preprocessor();

  pointcloud_downsample_ =
      PluginFactory::CreatePlugin(stage_config.pointcloud_downsample());
  if (!pointcloud_downsample_->Init(stage_config.pointcloud_downsample())) {
    return false;
  }
  return true;
}

bool PointCloudDetectionPreprocessor::Process(DataFrame* data_frame) {
  return true;
}

bool PointCloudDetectionPreprocessor::Process(DataFrame* data_frame,
                                              float* points_array,
                                              int num_points) {
  if (nullptr == data_frame) {
    AERROR << "Input null data_frame ptr.";
    return false;
  }
  if (nullptr == points_array) {
    AERROR << "Input null points_array ptr.";
    return false;
  }
  if (!pointcloud_downsample_->Process(data_frame, points_array, num_points)) {
    return false;
  }
  return true;
}

}  // namespace lidar
}  // namespace perception
}  // namespace apollo
