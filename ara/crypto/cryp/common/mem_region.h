#ifndef ARA_CRYPTO_MEM_REGION_H
#define ARA_CRYPTO_MEM_REGION_H

#include "ara/core/span.h"

namespace ara
{
    namespace crypto
    {
        /**
         * @brief [SWS_CRYPT_10033]
         * Read-Only Memory Region (intended for [in] arguments)
         */
        using ReadOnlyMemRegion = ara::core::Span<const std::uint8_t>;

        /**
         * @brief [SWS_CRYPT_10031]
         * Read-Write Memory Region (intended for [in/out] arguments)
         */
        using ReadWriteMemRegion = ara::core::Span<std::uint8_t>;
    }
}

#endif // ARA_CRYPTO_MEM_REGION_H