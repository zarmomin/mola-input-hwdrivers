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
#include <mrpt/hwdrivers/CGenericSensor.h>

namespace mola
{
/**
 *
 * \ingroup mola_input_hwdrivers_grp */
class GenericSensor : public RawDataSourceBase
{
    DEFINE_MRPT_OBJECT(GenericSensor)

   public:
    GenericSensor();
    ~GenericSensor() override = default;

    // See docs in base class
    void initialize(const std::string& cfg_block) override;
    void spinOnce() override;

   private:
    mrpt::hwdrivers::CGenericSensor::Ptr sensor_;
};

}  // namespace mola
