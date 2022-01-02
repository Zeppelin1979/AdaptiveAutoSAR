#ifndef ARA_CRYPTO_CRYP_CYPTO_CONTEXT_H
#define ARA_CRYPTO_CRYP_CYPTO_CONTEXT_H

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
            };
        }
    }
}
#endif // ARA_CRYPTO_CRYP_CYPTO_CONTEXT_H