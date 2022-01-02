#ifndef ARA_CRYPTO_CRYP_SYMMETRIC_BLOCK_CIPHER_CTX_H
#define ARA_CRYPTO_CRYP_SYMMETRIC_BLOCK_CIPHER_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23700]
             * Interface of a Symmetric Block Cipher Context with padding.
             */
            class SymmetricBlockCipherCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_23701]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<SymmetricBlockCipherCtx>;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SYMMETRIC_BLOCK_CIPHER_CTX_H