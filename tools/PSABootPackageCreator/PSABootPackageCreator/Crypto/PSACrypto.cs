using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
using System.Text;
using System.Windows.Forms;

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

        public enum KeySize { None = 0, Key1024 = 128, Key2048 = 256, Key4096 = 512 };

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

            CngKeyCreationParameters keyCreationParameters = new CngKeyCreationParameters();
            keyCreationParameters.ExportPolicy = CngExportPolicies.AllowPlaintextExport;
            keyCreationParameters.KeyUsage = CngKeyUsages.Signing;

            CngKey key = CngKey.Create(CngAlgorithm.ECDsaP256, null, keyCreationParameters);

            ECDsaCng dsa = new ECDsaCng(key); //dsa = Digital Signature Algorithm
            byte[] privateKey = dsa.Key.Export(CngKeyBlobFormat.EccPrivateBlob);
           
            CngKey importedKey = CngKey.Import(privateKey, CngKeyBlobFormat.EccPrivateBlob);
            ECDsaCng importedDSA = new ECDsaCng(importedKey); //dsa = Digital Signature Algorithm
            byte[] signed = dsa.SignData(data);
            return signed;
            
        }

        
        public void VerifySign(byte[] data, byte[] signed)
        {
            CngKeyCreationParameters keyCreationParameters = new CngKeyCreationParameters();
            keyCreationParameters.ExportPolicy = CngExportPolicies.AllowPlaintextExport;
            keyCreationParameters.KeyUsage = CngKeyUsages.AllUsages;
            CngKey key = CngKey.Create(CngAlgorithm.ECDsaP256, null, keyCreationParameters);

            ECDsaCng dsa = new ECDsaCng(key); //dsa = Digital Signature Algorithm
            
            byte[] publicKey = dsa.Key.Export(CngKeyBlobFormat.EccPublicBlob);

            using (ECDsaCng ecsdKey = new ECDsaCng(CngKey.Import(publicKey, CngKeyBlobFormat.EccPublicBlob)))
            {
                if (ecsdKey.VerifyData(data, signed))
                    MessageBox.Show("Data is good");
                else
                    MessageBox.Show("Data is bad");
            }
        }

    }
}

    

   
