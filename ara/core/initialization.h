#ifndef ARA_CORE_INITIALIZATION_H
#define ARA_CORE_INITIALIZATION_H
#include "ara/core/result.h"

namespace ara
{
    namespace core
    {
        /**
         * @brief [SWS_CORE_10001]
         * (Pre-)Initialization of the ARA Framework.
         * Prior to this call, interaction with the ARA is not allowed with the exception of types intended to
         * be used independently of initialization: ara::core::ErrorCode, ara::core::StringView,
         * ara::core::Result but not the function ValueOrThrow, ara::core::ErrorDomain and subclasses,
         * but not the function ThrowAsException. It is strongly recommended to make this call in a place
         * where it is guaranteed that static initialization has completed.
         * @return Result<void> a Result with an error code, in case an error occurred
         */
        Result<void> Initialize () noexcept;

        /**
         * @brief [SWS_CORE_10002]
         * Shutdown of the ARA Framework.
         * After this call, no interaction with the ARA is allowed with the exception of types intendent to be
         * used independently of initialization: ara::core::ErrorCode, ara::core::StringView,
         * ara::core::Result but not the function ValueOrThrow, ara::core::ErrorDomain and subclasses,
         * but not the function ThrowAsException. As a prerequisite to calling this API it is expected that
         * the use of ARA interfaces is completed (with the given exceptions). It is strongly recommended
         * to make this call in a place where it is guaranteed that the static initialization has completed and
         * destruction of statically initialized data has not yet started.
         * @return Result<void> a Result with an error code, in case an error occurred
         */
        Result<void> Deinitialize () noexcept;
    }
}


#endif // ARA_CORE_INITIALIZATION_H
