#ifndef ARA_CRYPTO_CRYP_EXTENSION_SERVICE_H
#define ARA_CRYPTO_CRYP_EXTENSION_SERVICE_H

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_29040]
             * Basic meta-information service for all contexts.
             */
            class ExtensionService
            {
            public:

                /**
                 * @brief [SWS_CRYPT_29042]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<ExtensionService>;

                /**
                 * @brief [SWS_CRYPT_29041]
                 * Destroy the Extension Service object
                 * 
                 */
                virtual ~ExtensionService () noexcept=default;

                /**
                 * @brief [SWS_CRYPT_29045]
                 * Get actual bit-length of a key loaded to the context. If no key was set to the context yet then 0 is
                 * returned.
                 * @return std::size_t 
                 */
                virtual std::size_t GetActualKeyBitLength () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29047]
                 * Get the COUID of the key deployed to the context this extension service is attached to. If no key
                 * was set to the context yet then an empty COUID (Nil) is returned.
                 * @return CryptoObjectUid the COUID of the CryptoObject
                 */
                virtual CryptoObjectUid GetActualKeyCOUID () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29046]
                 * Get allowed usages of this context (according to the key object attributes loaded to this context).
                 * If the context is not initialized by a key object yet then zero (all flags are reset) must be returned.
                 * @return AllowedUsageFlags a combination of bit-flags that specifies allowed usages of the context
                 */
                virtual AllowedUsageFlags GetAllowedUsage () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29044]
                 * Get maximal supported key length in bits.
                 * @return std::size_t maximal supported length of the key in bits
                 */
                virtual std::size_t GetMaxKeyBitLength () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29043]
                 * Get minimal supported key length in bits.
                 * @return std::size_t minimal supported length of the key in bits
                 */
                virtual std::size_t GetMinKeyBitLength () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29048]
                 * Verify supportness of specific key length by the context.
                 * @param keyBitLength length of the key in bits
                 * @return true if provided value of the key length is supported by the context
                 * @return false otherwise
                 */
                virtual bool IsKeyBitLengthSupported (std::size_t keyBitLength) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29049]
                 * Check if a key has been set to this context.
                 * @return true otherwise
                 * @return false if no key has been set
                 */
                virtual bool IsKeyAvailable () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30218]
                 * Copy-assign another ExtensionService to this instance.
                 * @param other the other instance
                 * @return ExtensionService& *this, containing the contents of other
                 */
                ExtensionService& operator= (const ExtensionService &other)=default;

                /**
                 * @brief [SWS_CRYPT_30218]
                 * Move-assign another ExtensionService to this instance.
                 * @param other the other instance
                 * @return ExtensionService& *this, containing the contents of other
                 */
                ExtensionService& operator= (const ExtensionService &&other)/*=default*/;

            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_EXTENSION_SERVICE_H