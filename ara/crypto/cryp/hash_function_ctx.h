#ifndef ARA_CRYPTO_CRYP_HASH_FUNCTION_CTX_H
#define ARA_CRYPTO_CRYP_HASH_FUNCTION_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_21100]
             * Hash function interface.
             */
            class HashFunctionCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_21101]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<HashFunctionCtx>;

                /**
                 * @brief [SWS_CRYPT_21115
                 * Finish the digest calculation and optionally produce the "signature" object. Only after call of this
                 * method the digest can be signed, verified, extracted or compared.
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > output data buffer
                 * @exception CryptoErrorDomain::kProcessingNotStarted if the digest calculation was not initiated by a call of the Start() method
                 * @exception CryptoErrorDomain::kInvalidUsageOrder if the digest calculation has not started yet or not been updated at least once
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > Finish() noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21102]
                 * Get DigestService instance.
                 * @return DigestService::Uptr 
                 */
                virtual DigestService::Uptr GetDigestService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21116]
                 * Get requested part of calculated digest. Entire digest value is kept in the context up to next call
                 * Start(), therefore any its part can be extracted again or verified. If (full_digest_size <= offset)
                 * then return_size = 0 bytes; else return_size = min(output.size(), (full_digest_size - offset))
                 * bytes. This method can be implemented as "inline" after standartization of function
                 * ara::core::memcpy().
                 * @param[in] offset position of the first byte of digest that should be placed to the output buffer
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > number of digest bytes really stored to the output buffer (they are always <= output.size() and denoted below as return_size)
                 * @exception CryptoErrorDomain::kProcessingNotFinished if the digest calculation was not finished by a call of the Finish() method
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > GetDigest (std::size_t offset=0) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21117]
                 * Get requested part of calculated digest to pre-reserved managed container. This method sets
                 * the size of the output container according to actually saved value. Entire digest value is kept in
                 * the context up to next call Start(), therefore any its part can be extracted again or verified. If
                 * (full_digest_size <= offset) then return_size = 0 bytes; else return_size = min(output.capacity(),
                 * (full_digest_size - offset)) bytes
                 * @tparam Alloc a custom allocator type of the output container
                 * @param[in] offset position of first byte of digest that should be placed to the output buffer
                 * @return ara::core::Result<ByteVector<Alloc> > 
                 * @exception CryptoErrorDomain::kProcessingNotFinished if the digest calculation was not finished by a call of the Finish() method
                 * @exception CryptoErrorDomain::kUsageViolation if the buffered digest belongs to a MAC/HMAC/AE/AEAD context initialized by a key without kAllowSignature permission
                 */
//                template <typename Alloc = <implementation-defined>>
//                ara::core::Result<ByteVector<Alloc> > GetDigest (std::size_t offset=0) const noexcept;

                /**
                 * @brief [SWS_CRYPT_21118]
                 * Initialize the context for a new data stream processing or generation (depending on the
                 * primitive) without IV.
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kMissingArgument the configured hash function expected an IV
                 */
                virtual ara::core::Result<void> Start () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21111]
                 * Initialize the context for a new data stream processing or generation (depending on the
                 * primitive). If IV size is greater than maximally supported by the algorithm then an
                 * implementation may use the leading bytes only from the sequence.
                 * @param[in] iv the Initialization Vector (IV) or "nonce" object
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kInvalidInputSize if the size of provided IV is not supported (i.e. if it is not enough for the initialization)
                 * @exception CryptoErrorDomain::kUnsupported if the base algorithm (or its current implementation) principally doesn’t support the IV variation
                 */
                virtual ara::core::Result<void> Start (const SecretSeed &iv) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21112]
                 * Update the digest calculation context by a new part of the message. This method is dedicated
                 * for cases then the RestrictedUseObject is a part of the "message".
                 * @param[in] in a part of input message that should be processed
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kProcessingNotStarted if the digest calculation was not initiated by a call of the Start() method
                 */
                virtual ara::core::Result<void> Update (const RestrictedUseObject &in) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21113]
                 * Update the digest calculation context by a new part of the message.
                 * @param[in] in a part of the input message that should be processed
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kProcessingNotStarted if the digest calculation was not initiated by a call of the Start() method
                 */
                virtual ara::core::Result<void> Update (ReadOnlyMemRegion in) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21114]
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

#endif // ARA_CRYPTO_CRYP_HASH_FUNCTION_CTX_H