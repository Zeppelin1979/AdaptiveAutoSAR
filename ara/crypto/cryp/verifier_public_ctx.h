#ifndef ARA_CRYPTO_CRYP_VERIFIER_PUBLIC_CTX_H
#define ARA_CRYPTO_CRYP_VERIFIER_PUBLIC_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_24100]
             * Signature Verification Public key Context interface.
             */
            class VerifierPublicCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_24101]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<VerifierPublicCtx>;

                /**
                 * @brief [SWS_CRYPT_24115]
                 * Set (deploy) a key to the verifier public algorithm context.
                 * @param key the source key object
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrc::kIncompatibleObject if the provided key object is incompatible with this symmetric key context
                 * @exception CryptoErrc::kUsageViolation if the transformation type associated with this context is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const PublicKey &key) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24116]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24102]
                 * Extension service member class.
                 * @return SignatureService::Uptr 
                 */
                virtual SignatureService::Uptr GetSignatureService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24112]
                 * Verify signature BLOB by a directly provided hash or message value. This method can be used
                 * for implementation of the "multiple passes" signature algorithms that process a message
                 * directly, i.e. without "pre-hashing" (like Ed25519ctx). But also this method is suitable for
                 * implementation of the traditional signature schemes with pre-hashing (like Ed25519ph,
                 * Ed448ph, ECDSA). If the target algorithm doesn’t support the context argument then the empty
                 * (default) value must be supplied! The user supplied context may be used for such algorithms
                 * as: Ed25519ctx, Ed25519ph, Ed448ph.
                 * @param[in] value the (pre-)hashed or direct message value that should be verified
                 * @param[in] signature the signature BLOB for the verification (the BLOB contains a plain sequence of the digital signature components located in fixed/maximum length fields defined by the algorithm specification, and each component is presented by a raw bytes sequence padded by zeroes to full length of the field; e.g. in case of (EC)DSA-256 (i.e. length of the q module is 256 bits) the signature BLOB must have two fixed-size fields: 32 + 32 bytes, for R and S components respectively, i.e. total BLOB size is 64 bytes)
                 * @param[in] context an optional user supplied "context" (its support depends from concrete algorithm)
                 * @return ara::core::Result<bool> 
                 */
                virtual ara::core::Result<bool> Verify (ReadOnlyMemRegion value, ReadOnlyMemRegion signature, ReadOnlyMemRegion context=ReadOnlyMemRegion()) const noexcept=0;
                
                /**
                 * @brief [SWS_CRYPT_24113]
                 * Verify signature by a digest value stored in the hash-function context. This is a pass-through
                 * interface to SWS_CRYPT_24112 for developer convenience, i.e. it adds additional input checks
                 * and then calls the default verify() interface.
                 * @param[in] hashFn hash function to be used for hashing
                 * @param[in] signature the signature object for the verification
                 * @param[in] context an optional user supplied "context" (its support depends from concrete algorithm)
                 * @return ara::core::Result<bool> 
                 * @retval true if the signature was verified successfully
                 * @retval false otherwise
                 * @exception CryptoErrc::kIncompatibleObject if the CryptoAlgId of this context does not match the CryptoAlgId of signature; or the required CryptoAlg Id of the hash is not kAlgIdDefault and the required hash CryptoAlgId of this context does not match hashAlgId or the hash CryptoAlgId of signature
                 * @exception CryptoErrc::kIncompatibleArguments if the provided hashAlgId is not kAlgIdDefault and the CryptoAlgId of the provided signature object does not match the provided hashAlgId
                 * @exception CryptoErrc::kBadObjectReference if the provided signature object does not reference the public key loaded to the context, i.e. if the COUID of the public key in the context is not equal to the COUID referenced from the signature object.
                 * @exception CryptoErrc::kInvalidInputSize if the size of the supplied context or hashValue is incompatible with the configured signature algorithm.
                 */
                virtual ara::core::Result<bool> VerifyPrehashed (const HashFunctionCtx &hashFn, const Signature &signature, ReadOnlyMemRegion context=ReadOnlyMemRegion()) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24114]
                 * Verify signature by a digest value stored in the hash-function context. This is a pass-through
                 * interface to SWS_CRYPT_24112 for developer convenience, i.e. it adds additional input checks
                 * and then calls the default verify() interface.
                 * @param[in] hashFn hash function to be used for hashing
                 * @param[in] signature the data BLOB to be verified
                 * @param[in] context an optional user supplied "context" (its support depends from concrete algorithm)
                 * @return ara::core::Result<bool> 
                 * @retval true if the signature was verified successfully
                 * @retval false otherwise
                 * @exception CryptoErrc::kProcessingNotFinished if the method hashFn.Finish() was not called before this method call
                 * @exception CryptoErrc::kInvalidArgument if the CryptoAlgId of hashFn differs from the Crypto AlgId of this context
                 * @exception CryptoErrc::kInvalidInputSize if the size of the supplied context or signature is incompatible with the configured signature algorithm.
                 */
                virtual ara::core::Result<bool> VerifyPrehashed (const HashFunctionCtx &hashFn, ReadOnlyMemRegion signature, ReadOnlyMemRegion context=ReadOnlyMemRegion()) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24111]
                 * Verify signature by a digest value stored in the hash-function context. This is a pass-through
                 * interface to SWS_CRYPT_24113 for developer convenience, i.e. it adds additional input checks
                 * and then calls the verify() interface from SWS_CRYPT_24113.
                 * @param hashAlgId hash function algorithm ID
                 * @param hashValue hash function value (resulting digest without any truncations)
                 * @param signature the signature object for verification
                 * @param context an optional user supplied "context" (its support depends from concrete algorithm)
                 * @return ara::core::Result<bool> 
                 * @retval true if the signature was verified successfully
                 * @retval false otherwise
                 * @exception CryptoErrc::kProcessingNotFinished if the method hashFn.Finish() was not called before this method call
                 * @exception CryptoErrc::kInvalidArgument if the CryptoAlgId of hashFn differs from the Crypto AlgId of this context
                 * @exception CryptoErrc::kInvalidInputSize if the size of the supplied context or signature is incompatible with the configured signature algorithm.
                */
                virtual ara::core::Result<bool> VerifyPrehashed (CryptoAlgId hashAlgId, ReadOnlyMemRegion hashValue, const Signature &signature, ReadOnlyMemRegion context=ReadOnlyMemRegion()) const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_VERIFIER_PUBLIC_CTX_H