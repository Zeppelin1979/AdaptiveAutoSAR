namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23200]
             * A private key context for asymmetric signature calculation and short message encoding
             * (RSA-like). Restricted groups of trusted subscribers can use this primitive for simultaneous
             * provisioning of confidentiality, authenticity and non-repudiation of short messages, if the public
             * key is generated appropriately and kept in secret.
             */
            class SigEncodePrivateCtx : public CryptoContext {...};
        }
    }
}