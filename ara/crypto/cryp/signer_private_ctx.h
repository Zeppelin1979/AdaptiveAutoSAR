#ifndef ARA_CRYPTO_CRYP_SIGNER_PRIVATE_CTX_H
#define ARA_CRYPTO_CRYP_SIGNER_PRIVATE_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23500]
             * Signature Private key Context interface.
             */
            class SignerPrivateCtx : public CryptoContext
            {
            public:
                
                /**
                 * @brief [SWS_CRYPT_23501]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<SignerPrivateCtx>;

                /**
                 * @brief [SWS_CRYPT_23510]
                 * Get SignatureService instance.
                 * @return SignatureService::Uptr 
                 */
                virtual SignatureService::Uptr GetSignatureService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23516]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23515]
                 * Set (deploy) a key to the signer private algorithm context.
                 * @param[in] key the source key object
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrc::kIncompatibleObject if the provided key object is incompatible with this symmetric key context
                 * @exception CryptoErrc::kUsageViolation if the transformation type associated with this context is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const PrivateKey &key) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23511]
                 * Sign a provided digest value stored in the hash-function context. This method must put the
                 * hash-function algorithm ID and a COUID of the used key-pair to the resulting signature object!
                 * The user supplied context may be used for such algorithms as: Ed25519ctx, Ed25519ph,
                 * Ed448ph. If the target algorithm doesn’t support the context argument then the empty (default)
                 * value must be supplied!
                 * @param[in] hashFn a finalized hash-function context that contains a digest value ready for sign
                 * @param[in] context an optional user supplied "context" (its support depends from concrete algorithm)
                 * @return ara::core::Result<Signature::Uptrc> unique smart pointer to serialized signature
                 * @exception CryptoErrorDomain::kInvalidArgument if hash-function algorithm does not comply with the signature algorithm specification of this context
                 * @exception CryptoErrorDomain::kInvalidInputSize if the user supplied context has incorrect (or unsupported) size
                 * @exception CryptoErrorDomain::kProcessingNotFinished if the method hash.Finish() was not called before the call of this method
                 * @exception CryptoErrorDomain::kUninitializedContext this context was not initialized by a key value
                 */
                virtual ara::core::Result<Signature::Uptrc> SignPreHashed (const HashFunctionCtx &hashFn, ReadOnlyMemRegion context=ReadOnlyMemRegion()) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23512]
                 * Sign a directly provided hash or message value. This method can be used for implementation
                 * of the "multiple passes" signature algorithms that process a message directly, i.e. without
                 * "pre-hashing" (like Ed25519ctx). But also this method is suitable for implementation of the
                 * traditional signature schemes with pre-hashing (like Ed25519ph, Ed448ph, ECDSA). If the
                 * target algorithm doesn’t support the context argument then the empty (default) value must be
                 * supplied!
                 * @param[in] value the (pre-)hashed or direct message value that should be signed
                 * @param[in] context an optional user supplied "context" (its support depends from concrete algorithm)
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > actual size of the signature value stored to the output buffer
                 * @exception CryptoErrorDomain::kInvalidInputSize if size of the input value or context arguments are incorrect / unsupported
                 * @exception CryptoErrorDomain::kUninitializedContext this context was not initialized by a key value
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > Sign (ReadOnlyMemRegion value, ReadOnlyMemRegion context=ReadOnlyMemRegion()) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23513]
                 * Sign a directly provided digest value and create the Signature object. This method must put the
                 * hash-function algorithm ID and a COUID of the used key-pair to the resulting signature object!
                 * The user supplied context may be used for such algorithms as: Ed25519ctx, Ed25519ph,
                 * Ed448ph. If the target algorithm doesn’t support the context argument then the empty (default)
                 * value must be supplied!
                 * @param[in] hashAlgId hash function algorithm ID
                 * @param[in] hashValue hash function value (resulting digest without any truncations)
                 * @param[in] context an optional user supplied "context" (its support depends from concrete algorithm)
                 * @return ara::core::Result<Signature::Uptrc> unique smart pointer to serialized signature
                 * @exception CryptoErrorDomain::kInvalidArgument if hash-function algorithm does not comply with the signature algorithm specification of this context
                 * @exception CryptoErrorDomain::kInvalidInputSize if the user supplied context has incorrect (or unsupported) size
                 * @exception CryptoErrorDomain::kUninitializedContext this context was not initialized by a key value
                 */
                virtual ara::core::Result<Signature::Uptrc> SignPreHashed (AlgId hashAlgId, ReadOnlyMemRegion hashValue, ReadOnlyMemRegion context=ReadOnlyMemRegion()) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23514]
                 * Sign a directly provided hash or message value. This method can be used for implementation
                 * of the "multiple passes" signature algorithms that process a message directly, i.e. without
                 * "pre-hashing" (like Ed25519ctx). But also this method is suitable for implementation of the
                 * traditional signature schemes with pre-hashing (like Ed25519ph, Ed448ph, ECDSA). This
                 * method sets the size of the output container according to actually saved value! If the target
                 * algorithm doesn’t support the context argument then the empty (default) value must be
                 * supplied!
                 * @tparam Alloc a custom allocator type of the output container
                 * @param[in] value the (pre-)hashed or direct message value that should be signed
                 * @param[in] context an optional user supplied "context" (its support depends from concrete algorithm)
                 * @return ara::core::Result<ByteVector<Alloc> > 
                 * @exception CryptoErrorDomain::kInvalidInputSize if size of the input value or context arguments are incorrect / unsupported
                 * @exception CryptoErrorDomain::kInsufficientCapacity if capacity of the output signature container is not enough
                 * @exception CryptoErrorDomain::kUninitializedContext this context was not initialized by a key value
                 */
//                template <typename Alloc = <implementation-defined>>
//                ara::core::Result<ByteVector<Alloc> > Sign (ReadOnlyMemRegion value, ReadOnlyMemRegion context=ReadOnlyMemRegion()) const noexcept;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SIGNER_PRIVATE_CTX_H