#ifndef _SRC_CORE_ASSERT_H_
#define _SRC_CORE_ASSERT_H_

#define APP_ASSERT_NO_INFO(condition){if(!(condition)){APP_ERROR("Assertion Failed:"); assert(false); }}
#define APP_ASSERT_INFO(condition, message){if(!(condition)){APP_ERROR("Assertion Failed: {}",message); assert(false);}}

#endif