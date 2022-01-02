#ifndef ARA_CRYPTO_CRYP_SYMMETRIC_KEY_WRAPPER_CTX_H
#define ARA_CRYPTO_CRYP_SYMMETRIC_KEY_WRAPPER_CTX_H

#include "ara/crypto/cryp/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_24000]
             * Context of a symmetric key wrap algorithm (for AES it should be compatible with RFC3394 or
             * RFC5649). The public interface of this context is dedicated for raw key material wrapping/
             * unwrapping, i.e. without any meta-information assigned to the key material in source crypto
             * object. But additionally this context type should support some "hidden" low-level methods
             * suitable for whole crypto object exporting/importing. Key Wrapping of a whole crypto object
             * (including associated meta-information) can be done by methods: ExportSecuredObject() and
             * ImportSecuredObject(), but without compliance to RFC3394 or RFC5649.
             */
            class SymmetricKeyWrapperCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_24001]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<SymmetricKeyWrapperCtx>;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SYMMETRIC_KEY_WRAPPER_CTX_H