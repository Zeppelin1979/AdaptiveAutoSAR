#ifndef ARA_CRYPTO_CRYP_MESSAGE_AUTHN_CODE_CTX_H
#define ARA_CRYPTO_CRYP_MESSAGE_AUTHN_CODE_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_22100]
             * Keyed Message Authentication Code Context interface definition (MAC/HMAC).
             */
            class MessageAuthnCodeCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_22101]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<MessageAuthnCodeCtx>;

                /**
                 * @brief [SWS_CRYPT_22119]
                 * Check the calculated digest against an expected "signature" object. Entire digest value is kept
                 * in the context up to next call Start(), therefore it can be verified again or extracted. This method
                 * can be implemented as "inline" after standartization of function ara::core::memcmp().
                 * @param[in] expected the signature object containing an expected digest value
                 * @return ara::core::Result<bool> true if value and meta-information of the provided
                 * "signature" object is identical to calculated digest and current configuration of the context respectively;
                 * but false otherwise
                 * @exception CryptoErrorDomain::kProcessingNotFinished if the digest calculation was not finished by a call of the Finish() method
                 * @exception CryptoErrorDomain::kIncompatibleObject if the provided "signature" object was produced by another crypto primitive type
                 */
                virtual ara::core::Result<bool> Check (const Signature &expected) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22115]
                 * Finish the digest calculation and optionally produce the "signature" object. Only after call of this
                 * method the digest can be signed, verified, extracted or compared! If the signature object
                 * produced by a keyed MAC/HMAC/AE/AEAD algorithm then the dependence COUID of the
                 * "signature" should be set to COUID of used symmetric key.
                 * @param[in] makeSignatureObject if this argument is true then the method will also produce the signature object
                 * @return ara::core::Result<Signature::Uptrc> unique smart pointer to created signature object, if (makeSignatureObject == true) or nullptr if (make SignatureObject == false)
                 * @exception CryptoErrorDomain::kProcessingNotStarted if the digest calculation was not initiated by a call of the Start() method
                 * @exception CryptoErrorDomain::kUsageViolation if the buffered digest belongs to a MAC/HMAC/AE/AEAD context initialized by a key without kAllow Signature permission, but (makeSignatureObject == true)
                 */
                virtual ara::core::Result<Signature::Uptrc> Finish (bool makeSignatureObject=false) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22102]
                 * Get DigestService instance.
                 * @return DigestService::Uptr 
                 */
                virtual DigestService::Uptr GetDigestService () const noexcept=0;
                
                /**
                 * @brief [SWS_CRYPT_22116]
                 * Get requested part of calculated digest to existing memory buffer. Entire digest value is kept in
                 * the context up to next call Start(), therefore any its part can be extracted again or verified. If
                 * (full_digest_size <= offset) then return_size = 0 bytes; else return_size = min(output.size(),
                 * (full_digest_size - offset)) bytes. This method can be implemented as "inline" after
                 * standartization of function ara::core::memcpy().
                 * @param[in] offset position of the first byte of digest that should be placed to the output buffer
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > number of digest bytes really stored to the output
                 * buffer (they are always <= output.size() and denoted below as return_size)
                 * @exception CryptoErrorDomain::kProcessingNotFinished if the digest calculation was not finished by a call of the Finish() method
                 * @exception CryptoErrorDomain::kUsageViolation if the buffered digest belongs to a MAC/HMAC/AE/AEAD context initialized by a key without kAllowSignature permission
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > GetDigest (std::size_t offset=0) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22117]
                 * Get requested part of calculated digest to pre-reserved managed container. This method sets
                 * the size of the output container according to actually saved value. Entire digest value is kept in
                 * the context up to next call Start(), therefore any its part can be extracted again or verified. If
                 * (full_digest_size <= offset) then return_size = 0 bytes; else return_size = min(output.capacity(),
                 * (full_digest_size - offset)) bytes.
                 * @tparam Alloc a custom allocator type of the output container
                 * @param[in] offset position of first byte of digest that should be placed to the output buffer
                 * @return ara::core::Result<ByteVector<Alloc> > 
                 * @exception CryptoErrorDomain::kProcessingNotFinished if the digest calculation was not finished by a call of the Finish() method
                 * @exception CryptoErrorDomain::kUsageViolation if the buffered digest belongs to a MAC/HMAC/AE/AEAD context initialized by a key without kAllowSignature permission
                 */
