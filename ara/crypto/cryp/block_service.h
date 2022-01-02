#ifndef ARA_CRYPTO_CRYP_BLOCK_SERVICE_H
#define ARA_CRYPTO_CRYP_BLOCK_SERVICE_H

#include "ara/crypto/cryp/extension_service.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
            * @brief [SWS_CRYPT_29030]
            * Extension meta-information service for block cipher contexts.
            */
            class BlockService : public ExtensionService
            {
            private:

            public:
                
                /**
                 * @brief [SWS_CRYPT_29035]
                 * Get actual bit-length of an IV loaded to the context.
                 * @param ivUid optional pointer to a buffer for saving an COUID of a
                 * IV object now loaded to the context. If the context
                 * was initialized by a SecretSeed object then the
                 * output buffer *ivUid must be filled by COUID of this
                 * loaded IV object, in other cases *ivUid must be filled
                 * by all zeros.
                 * @return std::size_t 
                 */
                virtual std::size_t GetActualIvBitLength (ara::core::Optional< CryptoObjectUid > ivUid) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29033]
                 * Get block (or internal buffer) size of the base algorithm.
                 * @return std::size_t size of the block in bytes
                 */
                virtual std::size_t GetBlockSize () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29032]
                 * Get default expected size of the Initialization Vector (IV) or nonce.
                 * @return std::size_t default expected size of IV in bytes
                 */
                virtual std::size_t GetIvSize () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29034]
                 * Verify validity of specific Initialization Vector (IV) length.
                 * @param[in] ivSize the length of the IV in bytes
                 * @return true if provided IV length is supported by the algorithm
                 * @return false otherwise
                 */
                virtual bool IsValidIvSize (std::size_t ivSize) const noexcept=0;
            };
        }
    }
}
#endif // ARA_CRYPTO_CRYP_BLOCK_SERVICE_H