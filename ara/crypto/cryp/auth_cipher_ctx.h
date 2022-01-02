#ifndef ARA_CRYPTO_CRYP_AUTH_CIPHER_CTX_H
#define ARA_CRYPTO_CRYP_AUTH_CIPHER_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"
#include "ara/crypto/cryp/digest_service.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_20100]
             * Generalized Authenticated Cipher Context interface. Methods of the derived interface Buffered
             * Digest are used for authentication of associated public data. Methods of the derived interface
             * StreamCipherCtx are used for encryption/decryption and authentication of confidential part of
             * message. The data processing must be executed in following order:
             * Call one of the Start() methods. Process all associated public data via calls of Update()
             * methods. Process the confidential part of the message via calls of ProcessBlocks(), Process
             * Bytes() (and optionally FinishBytes()) methods. Call the Finish() method due to finalize the
             * authentication code calculation (and get it optionally). Copy of the calculated MAC may be
             * extracted (by GetDigest()) or compared internally (by Compare()). Receiver side should not use
             * decrypted data before finishing of the whole decryption and authentication process! I.e.
             * decrypted data can be used only after successful MAC verification!
             */
            class AuthCipherCtx : public CryptoContext 
            {
            private:
                DigestService::Uptr mDigestService;
                bool mProcessingNotStarted;
                std::uint64_t mMaxAssociatedDataSize;
                SymmetricKey mKey;
                CryptoTransform mTransform;

            public:
                /**
                 * @brief [SWS_CRYPT_20319]
                 * Check the calculated digest against an expected "signature" object. Entire digest value is kept
                 * in the context up to next call Start(), therefore it can be verified again or extracted. This method
                 * can be implemented as "inline" after standartization of function ara::core::memcmp().
                 * @param[in] expected the signature object containing an expected digest value
                 * @return ara::core::Result<bool>
                 * @retval true if value and meta-information of the provided "signature" object is identical to calculated digest and current configuration of the context respectively;
                 * @retval false otherwise
                 * @retval CryptoErrorDomain::kProcessingNotFinished if the digest calculation was not finished by a call of the Finish() method
                 * @retval CryptoErrorDomain::kIncompatibleObject if the provided "signature" object was produced by another crypto primitive type
                 */
                virtual ara::core::Result<bool> Check (const Signature &expected) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20102]
                 * Get DigestService instance.
                 * @return DigestService::Uptr 
                 */
                virtual DigestService::Uptr GetDigestService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20316]
                 * Retrieve the calculated digest. The entire digest value is kept in the context until the next call of
                 * Start(). Therefore, the digest can be re-checked or extracted at any time. If the offset is larger
                 * than the digest, an empty buffer shall be returned. This method can be implemented as "inline"
                 * after standardization of function ara::core::memcpy().
                 * @tparam Alloc 
                 * @param[in] offset position of the first byte of digest that should be placed to the output buffer
                 * @return ara::core::Result<ByteVector<Alloc> > 
                 * @retval CryptoErrorDomain::kProcessingNotFinished if the digest calculation was not finished by a call of the Finish() method
                 * @retval CryptoErrorDomain::kUsageViolation if the buffered digest belongs to a MAC/HMAC/AE/AEAD context initialized by a key without kAllowSignature permission
                 */
                template <typename Alloc = <implementation-defined>>
                ara::core::Result<ByteVector<Alloc> > GetDigest (std::size_t offset=0) const noexcept;

                /**
                 * @brief [SWS_CRYPT_21715]
                 * Get the kind of transformation configured for this context: kEncrypt or kDecrypt.
                 * @return ara::core::Result<CryptoTransform> 
                 * @retval CryptoErrorDomain::kUninitializedContext if the transformation direction of this context is configurable during an initialization, but the context was not initialized yet
                 */
                virtual ara::core::Result<CryptoTransform> GetTransformation () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20103]
                 * Get maximal supported size of associated public data.
                 * @return std::uint64_t 
                 */
                virtual std::uint64_t GetMaxAssociatedDataSize () const noexcept=0
                {
                    return mMaxAssociatedDataSize;
                }

                /**
                 * @brief [SWS_CRYPT_23634]
                 * Process confidential data and return result. The input buffer will be overwritten by the
                 * processed message. This function is the final call, i.e. all associated data must have been
                 * already provided. Hence, the function will check the authentication tag and only return the
                 * processed data, if the tag is valid.
                 * @param[in] in the input buffer containing the full message
                 * @param expectedTag optional pointer to read only mem region containing the auth-tag for verification.
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > 
                 * @retval CryptoErrorDomain::kInvalidInputSize if size of the input buffer is not divisible by the block size (see GetBlockSize())
                 * @retval CryptoErrorDomain::kProcessingNotStarted if the data processing was not started by a call of the Start() method
                 * @retval CryptoErrorDomain::kAuthTagNotValid if the processed data cannot be authenticated
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ProcessConfidentialData (ReadOnlyMemRegion in, ara::core::Optional< ReadOnly MemRegion > expectedTag) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23635]
                 * Process confidential data and update the input buffer with the processed message. The input
                 * buffer will be overwritten by the processed message After this method is called no additional
                 * associated data may be updated.
                 * @param[in] inOut the input buffer containing the full message
                 * @param[in] expectedTag optional pointer to read only mem region containing the auth-tag for verification.
                 * @return ara::core::Result<void> 
                 * @retval CryptoErrorDomain::kInvalidInputSize if size of the input buffer is not divisible by the block size (see GetBlockSize())
                 * @retval CryptoErrorDomain::kProcessingNotStarted if the data processing was not started by a call of the Start() method
                 * @retval CryptoErrorDomain::kAuthTagNotValid if the processed data cannot be authenticated
                 */
                virtual ara::core::Result<void> ProcessConfidentialData (ReadWriteMemRegion inOut, ara::core::Optional< ReadOnlyMemRegion > expectedTag) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20414]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23911]
                 * Set (deploy) a key to the authenticated cipher symmetric algorithm context.
                 * @param[in] key the source key object
                 * @param[in] transform the "direction" indicator: deploy the key for encryption (if true) or for decryption (if false)
                 * @return ara::core::Result<void> 
                 * @retval CryptoErrorDomain::kIncompatibleObject if the provided key object is incompatible with this symmetric key context
                 * @retval CryptoErrorDomain::kUsageViolation if the transformation type associated with this
                 * context (taking into account the direction specified
                 * by transform) is prohibited by the "allowed usage"
                 * restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const SymmetricKey &key, CryptoTransform transform=CryptoTransform::kEncrypt) noexcept=0
                {
                    mKey = key;
                    mTransform = transform;
                    /// TODO: Error Handling
                }

                /**
                 * @brief [SWS_CRYPT_24714]
                 * Initialize the context for a new data processing or generation (depending from the primitive). If
                 * IV size is greater than maximally supported by the algorithm then an implementation may use
                 * the leading bytes only from the sequence.
                 * @param[in] iv an optional Initialization Vector (IV) or "nonce" value
                 * @return ara::core::Result<void> 
                 * @retval CryptoErrorDomain::kUninitializedContext if the context was not initialized
                 * @retval CryptoErrorDomain::kInvalidInputSize if the size of provided IV is not supported (i.e. if it is not enough for the initialization)
                 * @retval CryptoErrorDomain::kUnsupported if the base algorithm (or its current implementation) principally doesn’t support the IV variation, but provided IV value is not empty, i.e. if (iv.empty() == false)
                 */
                virtual ara::core::Result<void> Start (ReadOnlyMemRegion iv=ReadOnlyMemRegion()) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24715]
                 * Initialize the context for a new data processing or generation (depending from the primitive). If
                 * IV size is greater than maximally supported by the algorithm then an implementation may use
                 * the leading bytes only from the sequence.
                 * @param[in] iv the Initialization Vector (IV) or "nonce" object
                 * @return ara::core::Result<void> 
                 * @retval CryptoErrorDomain::kUninitializedContext if the context was not initialized
                 * @retval CryptoErrorDomain::kInvalidInputSize if the size of provided IV is not supported (i.e. if it is not enough for the initialization)
                 * @retval CryptoErrorDomain::kUnsupported if the base algorithm (or its current implementation) principally doesn’t support the IV variation, but provided IV value is not empty, i.e. if (iv.empty() == false)
                 * @retval CryptoErrorDomain::kUsageViolation if this transformation type is prohibited by the "allowed usage" restrictions of the provided Secret Seed object
                 */
                virtual ara::core::Result<void> Start (const SecretSeed &iv) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20312]
                 * Update the digest calculation by the specified RestrictedUseObject. This method is dedicated
                 * for cases then the RestrictedUseObject is a part of the "message".
                 * @param[in] in a part of input message that should be processed
                 * @return ara::core::Result<void> 
                 * @retval CryptoErrorDomain::kProcessingNotStarted if the digest calculation was not initiated by a call of the Start() method
                 * @retval CryptoErrorDomain::kInvalidUsageOrder if ProcessConfidentialData has already been called
                 */
                virtual ara::core::Result<void> UpdateAssociatedData (const RestrictedUseObject &in) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20313]
                 * Update the digest calculation by a new chunk of associated data.
                 * @param[in] in a part of the input message that should be processed 
                 * @return ara::core::Result<void> 
                 * @retval CryptoErrorDomain::kProcessingNotStarted if the digest calculation was not initiated by a call of the Start() method
                 * @retval CryptoErrorDomain::kInvalidUsageOrder if ProcessConfidentialData has already been called
                 */
                virtual ara::core::Result<void> UpdateAssociatedData (ReadOnlyMemRegion in) noexcept=0;

                 /**
                 * @brief [SWS_CRYPT_20314]
                 * Update the digest calculation by the specified Byte. This method is convenient for processing of
                 * constant tags.
                 * @param[in] in a byte value that is a part of input message
                 * @return ara::core::Result<void> 
                 * @retval CryptoErrorDomain::kProcessingNotStarted if the digest calculation was not initiated by a call of the Start() method
                 * @retval CryptoErrorDomain::kInvalidUsageOrder if ProcessConfidentialData has already been called
                 */
               virtual ara::core::Result<void> UpdateAssociatedData (std::uint8_t in) noexcept=0;
            };
        }
    }
}
#endif // ARA_CRYPTO_CRYP_AUTH_CIPHER_CTX_H
