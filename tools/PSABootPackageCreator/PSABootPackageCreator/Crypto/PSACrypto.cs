using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

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

    public class RSA
    {
        public enum KeySize{ None = 0, Key1024 = 128, Key2048 = 256, Key4096 = 512 };

        KeySize keySize = KeySize.None;

        public RSA(KeySize keySize, byte[] privateKey)
        {
            if (privateKey.Length != (int)keySize)
            {
                throw new Exception("Invalid Private Key");
            }
            this.keySize = keySize;
        }

        public byte[] Sign(byte[] data)
        {
            /* Remove the below line once you return a proper signature */
            return new byte[(int)this.keySize];
        }
    }
}
