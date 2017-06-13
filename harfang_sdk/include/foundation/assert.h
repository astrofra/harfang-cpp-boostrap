// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {

/// Trigger a system assert error (may be swapped by a platform specialized version).
extern void (*trigger_assert)(const char *source, int line, const char *function, const char *condition, const char *message);

} // gs

//#define ALWAYS_ENABLE_ASSERT

#if defined(ALWAYS_ENABLE_ASSERT) || defined(_DEBUG) || defined(MIXED_RELEASE)
 #define __ASSERT__(_EXP_) if (!(_EXP_)) gs::trigger_assert(__FILE__, __LINE__, __FUNCTION__, # _EXP_, nullptr)
 #define __ASSERT_IF__(_CND_, _EXP_) if (_CND_) if (!(_EXP_)) gs::trigger_assert(__FILE__, __LINE__, __FUNCTION__, # _EXP_, nullptr)
 #define __ASSERT_MSG__(_EXP_, _MSG_) if (!(_EXP_)) gs::trigger_assert(__FILE__, __LINE__, __FUNCTION__, # _EXP_, _MSG_)
 #define __ASSERT_ALWAYS__(_MSG_) gs::trigger_assert(__FILE__, __LINE__, __FUNCTION__, "ALWAYS", _MSG_)
#else
 #define __ASSERT__(_EXP_) false
 #define __ASSERT_IF__(_CND_, _EXP_) false
 #define __ASSERT_MSG__(_EXP_, _MSG_) false
 #define __ASSERT_ALWAYS__(_MSG_) false
#endif

#define __RASSERT__(_EXP_) if (!(_EXP_)) gs::trigger_assert(__FILE__, __LINE__, __FUNCTION__, # _EXP_, nullptr)
#define __RASSERT_MSG__(_EXP_, _MSG_) if (!(_EXP_)) gs::trigger_assert(__FILE__, __LINE__, __FUNCTION__, # _EXP_, _MSG_)
