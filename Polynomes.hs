module Polynomes where

import Structures

------------------------------------------------------------
-- Implémentation du corps à 2 éléments F2 = GF(2) = Z/2Z --
------------------------------------------------------------

newtype Zsur2Z = Z2Z Integer deriving (Show, Eq)

plusMod2 :: Zsur2Z -> Zsur2Z -> Zsur2Z
plusMod2 (Z2Z x) (Z2Z y) = Z2Z $ (x + y) `mod` 2

croixMod2 :: Zsur2Z -> Zsur2Z -> Zsur2Z
croixMod2 (Z2Z x) (Z2Z y) = Z2Z (x * y)

opposeMod2 :: Zsur2Z -> Zsur2Z
opposeMod2 x = x

inverseMod2 :: Zsur2Z -> Zsur2Z
inverseMod2 x = x              -- Pas d'inverse pour 0 => renvoie 0

instance Anneau Zsur2Z where
  unit_a = Z2Z 0
  unit_m = Z2Z 1
  plus = plusMod2
  croix = croixMod2
  oppose = opposeMod2

instance Corps Zsur2Z where
  inverse = inverseMod2

--------------------------------------------------------------------
-- Implémentation de l'anneau des polynômes à coefficient dans F2 --
--------------------------------------------------------------------

-- l'exposant le plus élevé du polymnôme se trouve en fin de liste (ex : X^2 = [Z2Z 0, Z2Z 0, Z2Z 1])

newtype PolyCoefCorps a = PCC [a] deriving (Show, Eq) 

plusPCC :: Anneau a => PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a
plusPCC (PCC p1) (PCC p2) = PCC $ comblists plus p1 p2

comblists :: (a -> a -> a) -> [a] -> [a] -> [a]
comblists f [] xs = xs
comblists f xs [] = xs
comblists f (x1:xs1) (x2:xs2) = (f x1 x2):(comblists f xs1 xs2)

croixPCC :: Anneau a => PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a
croixPCC (PCC []) _ = unit_a
croixPCC (PCC (x:x1s)) (PCC p2) = plusPCC (PCC (map (croix x) p2)) (croixPCC (PCC x1s) (foisX (PCC p2)))
              where foisX (PCC xs) = PCC $ unit_a:xs

opposePCC :: Anneau a => PolyCoefCorps a -> PolyCoefCorps a
opposePCC p = p

instance Anneau a => Anneau (PolyCoefCorps a) where
  unit_a = PCC [unit_a]
  unit_m = PCC [unit_m]
  plus = plusPCC
  croix = croixPCC
  oppose = opposePCC

-----------------------------
-- Implémentation de GF2^8 --
-----------------------------

shiftPoly :: Anneau a => PolyCoefCorps a -> Int -> PolyCoefCorps a
shiftPoly (PCC p) n = PCC $ replicate n unit_a ++ p

removeRight0 :: (Anneau a, Eq a) => PolyCoefCorps a -> PolyCoefCorps a
removeRight0 (PCC p) = PCC $ reverse $ p_safe
                  where 
                    p_safe | p_without_zeros == [] = [unit_a]
                           | otherwise = p_without_zeros
                    p_without_zeros = dropWhile (== unit_a) (reverse p)

fillRight0 :: Anneau a => PolyCoefCorps a -> PolyCoefCorps a
fillRight0 (PCC p) = PCC $ p ++ (replicate n unit_a)
                  where n = 8 - length p

deg :: (Anneau a, Eq a) => PolyCoefCorps a -> Int
deg p | p == unit_a = 0
      | otherwise = length $ p_without_zeros
    where
      (PCC p_without_zeros) = removeRight0 p

modPoly :: (Anneau a, Eq a) => PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a
modPoly p1 p2 | p1 == unit_a = unit_a
              | p2 == unit_a = p1
              | deg p1 < deg p2 = p1
              | otherwise = modPoly (removeRight0 (plus p1 (shiftPoly p2 ((deg p1) - (deg p2))))) p2

plusModPoly :: (Anneau a, Eq a) => PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a
plusModPoly p1 p2 pMod = modPoly (plus p1 p2) pMod

foisModPoly :: (Anneau a, Eq a) => PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a
foisModPoly p1 p2 pMod = modPoly (croix p1 p2) pMod

