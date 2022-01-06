#ifndef ARA_CRYPTO_X509_X509_PUBLIC_KEY_INFO_H
#define ARA_CRYPTO_X509_X509_PUBLIC_KEY_INFO_H

#include "ara/core/result.h"

#include "ara/crypto/cryp/common/serializable.h"

#include "ara/crypto/cryp/cryobj/public_key.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_24400]
             * X.509 Public Key Information interface.
             */
            class X509PublicKeyInfo : public Serializable
            {
            public:

                /**
                 * @brief [SWS_CRYPT_24401]
                 * Unique smart pointer of the interface.
                 */
                using Uptrc = std::unique_ptr<const X509PublicKeyInfo>;

                /**
                 * @brief [SWS_CRYPT_24414]
                 * Get public key object of the subject. Created PublicKey object is session and non-exportable,
                 * because generic X.509 certificate or certificate signing request (CSR) doesn’t have COUID of
                 * the public key, therefore it should be saved or transmitted only as a part of correspondent
                 * certificate or CSR.
                 * @return ara::core::Result<ara::crypto::cryp::PublicKey::Uptrc> unique smart pointer to the created public key of the subject
                 */
                virtual ara::core::Result<ara::crypto::cryp::PublicKey::Uptrc> GetPublicKey () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24412]
                 * Get an ID of hash algorithm required by current signature algorithm.
                 * @return CryptoAlgId required hash algorithm ID or kAlgIdAny if the
                 * signature algorithm specification does not include a concrete hash function
                 */
                virtual CryptoAlgId GetRequiredHashAlgId () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24411]
                 * Get the hash size required by current signature algorithm.
                 * @return std::size_t required hash size in bytes
                 */
                virtual std::size_t GetRequiredHashSize () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24413]
                 * Get size of the signature value produced and required by the current algorithm.
                 * @return std::size_t size of the signature value in bytes
                 */
                virtual std::size_t GetSignatureSize () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24410]
                 * Get the CryptoPrimitiveId instance of this class.
                 * @return ara::crypto::cryp::CryptoPrimitiveId::Uptrc 
                 */
                virtual ara::crypto::cryp::CryptoPrimitiveId::Uptrc GetAlgorithmId()=0;

                /**
                 * @brief [SWS_CRYPT_24415]
                 * Verify the sameness of the provided and kept public keys. This method compare the public key
                 * values only.
                 * @param[in] publicKey the public key object for comparison
                 * @return true if values of the stored public key and object provided by the argument are identical
                 * @return false otherwise
                 */
                virtual bool IsSameKey (const ara::crypto::cryp::PublicKey &publicKey) const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_X509_PUBLIC_KEY_INFO_H