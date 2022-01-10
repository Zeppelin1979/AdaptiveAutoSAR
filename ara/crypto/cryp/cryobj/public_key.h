#ifndef ARA_CRYPTO_CRYP_PUBLIC_KEY_H
#define ARA_CRYPTO_CRYP_PUBLIC_KEY_H

#include "ara/crypto/cryp/common/base_id_types.h"
#include "ara/crypto/cryp/cryobj/restricted_use_object.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_22700]
             * General Asymmetric Public Key interface.
             */
            class PublicKey : public RestrictedUseObject
            {
            public:
            
                /**
                 * @brief [SWS_CRYPT_22701]
                 * Unique smart pointer of the interface.
                 */
                using Uptrc = std::unique_ptr<const PublicKey>;
                
                /**
                 * @brief [SWS_CRYPT_22702]
                 * const object type
                 */
                static const CryptoObjectType kObjectType = CryptoObjectType::kPublicKey;

                /**
                 * @brief [SWS_CRYPT_22711]
                 * Check the key for its correctness.
                 * @param[in] strongCheck the severeness flag that indicates type of the required check: strong (if true) or fast (if false)
                 * @return true if the key is correct
                 * @return false otherwise
                 */
                virtual bool CheckKey (bool strongCheck=true) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22511]
                 * Get the public key correspondent to this private key.
                 * @return ara::core::Result<PublicKey::Uptrc> unique smart pointer to the public key correspondent to this private key
                 */
                virtual ara::core::Result<PublicKey::Uptrc> GetPublicKey () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22712]
                 * Calculate hash of the Public Key value. The original public key value BLOB is available via the
                 * Serializable interface.
                 * @param[in] hashFunc a hash-function instance that should be used the hashing
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > a buffer preallocated for the resulting hash value
                 * @exception CryptoErrorDomain::kInsufficientCapacity if size of the hash buffer is not enough for storing of the result
                 * @exception CryptoErrorDomain::kIncompleteArgState if the hashFunc context is not initialized
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > HashPublicKey (HashFunctionCtx &hashFunc) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22713]
                 * Calculate hash of the Public Key value. This method sets the size of the output container
                 * according to actually saved value! The original public key value BLOB is available via the
                 * Serializable interface.
                 * @tparam Alloc a custom allocator type of the output container
                 * @param[in] hashFunc a hash-function instance that should be used the hashing
                 * @return ara::core::Result<ByteVector<Alloc> > pre-reserved managed container for the resulting hash value
                 * @exception CryptoErrorDomain::kInsufficientCapacity if size of the hash buffer is not enough for storing of the result
                 * @exception CryptoErrorDomain::kIncompleteArgState if the hashFunc context is not initialized
                 */
//                template <typename Alloc = <implementation-defined>>
//                ara::core::Result<ByteVector<Alloc> > HashPublicKey (HashFunctionCtx &hashFunc) const noexcept;

            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_PUBLIC_KEY_H