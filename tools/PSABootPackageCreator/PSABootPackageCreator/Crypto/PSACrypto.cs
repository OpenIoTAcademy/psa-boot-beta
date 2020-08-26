using System;
using System.Collections.Generic;
using System.IO;
using System.Security.Cryptography;

namespace PSABootPackageCreator.Crypto
{
    public class AES
    {
        Aes aesAlg;
        byte[] key;

        public AES(byte[] key)
        {
            aesAlg = Aes.Create();
            aesAlg.GenerateIV();
            aesAlg.Mode = CipherMode.CBC;
            this.key = key;
            aesAlg.Key = this.key;
        }

        public byte[] IV
        {
            get
            {
                return aesAlg.IV;
            }
        }

        public byte[] Encrypt(byte[] plainData)
        {
            byte[] encrypted;

            var encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV);

            // Create the streams used for encryption. 
            using (var msEncrypt = new MemoryStream())
            {
                using (var csEncrypt = new CryptoStream(msEncrypt, encryptor, CryptoStreamMode.Write))
                {
                    using (var swEncrypt = new BinaryWriter(csEncrypt))
                    {
                        //Write all data to the stream.
                        swEncrypt.Write(plainData);
                    }
                    encrypted = msEncrypt.ToArray();
                }
            }

            return encrypted;
        }
    }

    public class ECC
    {
        public enum KeySize { None = 0, Key256 = 32, Key384 = 48, Key512 = 64 };

        KeySize keySize = KeySize.None;
        List<byte> signingKeyData = new List<byte>();
        static readonly byte[] NIST_PRIVATE_KEY_PREFIX = { 0x45, 0x43, 0x53, 0x32, 0x20, 0x00, 0x00, 0x00 };
        static readonly byte[] NIST_PUBLIC_KEY_PREFIX = { 0x45, 0x43, 0x53, 0x31, 0x20, 0x00, 0x00, 0x00 };

        public ECC(KeySize keySize, byte[] signingKey)
        {
            /* ECC : 2 Key Len for Public + 1 Key Len for Private */
            int expectedLength = ((int)keySize * 3);
            if (signingKey.Length != (int)expectedLength)
            {
                throw new Exception("Invalid Private Key");
            }

            this.keySize = keySize;
            this.signingKeyData.AddRange(NIST_PRIVATE_KEY_PREFIX);
            this.signingKeyData.AddRange(signingKey);
        }

        public byte[] Sign(byte[] data)
        {
            /* Import the signing key */
            CngKey signingKey = CngKey.Import(this.signingKeyData.ToArray(), CngKeyBlobFormat.EccPrivateBlob);

            ECDsaCng dsa = new ECDsaCng(signingKey); //dsa = Digital Signature Algorithm

            /* Get the signature of the data using the imported key */
            byte[] signature = dsa.SignData(data);

            // Verify for test purposes
            // bool verified = veriftSignature(data, signature);

            /* Return the signature */
            return signature;
        }

        private bool veriftSignature(byte[] data, byte[] signature)
        {
            /* 
             * CngKey expect the public key in NIST format, so prepare it before import
             */
            byte[] publicKey = new byte[64 + 8];
            Array.Copy(NIST_PUBLIC_KEY_PREFIX, 0, publicKey, 0, 8);
            Array.Copy(signingKeyData.ToArray(), 8, publicKey, 8, 64);

            /* Import the public key for verify */
            CngKey verifyKey = CngKey.Import(publicKey, CngKeyBlobFormat.EccPublicBlob);

            using (ECDsaCng dsa = new ECDsaCng(verifyKey))
            {
                return dsa.VerifyData(data, signature);
            }
        }
    }
}
