/* -------------------------------------------------------------------------
 *   A Modular Optimization framework for Localization and mApping  (MOLA)
 * Copyright (C) 2018-2019 Jose Luis Blanco, University of Almeria
 * See LICENSE for license information.
 * ------------------------------------------------------------------------- */
/**
 * @file   GenericSensor.h
 * @brief  RawDataSource from any sensor supported by mrpt-hwdrivers
 * @author Jose Luis Blanco Claraco
 * @date   Feb 15, 2019
 */
#pragma once

#include <mola-kernel/interfaces/RawDataSourceBase.h>

namespace mola
{
namespace sensor_hwdrivers
{
/**
 *
 * \ingroup mola_sensor_hwdrivers_grp */
class GenericSensor : public RawDataSourceBase
{
   public:
    GenericSensor();
    ~GenericSensor() override = default;

    // See docs in base class
    void initialize(const std::string& cfg_block) override;
    void spinOnce() override;

   private:
};

}  // namespace sensor_hwdrivers
}  // namespace mola
