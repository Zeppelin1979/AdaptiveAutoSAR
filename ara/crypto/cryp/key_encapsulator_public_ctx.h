#ifndef ARA_CRYPTO_CRYP_KEY_ENCAPSULATOR_PUBLIC_CTX_H
#define ARA_CRYPTO_CRYP_KEY_ENCAPSULATOR_PUBLIC_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_21800]
             * Asymmetric Key Encapsulation Mechanism (KEM) Public key Context interface.
             */
            class KeyEncapsulatorPublicCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_21801]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<KeyEncapsulatorPublicCtx>;

                /**
                 * @brief [SWS_CRYPT_21818]
                 * Get fixed size of the encapsulated data block.
                 * @return std::size_t size of the encapsulated data block in bytes
                 */
                virtual std::size_t GetEncapsulatedSize () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21802]
                 * Get ExtensionService instance.
                 * @return ExtensionService::Uptr 
                 */
                virtual ExtensionService::Uptr GetExtensionService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21817]
                 * Get entropy (bit-length) of the key encryption key (KEK) material. For RSA system the returned
                 * value corresponds to the length of module N (minus 1). For DH-like system the returned value
                 * corresponds to the length of module q (minus 1).
                 * @return std::size_t entropy of the KEK material in bits
                 */
                virtual std::size_t GetKekEntropy () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21810]
                 * Add the content to be encapsulated (payload) according to RFC 5990 ("keying data"). At the
                 * moment only SymmetricKey and SecretSeed objects are supported.
                 * @param[in] keyingData the payload to be protected
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrc::kUsageViolation if the keyingData cannot be exported due to CryptoObject::IsExportable() returning FALSE
                 * @exception CryptoErrc::kIncompatibleObject if the keyingData belongs to a different CryptoProvider
                 * @exception CryptoErrc::kInvalidInputSize if this context does not support the size of the keying Data
                 */
                virtual ara::core::Result<void> AddKeyingData (const RestrictedUseObject &keyingData) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21813]
                 * Encapsulate the last set keying-data.
                 * @param kdf[in] a context of a key derivation function, which should be used for the target KEK production
                 * @param kekAlgId[in] an algorithm ID of the target KEK
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > the encapsulated data as a byte-vector
                 * @exception CryptoErrc::kUninitializedContext if the context was not initialized by a public key value
                 * @exception CryptoErrc::kInvalidArgument if kekAlgId or kdf are incompatible with this context
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > Encapsulate (KeyDerivationFunctionCtx &kdf, CryptoAlgId kekAlgId) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21816]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21815]
                 * Set (deploy) a key to the key encapsulator public algorithm context.
                 * @param[in] key the source key object
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrc::kIncompatibleObject if the provided key object is incompatible with this symmetric key context
                 * @exception CryptoErrc::kUsageViolation if the transformation type associated with this context is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const PublicKey &key) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_KEY_ENCAPSULATOR_PUBLIC_CTX_H