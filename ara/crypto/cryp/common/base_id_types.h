#ifndef ARA_CRYPTO_CRYP_COMMON_BASE_ID_TYPES_H
#define ARA_CRYPTO_CRYP_COMMON_BASE_ID_TYPES_H

#include "ara/core/vector.h"
#include <cinttypes>

namespace ara
{
    namespace crypto
    {
        /**
         * @brief [SWS_CRYPT_10015]
         * A container type and constant bit-flags of allowed usages of a key or a secret seed object. Only
         * directly specified usages of a key are allowed, all other are prohibited! Similar set of flags are
         * defined for the usage restrictions of original key/seed and for a symmetric key or seed that
         * potentially can be derived from the original one. A symmetric key or secret seed can be derived
         * from the original one, only if it supports kAllowKeyAgreement or kAllowKeyDiversify or kAllow
         * KeyDerivation!
         */
        using AllowedUsageFlags = std::uint32_t;

        /**
         * @brief [SWS_CRYPT_10042]
         * Alias of a bytes’ vector template with customizable allocator.
         */
        using ByteVector = ara::core::Vector<std::uint8_t>;

        /**
         * @brief [SWS_CRYPT_10014]
         * Container type of the Crypto Algorithm Identifier.
         */
        using CryptoAlgId = std::uint64_t;

        /**
         * @brief [SWS_CRYPT_10016]
         * Enumeration of all types of crypto objects, i.e. types of content that can be stored to a key slot.
         */
        enum class CryptoObjectType : std::uint32_t
        {
            kUndefined= 0,      // Object type is currently not defined (empty container)
            kSymmetricKey= 1,   // cryp::SymmetricKey object
            kPrivateKey= 2,     // cryp::PrivateKey object
            kPublicKey= 3,      // cryp::PublicKey object
            kSignature= 4,      // cryp::Signature object (asymmetric digital signature or symmetric MAC/HMAC or hash digest)
            kSecretSeed= 5      // cryp::SecretSeed object. Note: the seed cannot have an associated crypto algorithm!
        };

        /**
         * @brief [SWS_CRYPT_10017]
         * Enumeration of all known Provider types.
         */
        enum class ProviderType : std::uint32_t
        {
            kUndefinedProvider= 0,  // Undefined/Unknown Provider type (or applicable for the whole Crypto Stack)
            kCryptoProvider= 1,     // Cryptography Provider.
            kKeyStorageProvider= 2, // Key Storage Provider.
            kX509Provider= 3        // X.509 Provider.
        };

        /**
         * @brief [SWS_CRYPT_10018]
         * Enumeration of key-slot types; currently only machine and applicaiton key-slots are defined.
         */
        enum class KeySlotType : std::uint32_t
        {
            kMachine= 1,            // machine type key-slot - can be managed by application
            kApplication= 2         // application exclusive type key-slot
        };

        /**
         * @brief [SWS_CRYPT_10019]
         * Enumeration of cryptographic transformations.
         */
        enum class CryptoTransform : std::uint32_t
        {
            kEncrypt= 1,            // encryption
            kDecrypt= 2,            // decryption
            kMacVerify= 3,          // MAC verification
            kMacGenerate= 4,        // MAC generation
            kWrap= 5,               // key wrapping
            kUnwrap= 6,             // key unwrapping
            kSigVerify= 7,          // signature verification
            kSigGenerate= 8         // signature generation
        };

        /**
         * @brief [SWS_CRYPT_13104]
         * The key/seed can be used for digital signature or MAC/HMAC verification (applicable to
         * symmetric and asymmetric algorithms).
         */
        const AllowedUsageFlags kAllowVerification = 0x0008;
        
        /**
         * @brief [SWS_CRYPT_13103]
         * The key/seed can be used for digital signature or MAC/HMAC production (applicable to
         * symmetric and asymmetric algorithms).
         */
        const AllowedUsageFlags kAllowSignature = 0x0004;

        /**
         * @brief [SWS_CRYPT_13107]
         * The seed or symmetric key can be used for seeding of a RandomGeneratorCtx.
         */
        const AllowedUsageFlags kAllowRngInit = 0x0040;

        /**
         * @brief [SWS_CRYPT_13100]
         * This group contains list of constant 1-bit values predefined for Allowed Usage flags.
         * The key/seed usage will be fully specified by a key slot prototype (the object can be used only
         * after reloading from the slot).
         */
        const AllowedUsageFlags kAllowPrototypedOnly = 0;

        /**
         * @brief [SWS_CRYPT_13110]
         * The key can be used as "transport" one for Key-Unwrap or Decapsulate transformations
         * (applicable to symmetric and asymmetric keys).
         */
        const AllowedUsageFlags kAllowKeyImporting = 0x0200;

        /**
         * @brief [SWS_CRYPT_13109]
         * The key can be used as "transport" one for Key-Wrap or Encapsulate transformations
         * (applicable to symmetric and asymmetric keys).
         */
        const AllowedUsageFlags kAllowKeyExporting = 0x0100;

        /**
         * @brief [SWS_CRYPT_13106]
         * The seed or symmetric key can be used for slave-keys diversification.
         */
        const AllowedUsageFlags kAllowKeyDiversify = 0x0020;

        /**
         * @brief [SWS_CRYPT_13105]
         * The seed or asymmetric key can be used for key-agreement protocol execution.
         */
        const AllowedUsageFlags kAllowKeyAgreement = 0x0010;

