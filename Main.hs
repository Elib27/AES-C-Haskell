import AES

aesEncryption :: String -> Int -> Key -> Input -> Output
aesEncryption "c" keySize key input = aesCipher keySize key input
aesEncryption "i" keySize key input = aesInvCipher keySize key input
aesEncryption _ _ _ _ = error "Invalid cipher type"

aesCipher :: Int -> Key -> Input -> Output
aesCipher 128 key input = aes128Cipher key input
aesCipher 192 key input = aes192Cipher key input
aesCipher 256 key input = aes256Cipher key input
aesCipher _ _ _ = error "Invalid key size"

aesInvCipher :: Int -> Key -> Input -> Output
aesInvCipher 128 key input = aes128InvCipher key input
aesInvCipher 192 key input = aes192InvCipher key input
aesInvCipher 256 key input = aes256InvCipher key input
aesInvCipher _ _ _ = error "Invalid key size"

main = do
  putStrLn "cipher or inverse cipher ? (c/i)"
  cipherType <- getLine
  putStrLn "Enter the key size (128, 192 or 256 bits): "
  keySize <- readLn
  putStrLn "Enter the key : "
  key <- getLine
  putStrLn "Enter the plaintext : "
  plaintext <- getLine
  if cipherType == "c" then putStrLn "Ciphered text : " else putStrLn "Deciphered text : "
  let cipheredText = aesEncryption cipherType keySize (hexaToKey key) (hexaToInput plaintext)
  putStrLn $ outputToHexa $ cipheredText