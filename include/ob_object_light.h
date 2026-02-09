#pragma once


#include <string>
#include <vector>
#include <optional>

#include "ob_uuid_t.h"
#include "ob_function.h"
#include "ob_object.h"
#include "ob_object_factory.h"



#if OBLIGHT_MODULE_BUILD == 1
#define OBL_EXTERN extern "C"
OBL_EXTERN OB::ObjectFactory* OBLGetFactory(const OB::uuid_t& subVersionUUID); // Must user Inplantieren 
#else
typedef OB::ObjectFactory* (*LPOBLGetFactory)(const OB::uuid_t& subVersionUUID);
#endif