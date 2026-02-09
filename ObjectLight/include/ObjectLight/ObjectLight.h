#pragma once


#include <string>
#include <vector>
#include <optional>

#include "Common.h"
#include "uuid.h"
#include "Function.h"
#include "Object.h"
#include "Objects.h"
#include "ObjectFactory.h"

#if OBLIGHT_MODULE_BUILD == 1
OBL_EXTERN OBL_API OB::ObjectFactory* OBLGetFactory(const uuid& subVersionUUID); // Must user Inplantieren 
#else
typedef OB::ObjectFactory* (*LPOBLGetFactory)(const uuid& subVersionUUID);
#endif