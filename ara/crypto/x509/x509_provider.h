#ifndef ARA_CRYPTO_X509_X509_PROVIDER_H
#define ARA_CRYPTO_X509_X509_PROVIDER_H

#include <memory>

#include "ara/core/instance_specifier.h"

#include "ara/crypto/cryp/signer_private_ctx.h"

#include "ara/crypto/x509/x509_dn.h"
#include "ara/crypto/x509/certificate.h"
#include "ara/crypto/x509/ocsp_response.h"
#include "ara/crypto/x509/ocsp_request.h"
#include "ara/crypto/x509/cert_sign_request.h"
#include "ara/crypto/x509/x509_extensions.h"
#include "ara/crypto/x509/x509_custom_extension_parser.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_40600]
             * X.509 Provider interface. The X.509 Provider supports two internal storages: volatile (or
             * session) and persistent. All X.509 objects created by the provider should have an actual
             * reference to their parent X.509 Provider. The X.509 Provider can be destroyed only after
             * destroying of all its daughterly objects. Each method of this interface that creates a X.509
             * object is non-constant, because any such creation increases a references counter of the X.509
             * Provider.
             */
            class X509Provider
            {
            public:

                /**
                 * @brief [SWS_CRYPT_40601]
                 * Shared smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<X509Provider>;

                /**
                 * @brief [SWS_CRYPT_40602]
                 * Type of an internal index inside the certificate storage.
                 */
                using StorageIndex = std::size_t;

                /**
                 * @brief [SWS_CRYPT_40603]
                 * Reserved "invalid index" value for navigation inside the certificate storage.
                 */
                static const StorageIndex kInvalidIndex = static_cast<std::size_t>(-1LL);

                /**
                 * @brief [SWS_CRYPT_40612]
                 * Create completed X.500 Distinguished Name structure from the provided string representation.
                 * @param[in] dn string representation of the Distinguished Name
                 * @return ara::core::Result<X509DN::Uptrc> unique smart pointer for the created X509DN object
                 * @exception CryptoErrorDomain::kInvalidArgument if the dn argument has incorrect format
                 * @exception CryptoErrorDomain::kInvalidInputSize if the dn argument has unsupported length (too large)
                 */
                virtual ara::core::Result<X509DN::Uptrc> BuildDn (ara::core::StringView dn) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40629]
                 * Check certificate status by directly provided OCSP response. This method may be used for
                 * implementation of the "OCSP stapling". This method updates the Certificate::Status associated
                 * with the certificate.
                 * @param[in] cert a certificate that should be verified
                 * @param[in] ocspResponse an OCSP response
                 * @return ara::core::Result<bool> true if the certificate is verified successfully and false otherwise
                 * @exception CryptoErrorDomain::kInvalidArgument if the cert is invalid
                 * @exception CryptoErrorDomain::kRuntimeFault if the ocspResponse is invalid
                 */
                virtual ara::core::Result<bool> CheckCertStatus (Certificate &cert, const OcspResponse &ocspResponse) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40630]
                 * Check status of a certificates list by directly provided OCSP response. This method may be
                 * used for implementation of the "OCSP stapling". This method updates the Certificate::Status
                 * associated with the certificates in the list.
                 * @param[in] certList a certificates list that should be verified
                 * @param[in] ocspResponse an OCSP response
                 * @return ara::core::Result<bool> true if the certificates list is verified successfully and false otherwise
                 * @exception CryptoErrorDomain::kInvalidArgument if the cert is invalid
                 * @exception CryptoErrorDomain::kRuntimeFault if the ocspResponse is invalid
                 */
                virtual ara::core::Result<bool> CheckCertStatus (const ara::core::Vector< Certificate * > &certList, const OcspResponse &ocspResponse) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40639]
                 * Check certificate status via On-line Certificate Status Protocol (OCSP).
                 * @param[in] cert a certificate that should be verified
                 * @return ara::core::Result<Certificate::Status> certificate status This method updates the
                 * Certificate::Status associated with the certificate.
                 * @exception CryptoErrorDomain::kInvalidArgument if the provided certificate is invalid
                 * @exception CryptoErrorDomain::kNoConnection if a connection to the OCSP responder cannot be established
                 */
                virtual ara::core::Result<Certificate::Status> CheckCertStatusOnline (Certificate &cert) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40635]
                 * Cleanup the volatile certificates storage. After execution of this command the certificates
                 * previously imported to the volatile storage cannot be found by a search, but it doesn’t influence
                 * to already loaded Certificate instances!
                 */
                virtual void CleanupVolatileStorage () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40640]
                 * Create certification request for a private key loaded to the context.
                 * @param[in] signerCtx the fully-configured SignerPrivateCtx to be used for signing this certificate request
                 * @param[in] derSubjectDN the DER-encoded subject distinguished name (DN) of the private key owner
                 * @param[in] x509Extensions the DER-encoded X.509 Extensions that should be included to the certification request
                 * @param[in] version the format version of the target certification request
                 * @return ara::core::Result<CertSignRequest::Uptrc> unique smart pointer to created certification request
                 * @exception CryptoErrorDomain::kUnexpectedValue if any of arguments has incorrect/unsupported value
                 */
                virtual ara::core::Result<CertSignRequest::Uptrc> CreateCertSignRequest (cryp::SignerPrivateCtx::Uptr signerCtx, ReadOnlyMemRegion derSubjectDN, ReadOnlyMemRegion x509Extensions=ReadOnlyMemRegion(), unsigned version=1) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40615]
                 * Count number of certificates in a serialized certificate chain represented by a single BLOB.
                 * @param[in] certChain DER/PEM-encoded certificate chain (in form of a single BLOB)
                 * @param[in] formatId input format identifier (kFormatDefault means auto-detect)
                 * @return ara::core::Result<std::size_t> number of certificates in the chain
                 * @exception CryptoErrorDomain::kInvalidArgument if the certChain argument cannot be pre-parsed
                 * @exception CryptoErrorDomain::kUnknownIdentifier if the formatId argument has unknown value
                 */
                virtual ara::core::Result<std::size_t> CountCertsInChain (ReadOnlyMemRegion certChain, Serializable::FormatId formatId=Serializable::kFormatDefault) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40611]
                 * Create an empty X.500 Distinguished Name (DN) structure. If (0 == capacity) then a maximally
                 * supported (by the implementation) capacity must be reserved.
                 * @param[in] capacity number of bytes that should be reserved for the content of the target X509DN object
                 * @return ara::core::Result<X509DN::Uptr> Unique smart pointer to created empty X509DN object
                 */
                virtual ara::core::Result<X509DN::Uptr> CreateEmptyDn (std::size_t capacity=0) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40636]
                 * Create an empty X.509 Extensions structure. If (0 == capacity) then a maximally supported (by
                 * the implementation) capacity must be reserved.
                 * @param[in] capacity number of bytes that should be reserved for the content of the target X509Extensions object
                 * @return ara::core::Result<X509Extensions::Uptr> Shared smart pointer to created empty X509Extensions object
                 */
                virtual ara::core::Result<X509Extensions::Uptr> CreateEmptyExtensions(std::size_t capacity=0) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40626]
                 * Create OCSP request for specified certificate. This method may be used for implementation of
                 * the "OCSP stapling".
                 * @param[in] cert a certificate that should be verified
                 * @param[in] signer an optional pointer to initialized signer context (if the request should be signed)
                 * @return ara::core::Result<OcspRequest::Uptrc> unique smart pointer to the created OCSP request
                 * @exception CryptoErrorDomain::kInvalidArgument if the provided certificate is invalid
                 * @exception CryptoErrorDomain::kIncompleteArgState if the signer context is not initialized by a key
                 */
                virtual ara::core::Result<OcspRequest::Uptrc> CreateOcspRequest (const Certificate &cert, ara::core::Optional< const cryp::SignerPrivateCtx::Uptr > signer) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40627]
                 * Create OCSP request for specified list of certificates. This method may be used for
                 * implementation of the "OCSP stapling".
                 * @param[in] certList a certificates’ list that should be verified
                 * @param[in] signer an optional pointer to initialized signer context (if the request should be signed)
                 * @return ara::core::Result<OcspRequest::Uptrc> unique smart pointer to the created OCSP request
                 * @exception CryptoErrorDomain::kInvalidArgument if the provided certificates are invalid
                 * @exception CryptoErrorDomain::kIncompleteArgState if the signer context is not initialized by a key
                 */
                virtual ara::core::Result<OcspRequest::Uptrc> CreateOcspRequest (const ara::core::Vector< const Certificate * > &certList, ara::core::Optional< const cryp::SignerPrivateCtx::Uptr > signer) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40613]
                 * Decode X.500 Distinguished Name structure from the provided serialized format.
                 * @param[in] dn DER/PEM-encoded representation of the Distinguished Name
                 * @param[in] formatId input format identifier (kFormatDefault means auto-detect)
                 * @return ara::core::Result<X509DN::Uptrc> unique smart pointer for the created X509DN object
                 * @exception CryptoErrorDomain::kInvalidArgument if the dn argument cannot be parsed
                 * @exception CryptoErrorDomain::kUnknownIdentifier if the formatId argument has unknown value
                 */
                virtual ara::core::Result<X509DN::Uptrc> DecodeDn (ReadOnlyMemRegion dn, Serializable::FormatId formatId=Serializable::kFormatDefault) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40631]
                 * Find a certificate by the subject and issuer Distinguished Names (DN).
                 * @param[in] subjectDn subject DN of the target certificate
                 * @param[in] issuerDn issuer DN of the target certificate
                 * @param[in] validityTimePoint a time point when the target certificate should be valid
                 * @return ara::core::Vector<Certificate::Uptrc> a vector of unique smart pointers to found certificates; the vector is empty, if nothing is found
                 */
                virtual ara::core::Vector<Certificate::Uptrc> FindCertByDn (const X509DN &subjectDn, const X509DN &issuerDn, time_t validityTimePoint) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40632]
                 * Find a certificate by its SKID & AKID.
                 * @param[in] subjectKeyId subject key identifier (SKID)
                 * @param[in] authorityKeyId optional authority key identifier (AKID)
                 * @return ara::core::Vector<Certificate::Uptrc> a vector of unique smart pointers to found certificates; the vector is empty, if nothing is found kUnknownIdentifier
                 */
                virtual ara::core::Vector<Certificate::Uptrc> FindCertByKeyIds (ReadOnlyMemRegion subjectKeyId, ara::core::Optional< ReadOnlyMemRegion > authorityKeyId) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40633]
                 * Find a certificate by its serial number and issue DN.
                 * @param sn serial number of the target certificate
                 * @param issuerDn authority’s Distinguished Names (DN)
                 * @return ara::core::Result<Certificate::Uptrc> the specified certificate or an error, if the certificate cannot be found
                 * @exception CryptoErrorDomain::kUnknownIdentifier if the specified certificate could not be found
                 */
                virtual ara::core::Result<Certificate::Uptrc> FindCertBySn (ReadOnlyMemRegion sn, const X509DN &issuerDn) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40634]
                 * Parse a certificate signing request (CSR) provided by the user.
                 * @param[in] csr the buffer containing a certificate signing request
                 * @param[in] withMetaData specifies the format of the buffer content: TRUE
                 * means the object has been previously serialized by using the Serializable interface; FALSE means the
                 * CSR was exported using the CertSign Request::ExportASN1CertSignRequest() interface
                 * @return ara::core::Result<CertSignRequest::Uptrc> unique smart pointer to the certificate signing request
                 * @exception CryptoErrorDomain::kUnsupportedFormat is returned in case the provided buffer does not contain the expected format
                 */
                virtual ara::core::Result<CertSignRequest::Uptrc> ParseCertSignRequest (ReadOnlyMemRegion csr, bool withMetaData=true) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40620]
                 * Import Certificate Revocation List (CRL) or Delta CRL from a memory BLOB. If the imported
                 * CRL lists some certificates kept in the persistent or volatile storages then their status must be
                 * automatically updated to Status::kInvalid. If some of these certificates were already openned
                 * during this operation, then this status change becomes available immediately (via method call
                 * Certificate::GetStatus())! All certificates with the status kInvalid should be automatically
                 * removed from correspondent storages (immediately if a certificate not in use now or just after
                 * its closing otherwise).
                 * @param crl serialized CRL or Delta CRL (in form of a BLOB)
                 * @return ara::core::Result<bool> true if the CRL is valid and false if it is already expired
                 * @exception CryptoErrorDomain::kUnexpectedValue if the provided BLOB is not a CRL/DeltaCRL
                 * @exception CryptoErrorDomain::kRuntimeFault if the CRL validation has failed
                 */
                virtual ara::core::Result<bool> ImportCrl (ReadOnlyMemRegion crl) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40621]
                 * Import the certificate to volatile or persistent storage. Only imported certificate may be found by
                 * a search and applied for automatic verifications! A certificate can be imported to only one of
                 * storage: volatile or persistent. Therefore if you import a certificate already kept in the persistent
                 * storage to the volatile one then nothing changes. But if you import a certificate already kept in
                 * the volatile storage to the persistent one then it is "moved" to the persistent realm. If an
                 * application successfully imports a certificate that correspond to a CSR existing in the storage
                 * then this CSR should be removed.
                 * @param[in] cert a valid certificate that should be imported
                 * @param[in] iSpecify optionally a valid InstanceSpecifier can be provided that points to a CertificateSlot for persistent storage
                 * of the certificate, otherwise the certificate shall be stored in volatile (session) storage
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kInvalidArgument if the provided certificate is invalid
                 * @exception CryptoErrorDomain::kIncompatibleObject if provided certificate has partial collision with a matched CSR in the storage
                 * @exception CryptoErrorDomain::kContentDuplication if the provided certificate already exists in the storage
                 * @exception CryptoErrorDomain::kAccessViolation if the InstanceSpecifier points to a CertificateSlot, which the application may only read
                 */
                virtual ara::core::Result<void> Import (const Certificate &cert, ara::core::Optional< ara::core::InstanceSpecifier > iSpecify) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40641]
                 * Load a certificate from the persistent certificate storage.
                 * @param[in] iSpecify the target certificate instance specifier
                 * @return ara::core::Result<Certificate::Uptr> an unique smart pointer to the instantiated certificate
                 * @exception CryptoErrorDomain::kUnreservedResource if the InstanceSpecifier is incorrect (the certificate cannot be found)
                 */
                virtual ara::core::Result<Certificate::Uptr> LoadCertificate (ara::core::InstanceSpecifier &iSpecify) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40616]
                 * Parse a serialized representation of the certificate chain and create their instances. Off-line
                 * validation of the parsed certification chain may be done via call VerifyCertChainByCrl(). After
                 * validation the certificates may be saved to the session or persistent storage for following search
                 * and usage. If the certificates are not imported then they will be lost after destroy of the returned
                 * instances! Only imported certificates may be found by a search and applied for automatic
                 * verifications! Certificates in the outcome vector will be placed from the root CA certificate (zero
                 * index) to the final end-entity certificate (last used index of the vector).
                 * @param[out] outcome an output vector for imported certificates
                 * @param[in] certChain DER/PEM-encoded certificate chain (in form of a single BLOB)
                 * @param[in] formatId input format identifier (kFormatDefault means auto-detect)
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kInsufficientCapacity if the capacity of outcome vector is less than actual number of certificates in the chain
                 * @exception CryptoErrorDomain::kInvalidArgument if the certChain argument cannot be parsed
                 * @exception CryptoErrorDomain::kUnknownIdentifier if the formatId argument has unknown value
                 */
                virtual ara::core::Result<void> ParseCertChain (ara::core::Vector<Certificate::Uptr > &outcome, ReadOnlyMemRegion certChain, Serializable::FormatId formatId=Serializable::kFormatDefault) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40617]
                 * Parse a serialized representation of the certificate chain and create their instances. Off-line
                 * validation of the parsed certification chain may be done via call VerifyCertChainByCrl(). After
                 * validation the certificates may be imported to the session or persistent storage for following
                 * search and usage. Capacity of the outcome vector must be equal to the size of the certChain
                 * vector. If the certificates are not imported then they will be lost after destroy of the returned
                 * instances! Only imported certificates may be found by a search and applied for automatic
                 * verifications! Certificates in the outcome vector will be placed from the root CA certificate (zero
                 * index) to the final end-entity certificate (last used index of the vector).
                 * @param[out] outcome an output vector for imported certificates
                 * @param[in] certChain DER/PEM-encoded certificate chain (in form of a single BLOB)
                 * @param[in] formatId input format identifier (kFormatDefault means auto-detect)
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kInsufficientCapacity if the capacity of outcome vector is less than actual number of certificates in the chain
                 * @exception CryptoErrorDomain::kInvalidArgument if the certChain argument cannot be parsed
                 * @exception CryptoErrorDomain::kUnknownIdentifier if the formatId argument has unknown value
                */
                virtual ara::core::Result<void> ParseCertChain (ara::core::Vector<Certificate::Uptr > &outcome, const ara::core::Vector< ReadOnlyMemRegion > &certChain, Serializable::FormatId formatId=Serializable::kFormatDefault) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40614]
                 * Parse a serialized representation of the certificate and create its instance. Off-line validation of
                 * the parsed certificate may be done via call VerifyCertByCrl(). After validation the certificate may
                 * be imported to the session or persistent storage for following search and usage. If the parsed
                 * certificate is not imported then it will be lost after destroy of the returned instance! Only
                 * imported certificate may be found by a search and applied for automatic verifications!
                 * @param[in] cert DER/PEM-encoded certificate
                 * @param[in] formatId input format identifier (kFormatDefault means auto-detect)
                 * @return ara::core::Result<Certificate::Uptr> unique smart pointer to created certificate
                 * @exception CryptoErrorDomain::kInvalidArgument if the cert argument cannot be parsed
                 * @exception CryptoErrorDomain::kUnknownIdentifier if the formatId argument has unknown value
                 */
                virtual ara::core::Result<Certificate::Uptr> ParseCert (ReadOnlyMemRegion cert, Serializable::FormatId formatId=Serializable::kFormatDefault) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40628]
                 * Parse serialized OCSP response and create correspondent interface instance. This method
                 * may be used for implementation of the "OCSP stapling".
                 * @param[in] response a serialized OCSP response
                 * @return OcspResponse::Uptrc unique smart pointer to the created OCSP response instance
                 * @exception CryptoErrorDomain::kUnexpectedValue if the provided BLOB response doesn’t keep an OCSP response
                 */
                virtual OcspResponse::Uptrc ParseOcspResponse (ReadOnlyMemRegion response) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40622]
                 * Remove specified certificate from the storage (volatile or persistent) and destroy it.
                 * @param[in] cert a unique smart pointer to a certificate that should be removed
                 * @return true if the certificate was found and removed from the storage
                 * @return false if it was not found
                 */
                virtual bool Remove (Certificate::Uptrc &&cert) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40638]
                 * Send prepared certificate request to CA and save it to volatile or persistent storage.
                 * @param[in] request a valid certificate request that should be send to CA
                 * @param[in] toVolatile if this flag true then the request should be saved to the volatile (session) storage, otherwise to the persistent storage
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kInvalidArgument if the provided certification request is invalid
                 * @exception CryptoErrorDomain::kNoConnection if connection to the CA cannot be established
                 */
                virtual ara::core::Result<void> SendRequest (const CertSignRequest &request, bool toVolatile=true) noexcept=0;

                /** 
                 * @brief [SWS_CRYPT_40625]
                 * Set specified CA certificate as a "root of trust". Only a certificate saved to the volatile or
                 * persistent storage may be marked as the "root of trust"! Only CA certificate can be a "root of
                 * trust"! Multiple certificates on an ECU may be marked as the "root of trust". Only an application
                 * with permissions "Trust Master" has the right to call this method!
                 * @param[in] caCert a valid CA certificate that should be trusted
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kInvalidArgument if the provided certificate is invalid
                 * @exception CryptoErrorDomain::kIncompatibleObject if provided certificate doesn’t belong to a CA
                 * @exception CryptoErrorDomain::kAccessViolation if the method called by an application without the "Trust Master" permission
                 */
                virtual ara::core::Result<void> SetAsRootOfTrust (const Certificate &caCert) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40624]
                 * Set the "pending" status associated to the CSR that means that the CSR already sent to CA.
                 * This method do nothing if the CSR already marked as "pending". Only an application with
                 * permissions "CA Connector" has the right to call this method!
                 * @param request certificate signing request that should be marked as "pending"
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kAccessViolation if the method called by an application without the "CA Connector" permission
                 */
                virtual ara::core::Result<void> SetPendingStatus (const CertSignRequest &request) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40637]
                 * Get Certificate Revocation List (CRL) or Delta CRL via on-line connection. CRL Distribution
                 * Point (CRL DP) should be extracted from the provided CA certificate.
                 * @param[in] caCert valid CA certificate
                 * @return ara::core::Result<bool> true if the CRL was updated succesfully and false if there is no fresh updates
                 * @exception CryptoErrorDomain::kInvalidArgument if the provided certificate is invalid
                 * @exception CryptoErrorDomain::kNoConnection if the connection cannot be established
                 */
                virtual ara::core::Result<bool> UpdateCrlOnline (const Certificate &caCert) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40618]
                 * Verify status of the provided certificate by locally stored CA certificates and CRLs only. This
                 * method updates the Certificate::Status associated with the certificate.
                 * @param[in] cert target certificate for verification
                 * @param[in] myRoot root certificate to be used for verification - if this is nullptr, use machine root certificates
                 * @return Certificate::Status verification status of the provided certificate
                 */
                virtual Certificate::Status VerifyCert (Certificate &cert, Certificate::Uptr myRoot=nullptr) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40619]
                 * Verify status of the provided certification chain by locally stored CA certificates and CRLs only.
                 * Verification status of the certificate chain is Certificate::Status::kValid only if all certificates in
                 * the chain have such status! Certificates in the chain (presented by container vector) must be
                 * placed from the root CA certificate (zero index) to the target end-entity certificate (last used
                 * index of the vector). Verification is executed in same order. If the chain verification is failed then
                 * status of the first failed certificate is returned. This method updates the Certificate::Status
                 * associated with the certificates in the chain.
                 * @param[in] chain target certificate chain for verification
                 * @param[in] myRoot root certificate to be used for verification - if this is nullptr, use machine root certificates
                 * @return Certificate::Status verification status of the provided certificate chain
                 */
                virtual Certificate::Status VerifyCertChain (ara::core::Span< const Certificate::Uptr > chain, Certificate::Uptr myRoot=nullptr) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40914]
                 * Parse the custom X.509 extensions This method parses the extensions of the provided
                 * certificate and calls the corresponding callbacks of the provided customExtensionsParser for
                 * each parsed ASN.1 element. If any call to one of the callbacks returns an error, the parsing
                 * stops and returns kRuntimeFault. Parsing starts at the first extension of the certificate and
                 * parses all extensions of the certificate.
                 * @param[in] cert Certificate object to be parsed
                 * @param[in] customExtensionsParser Custom extensions parser that implements the callbacks
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault If parsing the extensions fails or calling one of the callback returns an error.
                 */
                virtual ara::core::Result<void> ParseCustomCertExtensions (const Certificate &cert, std::unique_ptr< X509CustomExtensionsParser > customExtensionsParser) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40915]
                 * Parse the custom X.509 extensions This method parses the extension identified by the
                 * provided oid of the provided certificate and calls the corresponding callbacks of the provided
                 * customExtensionsParser for each parsed ASN.1 element. If any call to one of the callbacks
                 * returns an error, the parsing stops and returns kRuntimeFault. Only the sequence of the
                 * extension identified by the oid is parsed.
                 * @param[in] cert Certificate object to be parsed
                 * @param[in] customExtensionsParser Custom extensions parser that implements the callbacks
                 * @param[in] oid extension object identifier
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault If parsing the extensions fails or calling one of the callback returns an error.
                 * @exception CryptoErrorDomain::kUnexpectedValue If the certificate doesn’t contain an extension with the provided Oid.
                 */
                virtual ara::core::Result<void> ParseCustomCertExtensions (const Certificate &cert, std::unique_ptr< X509CustomExtensionsParser > customExtensionsParser, X509CustomExtensionsParser::Oid oid) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40604]
                 * Destroy the X509Provider object
                 * 
                 */
                virtual ~X509Provider () noexcept=default;

                /**
                 * @brief [SWS_CRYPT_30226]
                 * Copy-assign another X509Provider to this instance.
                 * @param other the other instance
                 * @return X509Provider& *this, containing the contents of other
                 */
                X509Provider& operator= (const X509Provider &other)=default;

                /**
                 * @brief [SWS_CRYPT_30227]
                 * Move-assign another X509Provider to this instance.
                 * @param other the other instance
                 * @return X509Provider& *this, containing the contents of other
                 */
                X509Provider& operator= (const X509Provider &&other)/*=default*/;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_X509_PROVIDER_H