-- avec deg p < 8 et p non nul
inverseModPoly :: (Anneau a, Eq a) => PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a
inverseModPoly p pMod = modPoly a pMod
                      where (_, a) = eucliEtendu pMod p unit_a unit_m unit_m unit_a

-- fonction auxiliaire de l'inverse modulo un polynôme permettant de calculer a(x) et c(x) dans b(x)a(x) + m(x)c(x) = 1 avec l'algorithme d'Euclide étendu
eucliEtendu :: (Anneau a, Eq a) => PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a -> PolyCoefCorps a -> (PolyCoefCorps a, PolyCoefCorps a)
eucliEtendu (PCC p1) (PCC p2) c oc a oa | (PCC p2) == unit_m = (c, a)
                                        | otherwise = eucliEtendu (PCC p2) (removeRight0 (plusPCC (PCC p1) (shiftPoly (PCC p2) (len_p1 - len_p2)))) new_c c new_a a
                                      where new_a = removeRight0 $ plusPCC oa (croixPCC coef a)
                                            new_c = removeRight0 $ plusPCC oc (croixPCC coef c)
                                            coef = shiftPoly unit_m (len_p1 - len_p2)
                                            len_p1 = length p1
                                            len_p2 = length p2

-- On utilise le type générique PolyCoefCorps a créé précédement pour le type GF2_8
type GF2_8 = PolyCoefCorps Zsur2Z

polyM = PCC [Z2Z 1, Z2Z 1, Z2Z 0, Z2Z 1, Z2Z 1, Z2Z 0, Z2Z 0, Z2Z 0, Z2Z 1]

plusGF2_8 :: GF2_8 -> GF2_8 -> GF2_8
plusGF2_8 p1 p2 = plusModPoly p1 p2 polyM

croixGF2_8 :: GF2_8 -> GF2_8 -> GF2_8
croixGF2_8 p1 p2 = foisModPoly p1 p2 polyM

inverseGF2_8 :: GF2_8 -> GF2_8
inverseGF2_8 (PCC [Z2Z 0]) = PCC [Z2Z 0]
inverseGF2_8 p = inverseModPoly p polyM

opposeGF2_8 :: GF2_8 -> GF2_8
opposeGF2_8 p = p

-----------------------------------------------------------
-- Implémentation des polynomes à coeficients dans GF2^8 --
-----------------------------------------------------------

data PolyCoefGF2_8 =  PCGF28 (PolyCoefCorps GF2_8) deriving (Show)

plusPC2_8 :: PolyCoefGF2_8 -> PolyCoefGF2_8 -> PolyCoefGF2_8
plusPC2_8 (PCGF28 p1) (PCGF28 p2) = PCGF28 $ plus p1 p2

croixPC2_8 :: PolyCoefGF2_8 -> PolyCoefGF2_8 -> PolyCoefGF2_8
croixPC2_8 (PCGF28 (PCC [a0, a1, a2, a3])) (PCGF28 (PCC [b0, b1, b2, b3])) = PCGF28 $ PCC [d0, d1, d2, d3]
                    where d0 = removeRight0 $ plusGF2_8 (croixGF2_8 a0 b0) $ plusGF2_8 (croixGF2_8 a3 b1) $ plusGF2_8 (croixGF2_8 a2 b2) (croixGF2_8 a1 b3)
                          d1 = removeRight0 $ plusGF2_8 (croixGF2_8 a1 b0) $ plusGF2_8 (croixGF2_8 a0 b1) $ plusGF2_8 (croixGF2_8 a3 b2) (croixGF2_8 a2 b3)
                          d2 = removeRight0 $ plusGF2_8 (croixGF2_8 a2 b0) $ plusGF2_8 (croixGF2_8 a1 b1) $ plusGF2_8 (croixGF2_8 a0 b2) (croixGF2_8 a3 b3)
                          d3 = removeRight0 $ plusGF2_8 (croixGF2_8 a3 b0) $ plusGF2_8 (croixGF2_8 a2 b1) $ plusGF2_8 (croixGF2_8 a1 b2) (croixGF2_8 a0 b3)

opposePC2_8 :: PolyCoefGF2_8 -> PolyCoefGF2_8
opposePC2_8 p = p

instance Anneau PolyCoefGF2_8 where
  unit_a = PCGF28 $ PCC [unit_a]
  unit_m = PCGF28 $ PCC [unit_a]
  plus = plusPC2_8
  croix = croixPC2_8
  oppose = opposePC2_8