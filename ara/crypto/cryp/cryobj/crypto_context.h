#ifndef ARA_CRYPTO_CRYP_CYPTO_CONTEXT_H
#define ARA_CRYPTO_CRYP_CYPTO_CONTEXT_H

#include "ara/crypto/cryp/common/base_id_types.h"
#include "ara/crypto/cryp/crypto_provider.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_20400]
             * A common interface of a mutable cryptographic context, i.e. that is not binded to a single crypto
             * object.
             */
            class CryptoContext
            {
            public:    
            
                /**
                 * @brief [SWS_CRYPT_20402]
                 * Type definition of vendor specific binary Crypto Primitive ID.
                 */
                using AlgId = CryptoAlgId;

                /**
                 * @brief [SWS_CRYPT_20401]
                 * Destroy the Crypto Context object                 * 
                 */
                virtual ~CryptoContext () noexcept=default;

                /**
                 * @brief [SWS_CRYPT_20411]
                 * Return CryptoPrimitivId instance containing instance identification.
                 * @return CryptoPrimitiveId::Uptr 
                 */
                virtual CryptoPrimitiveId::Uptr GetCryptoPrimitiveId () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20412]
                 * Check if the crypto context is already initialized and ready to use. It checks all required values,
                 * including: key value, IV/seed, etc
                 * @return true if the crypto context is completely initialized and ready to use
                 * @return false otherwise
                 */
                virtual bool IsInitialized () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30214]
                 * Copy-assign another CryptoContext to this instance.
                 * @param other the other instance
                 * @return CryptoContext& *this, containing the contents of other
                 */
                CryptoContext& operator= (const CryptoContext &other)=default;

                /**
                 * @brief [SWS_CRYPT_30215]
                 * Move-assign another CryptoContext to this instance.
                 * @param other the other instance
                 * @return CryptoContext& *this, containing the contents of other
                 */
                CryptoContext& operator= (CryptoContext &&other)=default;

                /**
                 * @brief [SWS_CRYPT_20654]
                 * Get a reference to Crypto Provider of this context.
                 * @return CryptoProvider& a reference to Crypto Provider instance that provides this context
                 */
                virtual CryptoProvider& MyProvider () const noexcept=0;

            };
        }
    }
}
#endif // ARA_CRYPTO_CRYP_CYPTO_CONTEXT_H