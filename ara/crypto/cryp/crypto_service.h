#ifndef ARA_CRYPTO_CRYP_CRYPTO_SERVICE_H
#define ARA_CRYPTO_CRYP_CRYPTO_SERVICE_H

#include <memory>

#include "ara/crypto/cryp/extension_service.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_29020]
             * Extension meta-information service for cryptographic contexts.
             */
            class CryptoService : public ExtensionService
            {
            public:

                /**
                 * @brief [SWS_CRYPT_29024]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<CryptoService>;

                /**
                 * @brief [SWS_CRYPT_29023]
                 * Get block (or internal buffer) size of the base algorithm. For digest, byte-wise stream cipher and
                 * RNG contexts it is an informative method, intended only for optimization of the interface usage.
                 * @return std::size_t size of the block in bytes
                 */
                virtual std::size_t GetBlockSize () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29021]
                 * Get maximum expected size of the input data block. suppressPadding argument and it will be
                 * equal to the block size.
                 * @param suppressPadding if true then the method calculates the size for the case when the whole space of the plain data block is used for the payload only
                 * @return std::size_t maximum size of the input data block in bytes
                 */
                virtual std::size_t GetMaxInputSize (bool suppressPadding=false) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29022]
                 * Get maximum possible size of the output data block. If (IsEncryption() == true) then a value
                 * returned by this method is independent from the suppressPadding argument and will be equal
                 * to the block size.
                 * @param suppressPadding if true then the method calculates the size for the case when the whole space of the plain data block is used for the payload only
                 * @return std::size_t maximum size of the output data block in bytes
                 */
                virtual std::size_t GetMaxOutputSize (bool suppressPadding=false) const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_CRYPTO_SERVICE_H