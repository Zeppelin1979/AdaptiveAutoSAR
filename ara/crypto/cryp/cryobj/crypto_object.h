#ifndef ARA_CRYPTO_CRYP_CRYOBJ_CRYPTO_OBJECT_H
#define ARA_CRYPTO_CRYP_CRYOBJ_CRYPTO_OBJECT_H

namespace ara
{
    namespace crypto
    {
        /**
         * @brief [SWS_CRYPT_20500]
         * A common interface for all cryptograhic objects recognizable by the Crypto Provider. This
         * interface (or any its derivative) represents a non-mutable (after completion) object loadable to a
         * temporary transformation context.
         */
        class CryptoObject
        {
        private:
            CryptoPrimitiveId::Uptr mCryptoPrimitiveId;
            COIdentifier mObjectId;

        public:

            /**
             * @brief [SWS_CRYPT_20402]
             * Type definition of vendor specific binary Crypto Primitive ID.
             */
            using AlgId = CryptoAlgId;

            /**
             * @brief [SWS_CRYPT_20504]
             * Unique identifier of this CryptoObject.
             */
            struct COIdentifier
            {
                /**
                 * @brief [SWS_CRYPT_20506]
                 * type of objext
                 */
                CryptoObjectType mCOType;

                /**
                 * @brief [SWS_CRYPT_20507]
                 * object identifier
                 */
                CryptoObjectUid mCouid;
            };

            /**
             * @brief [SWS_CRYPT_20502]
             * Unique smart pointer of the constant interface.
             */
            using Uptrc = std::unique_ptr<const CryptoObject>;

            /**
             * @brief [SWS_CRYPT_20501]
             * Unique smart pointer of the interface.
             */
            using Uptr = std::unique_ptr<CryptoObject>;

            /**
             * @brief [SWS_CRYPT_20503]
             * Destroy the Crypto Object object
             * 
             */
            virtual ~CryptoObject () noexcept=default;

            /**
             * @brief [SWS_CRYPT_20518]
             * Downcast and move unique smart pointer from the generic CryptoObject interface to concrete
             * derived object.
             * @tparam ConcreteObject target type (derived from CryptoObject) for downcasting
             * @param[in] object unique smart pointer to the constant generic Crypto Object interface
             * @return ara::core::Result<typename ConcreteObject::Uptrc> unique smart pointer to downcasted constant interface of specified derived type
             * @exception CryptoErrorDomain::kBadObjectType if an actual type of the object is not the specified ConcreteObject
             */
            template <class ConcreteObject>
            static ara::core::Result<typename ConcreteObject::Uptrc> Downcast (CryptoObject::Uptrc &&object) noexcept;

            /**
             * @brief [SWS_CRYPT_20505]
             * Return the CryptoPrimitivId of this CryptoObject.
             * @return CryptoPrimitiveId::Uptr 
             */
            virtual CryptoPrimitiveId::Uptr GetCryptoPrimitiveId () const noexcept=0
            {
                return mCryptoPrimitiveId;
            }

            /**
             * @brief [SWS_CRYPT_20514]
             * Return the object’s COIdentifier, which includes the object’s type and UID. An object that has no
             * assigned COUID cannot be (securely) serialized / exported or saved to a non-volatile storage.
             * An object should not have a COUID if it is session and non-exportable simultaneously A few
             * related objects of different types can share a single COUID (e.g. private and public keys), but a
             * combination of COUID and object type must be unique always!
             * @return COIdentifier the object’s COIdentifier including the object’s type
             * and COUID (or an empty COUID, if this object is not identifiable).
             */
            virtual COIdentifier GetObjectId () const noexcept=0
            {
                return mObjectId;
            }

            /**
             * @brief [SWS_CRYPT_20516]
             * Return actual size of the object’s payload. Returned value always must be less than or equal to
             * the maximum payload size expected for this primitive and object type, it is available via call:
             * MyProvider().GetPayloadStorageSize(GetObjectType(), GetPrimitiveId()).Value(); Returned value
             * does not take into account the object’s meta-information properties, but their size is fixed and
             * common for all crypto objects independently from their actual type. During an allocation of a
             * TrustedContainer, Crypto Providers (and Key Storage Providers) reserve space for an object’s
             * meta-information automatically, according to their implementation details.
             * @return std::size_t 
             */
            virtual std::size_t GetPayloadSize () const noexcept=0;

            /**
             * @brief [SWS_CRYPT_20515]
             * Return the COIdentifier of the CryptoObject that this CryptoObject depends on. For signatures
             * objects this method must return a reference to correspondent signature verification public key!
             * Unambiguous identification of a CryptoObject requires both components: CryptoObjectUid and
             * CryptoObjectType.
             * @return COIdentifier 
             */
            virtual COIdentifier HasDependence () const noexcept=0;

            /**
             * @brief [SWS_CRYPT_20513]
             * Get the exportability attribute of the crypto object. An exportable object must have an assigned
             * COUID (see GetObjectId()).
             * @return true if the object is exportable (i.e. if it can be exported outside the trusted environment of the Crypto Provider)
             * @return false otherwise
             */
            virtual bool IsExportable () const noexcept=0;

            /**
             * @brief [SWS_CRYPT_20512]
             * Return the "session" (or "temporary") attribute of the object. A temporary object cannot be
             * saved to a persistent storage location pointed to by an IOInterface! A temporary object will be
             * securely destroyed together with this interface instance! A non-session object must have an
             * assigned COUID (see GetObjectId()).
             * @return true if the object is temporay (i.e. its life time is limited by the current session only)
             * @return false otherwise
             */
            virtual bool IsSession () const noexcept=0;

            /**
             * @brief [SWS_CRYPT_20517]
             * Save itself to provided IOInterface A CryptoObject with property "session" cannot be saved in a
             * KeySlot.
             * @param[in] container IOInterface representing underlying storag
             * @return ara::core::Result<void> 
             * @exception CryptoErrorDomain::kIncompatibleObject if the object is "session", but the IOInterface represents a KeySlot.
             * @exception CryptoErrorDomain::kContentRestrictions if the object doesn’t satisfy the slot restrictions (
             * @exception CryptoErrorDomain::kInsufficientCapacity if the capacity of the target container is not enough, i.e. if (container.Capacity() < this->StorageSize())
             * @exception CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after the IOInterface has been opened, i.e., the IOInterface has been invalidated.
             * @exception CryptoErrorDomain::kUnreservedResource if the IOInterface is not opened writeable.
             */
            virtual ara::core::Result<void> Save (IOInterface &container) const noexcept=0;

            /**
             * @brief [SWS_CRYPT_30208]
             * Copy-assign another CryptoObject to this instance.
             * @param other the other instance
             * @return CryptoObject& *this, containing the contents of other
             */
            CryptoObject& operator= (const CryptoObject &other)=default;

            /**
             * @brief [SWS_CRYPT_30208]
             * Move-assign another CryptoObject to this instance.
             * @param other the other instance
             * @return CryptoObject& *this, containing the contents of other
             */
            CryptoObject& operator= (const CryptoObject &&other)=default;

        };
    }
}

#endif // ARA_CRYPTO_CRYP_CRYOBJ_CRYPTO_OBJECT_H
