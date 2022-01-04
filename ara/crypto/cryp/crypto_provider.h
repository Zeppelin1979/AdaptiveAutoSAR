#ifndef ARA_CRYPTO_CRYP_CRYPTO_PROVIDER_H
#define ARA_CRYPTO_CRYP_CRYPTO_PROVIDER_H

#include "ara/crypto/cryp/cryobj/crypto_primitive_id.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_20700]
             * Crypto Provider is a "factory" interface of all supported Crypto Primitives and a "trusted
             * environmet" for internal communications between them. All Crypto Primitives should have an
             * actual reference to their parent Crypto Provider. A Crypto Provider can be destroyed only after
             * destroying of all its daughterly Crypto Primitives. Each method of this interface that creates a
             * Crypto Primitive instance is non-constant, because any such creation increases a references
             * counter of the Crypto Primitive.
             */
            class CryptoProvider
            {
            public:

                /**
                 * @brief [SWS_CRYPT_20703]
                 * A short alias for Algorithm ID type definition.
                 */
                using AlgId = CryptoPrimitiveId::AlgId;

                /**
                 * @brief [SWS_CRYPT_20701]
                 * Shared smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<CryptoProvider>;

                /**
                 * @brief [SWS_CRYPT_20710]
                 * Destroy the Crypto Provider object
                 * 
                 */
                virtual ~CryptoProvider () noexcept=default;
                
                /**
                 * @brief [SWS_CRYPT_20726]
                 * Allocate a Volatile (virtual) Trusted Container according to directly specified capacity. The
                 * Volatile Trusted Container can be used for execution of the import operations. Current process
                 * obtains the "Owner" rights for allocated Container. If (capacity == 0) then the capacity of the
                 * container will be selected automatically according to a maximal size of supported crypto
                 * objects. A few volatile (temporary) containers can coexist at same time without any affecting
                 * each-other.
                 * @param[in] capacity the capacity required for this volatile trusted container (in bytes)
                 * @return ara::core::Result<VolatileTrustedContainer::Uptr> unique smart pointer to an allocated volatile trusted container
                 */
                virtual ara::core::Result<VolatileTrustedContainer::Uptr> AllocVolatileContainer (std::size_t capacity=0) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20727]
                 * Allocate a Volatile (virtual) Trusted Container according to indirect specification of a minimal
                 * required capacity for hosting of any listed object. The Volatile Trusted Container can be used for
                 * execution of the import operations. Current process obtains the "Owner" rights for allocated
                 * Container. Real container capacity is calculated as a maximal storage size of all listed objects.
                 * @param[in] theObjectDef the list of objects that can be stored to this volatile trusted container
                 * @return ara::core::Result<VolatileTrustedContainer::Uptr> unique smart pointer to an allocated volatile trusted container
                 * @exception CryptoErrorDomain::kInvalidArgument if unsupported combination of object type and algorithm ID presents in the list
                 */
                virtual ara::core::Result<VolatileTrustedContainer::Uptr> AllocVolatileContainer (std::pair< AlgId, CryptoObjectType > theObjectDef) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20711]
                 * Convert a common name of crypto algorithm to a correspondent vendor specific binary algorithm ID.
                 * @param[in] primitiveName the unified name of the crypto primitive (see "Crypto Primitives Naming Convention" for more details)
                 * @return AlgId vendor specific binary algorithm ID or kAlgId Undefined if a primitive with provided name is not supported
                 */
                virtual AlgId ConvertToAlgId (ara::core::StringView primitiveName) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20712]
                 * Convert a vendor specific binary algorithm ID to a correspondent common name of the crypto algorithm.
                 * @param[in] algId the vendor specific binary algorithm ID
                 * @return ara::core::Result<ara::core::String> the common name of the crypto algorithm (see "Crypto Primitives Naming Convention" for more details)
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<ara::core::String> ConvertToAlgName (AlgId algId) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20731]
                 * Export publicly an object from a IOInterface (i.e. without an intermediate creation of a crypto
                 * object).
                 * @param[in] container the IOInterface that contains an object for export
                 * @param[in] formatId the CryptoProvider specific identifier of the output format
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > actual capacity required for the serialized data
                 * @exception CryptoErrorDomain::kEmptyContainer if the container is empty
                 * @exception CryptoErrorDomain::kUnexpectedValue if the container contains a secret crypto object
                 * @exception CryptoErrorDomain::kInsufficientCapacity if (serialized.empty() == false), but its capacity is not enough for storing result
                 * @exception CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after the IOInterface has been opened, i.e., the IOInterface has been invalidated
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ExportPublicObject (const IOInterface &container, Serializable::FormatId formatId=Serializable::kFormatDefault) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20728]
                 * Export a crypto object in a secure manner. if (serialized.empty() == true) then the method
                 * returns required size only, but content of the transportContext stays unchanged! Only an
                 * exportable and completed object (i.e. that have a UUID) can be exported!
                 * @param object the crypto object for export
                 * @param transportContext the symmetric key wrap context initialized by a transport key (allowed usage: kAllowKeyExporting)
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > the wrapped crypto object data
                 * @exception CryptoErrorDomain::kIncompatibleObject if the object cannot be exported due to IsExportable() returning false
                 * @exception CryptoErrorDomain::kIncompleteArgState if the transportContext is not initialized
                 * @exception CryptoErrorDomain::kIncompatibleObject if a key loaded to the transportContext doesn’t have required attributes (note: it is an optional error condition for this method)
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ExportSecuredObject (const CryptoObject &object, SymmetricKeyWrapperCtx &transportContext) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20729]
                 * Export securely an object directly from an IOInterface (i.e. without an intermediate creation of a
                 * crypto object). if (serialized == nullptr) then the method returns required size only, but content of
                 * the transportContext stays unchanged. This method can be used for re-exporting of just
                 * imported object but on another transport key.
                 * @param container the IOInterface that refers an object for export
                 * @param transportContext the symmetric key wrap context initialized by a transport key (allowed usage: kAllowKeyExporting)
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > actual capacity required for the serialized data
                 * @exception CryptoErrorDomain::kEmptyContainer if the container is empty
                 * @exception CryptoErrorDomain::kInsufficientCapacity if size of the serialized buffer is not enough for saving the output data
                 * @exception CryptoErrorDomain::kIncompleteArgState if the transportContext is not initialized
                 * @exception CryptoErrorDomain::kIncompatibleObject if a key loaded to the transportContext doesn’t have equired attributes (note: it is an optional error condition for this method)
                 * @exception CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after the IOInterface has been opened, i.e., the IOInterface has been invalidated.
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ExportSecuredObject (const IOInterface &container, SymmetricKeyWrapperCtx &transportContext) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20722]
                 * Allocate a new private key context of correspondent type and generates the key value
                 * randomly. A common COUID should be shared for both private and public keys. Any
                 * serializable (i.e. savable/non-session or exportable) key must generate own COUID!
                 * @param algId the identifier of target public-private key crypto algorithm
                 * @param allowedUsage the flags that define a list of allowed transformations’ types in which the target key can be used (see constants in scope of RestrictedUseObject)
                 * @param isSession the "session" (or "temporary") attribute for the target key (if true)
                 * @param Exportable the exportability attribute of the target key (if true)
                 * @return ara::core::Result<PrivateKey::Uptrc> smart unique pointer to the created private key object
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId has an unsupported value
                 * @exception CryptoErrorDomain::kIncompatibleArguments if allowedUsage argument is incompatible with target algorithm algId (note: it is an optional error condition for this method)
                 */
                virtual ara::core::Result<PrivateKey::Uptrc> GeneratePrivateKey (AlgId algId, AllowedUsageFlags allowedUsage, bool isSession=false, bool is Exportable=false) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20723]
                 * Generate a random Secret Seed object of requested algorithm.
                 * @param algId the identifier of target crypto algorithm
                 * @param allowedUsage the lags that define a list of allowed transformations’ types in which the target seed can be used (see constants in scope of RestrictedUseObject)
                 * @param isSession the "session" (or "temporary") attribute of the target seed (if true)
                 * @param isExportable the exportability attribute of the target seed (if true)
                 * @return ara::core::Result<SecretSeed::Uptrc> unique smart pointer to generated SecretSeed object
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId has an unsupported value
                 * @exception CryptoErrorDomain::kIncompatibleArguments if allowedUsage argument is incompatible with target algorithm algId (note: it is an optional error condition for this method)
                 */
                virtual ara::core::Result<SecretSeed::Uptrc> GenerateSeed (AlgId algId, SecretSeed::Usage allowedUsage, bool isSession=true, bool isExportable=false) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20721]
                 * Allocate a new symmetric key object and fill it by a new randomly generated value. Any
                 * serializable (i.e. savable/non-session or exportable) key must generate own COUID! By default
                 * Crypto Provider should use an internal instance of a best from all supported RNG (ideally
                 * TRNG).
                 * @param algId the identifier of target symmetric crypto algorithm
                 * @param allowedUsage the flags that define a list of allowed transformations’ types in which the target key can be used (see constants in scope of RestrictedUseObject)
                 * @param isSession the "session" (or "temporary") attribute of the target key (if true)
                 * @param isExportable the exportability attribute of the target key (if true)
                 * @return ara::core::Result<SymmetricKey::Uptrc> smart unique pointer to the created symmetric key object
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId has an unsupported value
                 * @exception CryptoErrorDomain::kIncompatibleArguments if allowedUsage argument is incompatible with target algorithm algId (note: it is an optional error condition for this method)
                 */
                virtual ara::core::Result<SymmetricKey::Uptrc> GenerateSymmetricKey (AlgId algId, AllowedUsageFlags allowedUsage, bool isSession=true, bool isExportable=false) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20725]
                 * Return minimally required capacity of a key slot for saving of the object’s payload. Returned
                 * value does not take into account the object’s meta-information properties, but their size is fixed
                 * and common for all crypto objects independently from their actual type. During an allocation of
                 * a TrustedContainer, Crypto Providers (and Key Storage Providers) reserve space for an object’s
                 * meta-information automatically, according to their implementation details.
                 * @param[in] cryptoObjectType the type of the target object
                 * @param[in] algId a CryptoProvider algorithm ID of the target object
                 * @return ara::core::Result<std::size_t> minimal size required for storing of the object in a TrustedContainer (persistent or volatile)
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId has an unsupported value
                 * @exception CryptoErrorDomain::kIncompatibleArguments if the arguments are incompatible
                 */
                virtual ara::core::Result<std::size_t> GetPayloadStorageSize (CryptoObjectType cryptoObjectType, AlgId algId) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20724]
                 * Return required buffer size for serialization of an object in specific format.
                 * @param[in] cryptoObjectType the type of the target object
                 * @param[in] algId the Crypto Provider algorithm ID of the target object
                 * @param[in] formatId the Crypto Provider specific identifier of the output format
                 * @return ara::core::Result<std::size_t> size required for storing of the object serialized in the specified format
                 * @exception CryptoErrorDomain::kUnknownIdentifier if any argument has an unsupported value
                 * @exception CryptoErrorDomain::kIncompatibleArguments if any pair of arguments are incompatible
                 */
                virtual ara::core::Result<std::size_t> GetSerializedSize (CryptoObjectType cryptoObjectType, AlgId algId, Serializable::FormatId formatId=Serializable::kFormatDefault) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20732]
                 * Import publicly serialized object to a storage location pointed to by an IOInterface for following
                 * processing (without allocation of a crypto object). If (expectedObject != CryptoObjectType::kUnknown)
                 * and an actual object type differs from the expected one then this method fails. If the
                 * serialized contains incorrect data then this method fails.
                 * @param[out] container the IOInterface for storing of the imported object
                 * @param[in] serialized the memory region that contains a securely serialized object that should be imported to the IOInterface
                 * @param[in] expectedObject the expected object type (default value CryptoObjectType::kUnknown means without check)
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUnexpectedValue if the serialized contains incorrect data
                 * @exception CryptoErrorDomain::kBadObjectType if (expectedObject != CryptoObjectType::kUnknown), but the actual object type differs from the expected one
                 * @exception CryptoErrorDomain::kInsufficientCapacity if capacity of the container is not enough to save the de-serialized object
                 * @exception CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after the IOInterface has been opened, i.e., the IOInterface has been invalidated.
                 * @exception CryptoErrorDomain::kUnreservedResource if the IOInterface is not opened writable
                 */
                virtual ara::core::Result<void> ImportPublicObject (IOInterface &container, ReadOnlyMemRegion serialized, CryptoObjectType expectedObject=CryptoObjectType::kUndefined) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20730]
                 * Import securely serialized object to the persistent or volatile storage represented by an
                 * IOInterface for following processing.
                 * @param[out] container the IOInterface for storing of the imported object
                 * @param[in] serialized the memory region that contains a securely serialized object that should be imported to the IOInterface
                 * @param[in] transportContext the symmetric key wrap context initialized by a transport key (allowed usage: kAllowKeyImporting)
                 * @param[in] isExportable the exportability attribute of the target object
                 * @param[in] expectedObject the expected object type (default value CryptoObjectType::kUnknown means without check)
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUnexpectedValue if the serialized contains incorrect data
                 * @exception CryptoErrorDomain::kBadObjectType if (expectedObject != CryptoObjectType::kUnknown), but the actual object type differs from the expected one
                 * @exception CryptoErrorDomain::kIncompleteArgState if the transportContext is not initialized
                 * @exception CryptoErrorDomain::kIncompatibleObject if a key loaded to the transportContext doesn’t have required attributes (note: it is an optional error condition for this method)
                 * @exception CryptoErrorDomain::kInsufficientCapacity if capacity of the container is not enough to save the de-serialized object
                 * @exception CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after the IOInterface has been opened, i.e., the IOInterface has been invalidated.
                 * @exception CryptoErrorDomain::kUnreservedResource if the IOInterface is not opened writable
                 */
                virtual ara::core::Result<void> ImportSecuredObject (IOInterface &container, ReadOnlyMemRegion serialized, SymmetricKeyWrapperCtx &transportContext, bool isExportable=false, CryptoObjectType expectedObject=CryptoObjectType::kUndefined) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20733]
                 * This method is one of the "binding" methods between a CryptoProvider and the Key Storage
                 * Provider.
                 * @param[in] container the IOInterface that contains the crypto object for loading
                 * @return ara::core::Result<CryptoObject::Uptrc> unique smart pointer to the created object
                 * @exception CryptoErrorDomain::kEmptyContainer if the container is empty
                 * @exception CryptoErrorDomain::kResourceFault if the container content is damaged
                 * @exception CryptoErrorDomain::kModifiedRessource if the underlying resource has been modified after the IOInterface has been opened, i.e., the IOInterface has been invalidated.
                 * @exception CryptoErrorDomain::kIncompatibleObject if the underlying resource belongs to another, incompatible CryptoProvider
                 */
                virtual ara::core::Result<CryptoObject::Uptrc> LoadObject (const IOInterface &container) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20764]
                 * Load a private key from the IOInterface provided.
                 * @param[in] container the IOInterface that contains the crypto object for loading
                 * @return ara::core::Result<PrivateKey::Uptrc> unique smart pointer to the PrivateKey
                 * @exception CryptoErrorDomain::kEmptyContainer if the container is empty
                 * @exception CryptoErrorDomain::kResourceFault if the container content is damaged
                 * @exception CryptoErrorDomain::kModifiedRessource if the underlying resource has been modified after the IOInterface has been opened, i.e., the IOInterface has been invalidated.
                 * @exception CryptoErrorDomain::kIncompatibleObject if the underlying resource belongs to another, incompatible CryptoProvider
                 */
                virtual ara::core::Result<PrivateKey::Uptrc> LoadPrivateKey (const IOInterface &container) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20763]
                 * Load a public key from the IOInterface provided.
                 * @param[in] container the IOInterface that contains the crypto object for loading
                 * @return ara::core::Result<PublicKey::Uptrc> unique smart pointer to the PublicKey
                 * @exception CryptoErrorDomain::kEmptyContainer if the container is empty
                 * @exception CryptoErrorDomain::kResourceFault if the container content is damaged
                 * @exception CryptoErrorDomain::kModifiedRessource if the underlying resource has been modified after the IOInterface has been opened, i.e., the IOInterface has been invalidated.
                 * @exception CryptoErrorDomain::kIncompatibleObject if the underlying resource belongs to another, incompatible CryptoProvider
                 */
                virtual ara::core::Result<PublicKey::Uptrc> LoadPublicKey (const IOInterface &container) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20765]
                 * Load secret seed from the IOInterface provided.
                 * @param container[in] the IOInterface that contains the crypto object for loading
                 * @return ara::core::Result<SecretSeed::Uptrc> unique smart pointer to the SecretSeed
                 * @exception CryptoErrorDomain::kEmptyContainer if the container is empty
                 * @exception CryptoErrorDomain::kResourceFault if the container content is damaged
                 * @exception CryptoErrorDomain::kModifiedRessource if the underlying resource has been modified after the IOInterface has been opened, i.e., the IOInterface has been invalidated.
                 * @exception CryptoErrorDomain::kIncompatibleObject if the underlying resource belongs to another, incompatible CryptoProvider
                 */
                virtual ara::core::Result<SecretSeed::Uptrc> LoadSecretSeed (const IOInterface &container) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20762]
                 * Load a symmetric key from the IOInterface provided.
                 * @param container[in] the IOInterface that contains the crypto object for loading
                 * @return ara::core::Result<SymmetricKey::Uptrc> unique smart pointer to the SymmetricKey
                 * @exception CryptoErrorDomain::kEmptyContainer if the container is empty
                 * @exception CryptoErrorDomain::kResourceFault if the container content is damaged
                 * @exception CryptoErrorDomain::kModifiedRessource if the underlying resource has been modified after the IOInterface has been opened, i.e., the IOInterface has been invalidated.
                 * @exception CryptoErrorDomain::kIncompatibleObject if the underlying resource belongs to another, incompatible CryptoProvider
                 */
                virtual ara::core::Result<SymmetricKey::Uptrc> LoadSymmetricKey (const IOInterface &container) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20745]
                 * Create a symmetric authenticated cipher context.
                 * @param[in] algId identifier of the target crypto algorithm
                 * @return ara::core::Result<AuthCipherCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from symmetric authenticated stream cipher
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<AuthCipherCtx::Uptr> CreateAuthCipherCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20751]
                 * Create a decryption private key context.
                 * @param[in] algId identifier of the target asymmetric encryption/decryption algorithm
                 * @return ara::core::Result<DecryptorPrivateCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from asymmetric encryption/decryption
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<DecryptorPrivateCtx::Uptr> CreateDecryptorPrivateCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20750]
                 * Create an encryption public key context.
                 * @param[in] algId identifier of the target asymmetric encryption/decryption algorithm
                 * @return ara::core::Result<EncryptorPublicCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from asymmetric encryption/decryption
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<EncryptorPublicCtx::Uptr> CreateEncryptorPublicCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20761]
                 * Construct Signature object from directly provided components of a hash digest.
                 * @param[in] hashAlgId identifier of an applied hash function crypto algorithm
                 * @param[in] value raw BLOB value of the hash digest
                 * @return ara::core::Result<Signature::Uptrc> unique smart pointer to the created Signature object
                 * @exception CryptoErrorDomain::kInvalidInputSize if the value argument has invalid size (i.e. incompatible with the hashAlgId argument)
                 * @exception CryptoErrorDomain::kInvalidArgument if hashAlgId argument specifies crypto algorithm different from a hash function
                 * @exception CryptoErrorDomain::kUnknownIdentifier if hashAlgId argument has unsupported value
                 */
                virtual ara::core::Result<Signature::Uptrc> CreateHashDigest (AlgId hashAlgId, ReadOnlyMemRegion value) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20747]
                 * Create a hash function context.
                 * @param algId identifier of the target crypto algorithm
                 * @return ara::core::Result<HashFunctionCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from hash function
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<HashFunctionCtx::Uptr> CreateHashFunctionCtx(AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20758]
                 * Create a key-agreement private key context.
                 * @param algId identifier of the target key-agreement crypto algorithm
                 * @return ara::core::Result<KeyAgreementPrivateCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from key-agreement
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<KeyAgreementPrivateCtx::Uptr> CreateKeyAgreementPrivateCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20753]
                 * Create a key-decapsulator private key context of a Key Encapsulation Mechanism (KEM).
                 * @param algId identifier of the target KEM crypto algorithm
                 * @return ara::core::Result<KeyDecapsulatorPrivateCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from asymmetric KEM
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<KeyDecapsulatorPrivateCtx::Uptr> CreateKeyDecapsulatorPrivateCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20748]
                 * Create a key derivation function context.
                 * @param algId identifier of the target crypto algorithm
                 * @return ara::core::Result<KeyDerivationFunctionCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from key derivation function
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<KeyDerivationFunctionCtx::Uptr> CreateKeyDerivationFunctionCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20752]
                 * Create a key-encapsulator public key context of a Key Encapsulation Mechanism (KEM).
                 * @param algId identifier of the target KEM crypto algorithm
                 * @return ara::core::Result<KeyEncapsulatorPublicCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from asymmetric KEM
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<KeyEncapsulatorPublicCtx::Uptr> CreateKeyEncapsulatorPublicCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20746]
                 * Create a symmetric message authentication code context.
                 * @param algId identifier of the target crypto algorithm
                 * @return ara::core::Result<MessageAuthnCodeCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from symmetric message authentication code
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<MessageAuthnCodeCtx::Uptr> CreateMessageAuthCodeCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20755]
                 * Create a message recovery public key context.
                 * @param algId identifier of the target asymmetric crypto algorithm
                 * @return ara::core::Result<MsgRecoveryPublicCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from asymmetric signature encoding with message recovery
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<MsgRecoveryPublicCtx::Uptr> CreateMsgRecoveryPublicCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20741]
                 * Create a Random Number Generator (RNG) context.
                 * @param algId identifier of target RNG algorithm. If no algId is given, the default RNG is returned
                 * @param initialize indicates whether the returned context shall be initialized (i.e., seeded) by the stack
                 * @return ara::core::Result<RandomGeneratorCtx::Uptr> unique smart pointer to the created RNG context
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value or if (algId == kAlgIdDefault) and the CryptoProvider does not provide any RandomGeneratorCtx
                 * @exception CryptoErrorDomain::kBusyResource if (initialize == true) but the context currently cannot be seeded (e.g., due to a lack of entropy)
                 */
                virtual ara::core::Result<RandomGeneratorCtx::Uptr> CreateRandomGeneratorCtx (AlgId algId=kAlgIdDefault, bool initialize=true) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20754]
                 * Create a signature encoding private key context.
                 * @param algId identifier of the target asymmetric crypto algorithm
                 * @return ara::core::Result<SigEncodePrivateCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from asymmetric signature encoding with message recovery
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<SigEncodePrivateCtx::Uptr> CreateSigEncodePrivateCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20760]
                 * Construct Signature object from directly provided components of a digital signature/MAC or
                 * authenticated encryption (AE/AEAD). All integers inside a digital signature BLOB value are
                 * always presented in Big Endian bytes order (i.e. MSF - Most Significant byte First).
                 * @param signAlgId identifier of an applied signature/MAC/AE/AEAD crypto algorithm
                 * @param value raw BLOB value of the signature/MAC
                 * @param key symmetric or asymmetric key (according to signAlgId) applied for the sign or MAC/AE/AEAD operation
                 * @param hashAlgId identifier of a hash function algorithm applied together with the signature algorithm
                 * @return ara::core::Result<Signature::Uptrc> unique smart pointer to the created Signature object
                 * @exception CryptoErrorDomain::kInvalidArgument if signAlgId or hashAlgId arguments specify crypto algorithms different from the signature/MAC/AE/AEAD and message digest respectively
                 * @exception CryptoErrorDomain::kUnknownIdentifier if signAlgId or hashAlgId arguments have unsupported values
                 * @exception CryptoErrorDomain::kIncompatibleArguments if signAlgId and hashAlgId arguments specify incompatible algorithms (if signAlgId includes hash function specification) or if a crypto primitive associated with the key argument is incompatible with provided signAlgId or hashAlgId arguments
                 * @exception CryptoErrorDomain::kInvalidInputSize if the value argument has invalid size (i.e. incompatible with the signAlgId argument)
                 */
                virtual ara::core::Result<Signature::Uptrc> CreateSignature (AlgId signAlgId, ReadOnlyMemRegion value, const RestrictedUseObject &key, AlgId hashAlgId=kAlgIdNone) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20756]
                 * Create a signature private key context.
                 * @param algId identifier of the target signature crypto algorithm
                 * @return ara::core::Result<SignerPrivateCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from private key signature
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<SignerPrivateCtx::Uptr> CreateSignerPrivateCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20744]
                 * Create a symmetric stream cipher context.
                 * @param algId identifier of the target crypto algorithm
                 * @return ara::core::Result<StreamCipherCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from symmetric stream cipher
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<StreamCipherCtx::Uptr> CreateStreamCipherCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20742]
                 * Create a symmetric block cipher context.
                 * @param algId identifier of the target crypto algorithm
                 * @return ara::core::Result<SymmetricBlockCipherCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<SymmetricBlockCipherCtx::Uptr> CreateSymmetricBlockCipherCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20743]
                 * Create a symmetric key-wrap algorithm context.
                 * @param algId identifier of the target crypto algorithm
                 * @return ara::core::Result<SymmetricKeyWrapperCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from symmetric key-wrapping
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<SymmetricKeyWrapperCtx::Uptr> CreateSymmetricKeyWrapperCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20757]
                 * Create a signature verification public key context.
                 * @param algId identifier of the target signature crypto algorithm
                 * @return ara::core::Result<VerifierPublicCtx::Uptr> unique smart pointer to the created context
                 * @exception CryptoErrorDomain::kInvalidArgument if algId argument specifies a crypto algorithm different from public key signature verification
                 * @exception CryptoErrorDomain::kUnknownIdentifier if algId argument has an unsupported value
                 */
                virtual ara::core::Result<VerifierPublicCtx::Uptr> CreateVerifierPublicCtx (AlgId algId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30216]
                 * Copy-assign another CryptoProvider to this instance.
                 * @param other the other instance
                 * @return CryptoProvider& *this, containing the contents of other
                 */
                CryptoProvider& operator= (const CryptoProvider &other)=default;

                /**
                 * @brief [SWS_CRYPT_30217]
                 * Move-assign another CryptoProvider to this instance.
                 * @param other the other instance
                 * @return CryptoProvider& *this, containing the contents of other
                 */
                CryptoProvider& operator= (const CryptoProvider &&other)=default;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_CRYPTO_PROVIDER_H