//                template <typename Alloc = <implementation-defined>>
//                ara::core::Result<ByteVector<Alloc> > GetDigest (std::size_t offset=0) const noexcept;

                /**
                 * @brief [SWS_CRYPT_22120]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22118]
                 * Set (deploy) a key to the message authn code algorithm context.
                 * @param key the source key object
                 * @param transform the "direction" indicator: deploy the key for direct transformation (if true) or for reverse one (if false)
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kIncompatibleObject if the provided key object is incompatible with this symmetric key context
                 * @exception CryptoErrorDomain::kUsageViolation if the transformation type associated with this context (taking into account the direction specified by transform) is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const SymmetricKey &key, CryptoTransform transform=CryptoTransform::kMacGenerate) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22110]
                 * Initialize the context for a new data stream processing or generation (depending from the
                 * primitive). If IV size is greater than maximally supported by the algorithm then an
                 * implementation may use the leading bytes only from the sequence.
                 * @param iv an optional Initialization Vector (IV) or "nonce" value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by deploying a key
                 * @exception CryptoErrorDomain::kInvalidInputSize if the size of provided IV is not supported (i.e. if it is not enough for the initialization)
                 * @exception CryptoErrorDomain::kUnsupported if the base algorithm (or its current implementation) principally doesn’t support the IV variation, but provided IV value is not empty, i.e. if (iv.empty() == false)
                 */
                virtual ara::core::Result<void> Start (ReadOnlyMemRegion iv=ReadOnlyMemRegion()) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22111]
                 * Initialize the context for a new data stream processing or generation (depending from the
                 * primitive). If IV size is greater than maximally supported by the algorithm then an
                 * implementation may use the leading bytes only from the sequence.
                 * @param iv the Initialization Vector (IV) or "nonce" object
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by deploying a key
                 * @exception CryptoErrorDomain::kInvalidInputSize if the size of provided IV is not supported (i.e. if it is not enough for the initialization)
                 * @exception CryptoErrorDomain::kUnsupported if the base algorithm (or its current implementation) principally doesn’t support the IV variation, but provided IV value is not empty, i.e. if (iv.empty() == false)
                 * @exception CryptoErrorDomain::kUsageViolation if this transformation type is prohibited by the "allowed usage" restrictions of the provided Secret Seed object
                 */
                virtual ara::core::Result<void> Start (const SecretSeed &iv) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22112]
                 * Update the digest calculation context by a new part of the message. This method is dedicated
                 * for cases then the RestrictedUseObject is a part of the "message".
                 * @param[in] in a part of input message that should be processed
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kProcessingNotStarted if the digest calculation was not initiated by a call of the Start() method
                 */
                virtual ara::core::Result<void> Update (const RestrictedUseObject &in) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22113]
                 * Update the digest calculation context by a new part of the message.
                 * @param[in] in a part of the input message that should be processed
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kProcessingNotStarted if the digest calculation was not initiated by a call of the Start() method
                 */
                virtual ara::core::Result<void> Update (ReadOnlyMemRegion in) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22114]
                 * Update the digest calculation context by a new part of the message. This method is convenient
                 * for processing of constant tags.
                 * @param[in] in a byte value that is a part of input message
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kProcessingNotStarted if the digest calculation was not initiated by a call of the Start() method
                 */
                virtual ara::core::Result<void> Update (std::uint8_t in) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_MESSAGE_AUTHN_CODE_CTX_H