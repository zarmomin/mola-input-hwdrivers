/* -------------------------------------------------------------------------
 *   A Modular Optimization framework for Localization and mApping  (MOLA)
 * Copyright (C) 2018-2019 Jose Luis Blanco, University of Almeria
 * See LICENSE for license information.
 * ------------------------------------------------------------------------- */
/**
 * @file   GenericSensor.cpp
 * @brief  RawDataSource from any sensor supported by mrpt-hwdrivers
 * @author Jose Luis Blanco Claraco
 * @date   Feb 15, 2019
 */

/** \defgroup mola_input_hwdrivers_grp mola_input_hwdrivers_grp.
 * RawDataSource from any sensor supported by mrpt-hwdrivers
 *
 *
 */

#include <mola-input-hwdrivers/GenericSensor.h>
#include <mola-kernel/yaml_helpers.h>
#include <mrpt/core/initializer.h>
#include <yaml-cpp/yaml.h>

using namespace mola;

IMPLEMENTS_MRPT_OBJECT_NS_PREFIX(GenericSensor, RawDataSourceBase, mola);

MRPT_INITIALIZER(do_register_GenericSensor)
{
    MOLA_REGISTER_MODULE(GenericSensor);
}

GenericSensor::GenericSensor() = default;

void GenericSensor::initialize(const std::string& cfg_block)
{
    using namespace std::string_literals;

    MRPT_START
    ProfilerEntry tle(profiler_, "initialize");

    // Mandatory parameters:
    auto c = YAML::Load(cfg_block);

    ENSURE_YAML_ENTRY_EXISTS(c, "params");
    auto cfg = c["params"];
    MRPT_LOG_DEBUG_STREAM("Initializing with these params:\n" << cfg);

    // YAML_LOAD_MEMBER_REQ(base_dir, std::string);

    MRPT_END
}  // end initialize()

void GenericSensor::spinOnce()
{
    MRPT_START
    ProfilerEntry tleg(profiler_, "spinOnce");

    MRPT_END
}