        /**
         * @brief [SWS_CRYPT_13108]
         * The object can be used as an input key material to KDF. The seed or symmetric key can be
         * used as a RestrictedUseObject for slave-keys derivation via a Key Derivation Function (KDF).
         */
        const AllowedUsageFlags kAllowKdfMaterial = 0x0080;

        /**
         * @brief [SWS_CRYPT_13111]
         * The key can be used only for the mode directly specified by Key::AlgId
         */
        const AllowedUsageFlags kAllowExactModeOnly = 0x8000;

        /**
         * @brief [SWS_CRYPT_13115]
         * A derived seed or symmetric key can be used for MAC/HMAC verification.
         */
        const AllowedUsageFlags kAllowDerivedVerification = kAllowVerification << 16;

        /**
         * @brief [SWS_CRYPT_13114]
         * A derived seed or symmetric key can be used for MAC/HMAC production.
         */
        const AllowedUsageFlags kAllowDerivedSignature = kAllowSignature << 16;

        /**
         * @brief [SWS_CRYPT_13120]
         * A derived seed or symmetric key can be used as a "transport" one for Key-Unwrap
         * transformation.
         */
        const AllowedUsageFlags kAllowDerivedKeyImporting = kAllowKeyImporting << 16;

        /**
         * @brief [SWS_CRYPT_13119]
         * A derived seed or symmetric key can be used as a "transport" one for Key-Wrap transformation.
         */
        const AllowedUsageFlags kAllowDerivedKeyExporting = kAllowKeyExporting << 16;

        /**
         * @brief [SWS_CRYPT_13116]
         * A derived seed or symmetric key can be used for slave-keys diversification.
         */
        const AllowedUsageFlags kAllowDerivedKeyDiversify = kAllowKeyDiversify << 16;

        /**
         * @brief [SWS_CRYPT_13122]
         * Allow usage of the object as a key material for KDF and any usage of derived objects. The
         * seed or symmetric key can be used as a RestrictedUseObject for a Key Derivation Function
         * (KDF) and the derived "slave" keys can be used without limitations.
         */
        const AllowedUsageFlags kAllowKdfMaterialAnyUsage = kAllowKdfMaterial | kAllowDerivedDataEncryption | kAllowDerivedDataDecryption | kAllowDerivedSignature | kAllowDerivedVerification | kAllowDerivedKeyDiversify | kAllowDerivedRngInit | kAllowDerivedKdfMaterial | kAllowDerivedKeyExporting | kAllowDerivedKeyImporting;

        /**
         * @brief [SWS_CRYPT_13118]
         * A derived seed or symmetric key can be used as a RestrictedUseObject for slave-keys
         * derivation via a Key Derivation Function (KDF).
         */
        const AllowedUsageFlags kAllowDerivedKdfMaterial = kAllowKdfMaterial << 16;

        /**
         * @brief [SWS_CRYPT_13121]
         * Restrict usage of derived objects to specified operation mode only. A derived seed or
         * symmetric key can be used only for the mode directly specified by Key::AlgId.
         */
        const AllowedUsageFlags kAllowDerivedExactModeOnly = kAllowExactModeOnly << 16;

        /**
         * @brief [SWS_CRYPT_13117]
         * A derived seed or symmetric key can be used for seeding of a RandomGeneratorContext.
         */
        const AllowedUsageFlags kAllowDerivedRngInit = kAllowRngInit << 16;

        /**
         * @brief [SWS_CRYPT_13112]
         * A derived seed or symmetric key can be used for data encryption.
         */
        const AllowedUsageFlags kAllowDerivedDataEncryption = kAllowDataEncryption << 16;

        /**
         * @brief [SWS_CRYPT_13113]
         * A derived seed or symmetric key can be used for data decryption.
         */
        const AllowedUsageFlags kAllowDerivedDataDecryption = kAllowDataDecryption << 16;

        /**
         * @brief [SWS_CRYPT_13101]
         * The key/seed can be used for data encryption initialization (applicable to symmetric and
         * asymmetric algorithms).
         */
        const AllowedUsageFlags kAllowDataEncryption = 0x0001;

        /**
         * @brief [SWS_CRYPT_13102]
         * The key/seed can be used for data decryption initialization (applicable to symmetric and
         * asymmetric algorithms).
         */
        const AllowedUsageFlags kAllowDataDecryption = 0x0002;

        /**
         * @brief [SWS_CRYPT_13000]
         * Algorithm ID is undefined. Also this value may be used in meanings: Any or Default algorithm,
         * None of algorithms.
         * Effective values of Crypto Algorithm IDs are specific for concrete Crypto Stack implementation.
         * But the zero value is reserved for especial purposes, that can differ depending from a usage
         * context. This group defines a few constant names of the single zero value, but semantically
         * they have different meaning specific for concrete application of the constant.
         */
        const CryptoAlgId kAlgIdUndefined = 0u;

        /**
         * @brief [SWS_CRYPT_13003]
         * None of Algorithm ID (i.e. an algorithm definition is not applicable).
         */
        const CryptoAlgId kAlgIdNone = kAlgIdUndefined;

        /**
         * @brief [SWS_CRYPT_13002]
         * Default Algorithm ID (in current context/primitive).
         */
        const CryptoAlgId kAlgIdDefault = kAlgIdUndefined;

        /**
         * @brief [SWS_CRYPT_13001]
         * Any Algorithm ID is allowed.
         */
        const CryptoAlgId kAlgIdAny = kAlgIdUndefined;
    }
}

#endif // ARA_CRYPTO_CRYP_COMMON_BASE_ID_TYPES_H
