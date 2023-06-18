module Conversions where

import Polynomes

-- Binaire vers hexadécimal

polyGF28ToHexa :: GF2_8 -> String
polyGF28ToHexa poly = ((hexDigit . binToDec) hex2) ++ ((hexDigit . binToDec) hex1)
  where
    hex1 = take 4 p
    hex2 = take 4 (drop 4 p)
    (PCC p) = fillRight0 poly
    binToDec [Z2Z a, Z2Z b, Z2Z c, Z2Z d] = a + 2*b + 4*c + 8*d 
    hexDigit n | n < 10 = show n
               | otherwise = case n of
                  10 -> "a"
                  11 -> "b"
                  12 -> "c"
                  13 -> "d"
                  14 -> "e"
                  15 -> "f"


polyCoefGF28ToHexa :: PolyCoefGF2_8 -> String
polyCoefGF28ToHexa (PCGF28 (PCC p)) = concatMap polyGF28ToHexa p

polyListGF28ToHexa :: [GF2_8] -> String
polyListGF28ToHexa p = concatMap polyGF28ToHexa p

-- Hexadécimal vers binaire

hexaToPolyGF28 :: String -> GF2_8
hexaToPolyGF28 s = PCC $ (hexToBin a) ++ (hexToBin b)
              where
                (a, b) = (last s, head s)
                hexToBin '0' = [Z2Z 0, Z2Z 0, Z2Z 0, Z2Z 0]
                hexToBin '1' = [Z2Z 1, Z2Z 0, Z2Z 0, Z2Z 0]
                hexToBin '2' = [Z2Z 0, Z2Z 1, Z2Z 0, Z2Z 0]
                hexToBin '3' = [Z2Z 1, Z2Z 1, Z2Z 0, Z2Z 0]
                hexToBin '4' = [Z2Z 0, Z2Z 0, Z2Z 1, Z2Z 0]
                hexToBin '5' = [Z2Z 1, Z2Z 0, Z2Z 1, Z2Z 0]
                hexToBin '6' = [Z2Z 0, Z2Z 1, Z2Z 1, Z2Z 0]
                hexToBin '7' = [Z2Z 1, Z2Z 1, Z2Z 1, Z2Z 0]
                hexToBin '8' = [Z2Z 0, Z2Z 0, Z2Z 0, Z2Z 1]
                hexToBin '9' = [Z2Z 1, Z2Z 0, Z2Z 0, Z2Z 1]
                hexToBin 'a' = [Z2Z 0, Z2Z 1, Z2Z 0, Z2Z 1]
                hexToBin 'b' = [Z2Z 1, Z2Z 1, Z2Z 0, Z2Z 1]
                hexToBin 'c' = [Z2Z 0, Z2Z 0, Z2Z 1, Z2Z 1]
                hexToBin 'd' = [Z2Z 1, Z2Z 0, Z2Z 1, Z2Z 1]
                hexToBin 'e' = [Z2Z 0, Z2Z 1, Z2Z 1, Z2Z 1]
                hexToBin 'f' = [Z2Z 1, Z2Z 1, Z2Z 1, Z2Z 1]

-- fonction qui prend en entrée des chaines de 8 caractères
hexaToPolyCoefGF28 :: String -> PolyCoefGF2_8
hexaToPolyCoefGF28 s = PCGF28 $ PCC $ hexaToPolyCoef s
            where
              hexaToPolyCoef [] = []
              hexaToPolyCoef (a:b:r) = (hexaToPolyGF28 [a, b]) : (hexaToPolyCoef r)

hexaToPolyListGF28 :: String -> [GF2_8]
hexaToPolyListGF28 s = hexaToPolyList s
            where
              hexaToPolyList [] = []
              hexaToPolyList (a:b:r) = (hexaToPolyGF28 [a, b]) : (hexaToPolyList r)