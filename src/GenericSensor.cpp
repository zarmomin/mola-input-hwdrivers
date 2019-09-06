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
#include <mrpt/config/CConfigFileMemory.h>
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
    using namespace mrpt::hwdrivers;

    MRPT_START ProfilerEntry tle(profiler_, "initialize");

    // Mandatory parameters:
    auto c = YAML::Load(cfg_block);

    ensureYamlEntryExists(c, "params");
    auto cfg = c["params"];
    MRPT_LOG_DEBUG_STREAM("Initializing with these params:\n" << cfg);

    std::string driver;
    yamlLoadMemberReq<std::string>(cfg, "driver", &driver);

    sensor_ = CGenericSensor::createSensorPtr(driver);
    if (!sensor_)
    {
        THROW_EXCEPTION_FMT(
            "***ERROR***: Sensor driver class name not recognized: `%s`",
            driver.c_str());
    }

    // Load common & sensor specific parameters:
    const std::string cfg_params = mola::yaml2string(cfg);

    mrpt::config::CConfigFileMemory cfgYaml;
    cfgYaml.setContentFromYAML(cfg_params);
    sensor_->loadConfig(cfgYaml, "");

    MRPT_TODO("use external dir?");
    // For imaging sensors, set external storage directory:
    // sensor->setPathForExternalImages(rawlog_ext_imgs_dir);

    MRPT_LOG_INFO_STREAM("Initializing sensor of class:" << driver);

    // Init device:
    sensor_->initialize();

    MRPT_END
}  // end initialize()

void GenericSensor::spinOnce()
{
    using namespace mrpt::hwdrivers;

    MRPT_START
    ProfilerEntry tleg(profiler_, "spinOnce");

    // Process
    sensor_->doProcess();

    // Get new observations
    CGenericSensor::TListObservations lstObjs;
    sensor_->getObservations(lstObjs);

    // Send to front-ends:
    for (auto& to : lstObjs)
    {
        auto& ptrSerializable = to.second;
        auto  ptrObj =
            mrpt::ptr_cast<mrpt::obs::CObservation>::from(ptrSerializable);
        this->sendObservationsToFrontEnds(ptrObj);
    }

    MRPT_END
}
