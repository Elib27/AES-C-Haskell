import AES
import Conversions

box :: [String]
box = [toHex a b | a <- [0..15], b <- [0..15]]
  where toHex :: Int -> Int -> String
        toHex a b = [hexaChars !! a] ++ [hexaChars !! b]
        hexaChars = "0123456789abcdef"

sBox :: [String]
sBox = map (polyGF28ToHexa . subByte . hexaToPolyGF28) box

formatedSBox :: String
formatedSBox = concatMap (\x -> "0x" ++ x ++ ", ") sBox

rsBox :: [String]
rsBox = map (polyGF28ToHexa . invSubByte . hexaToPolyGF28) box

formatedRSBox :: String
formatedRSBox = concatMap (\x -> "0x" ++ x ++ ", ") rsBox

-- utiliser formatedSbox et formatedRSBox pour remplir les tableaux SBOX et RSBOX dans AES.c