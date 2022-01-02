#ifndef ARA_CRYPTO_CRYP_STREAM_CIPHER_CTX_H
#define ARA_CRYPTO_CRYP_STREAM_CIPHER_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23600]
             * Generalized Stream Cipher Context interface (it covers all modes of operation).
             */
            class StreamCipherCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_23601]
                 * Unique smart pointer of the interface
                 */
                using Uptr = std::unique_ptr<StreamCipherCtx>;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_STREAM_CIPHER_CTX_H