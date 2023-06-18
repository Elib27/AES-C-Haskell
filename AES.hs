module AES where
import Data.List
import Polynomes
import Conversions

newtype State = State [PolyCoefGF2_8] deriving Show
type Input = [GF2_8]
type Output = [GF2_8]
type Key = [GF2_8]
type KeySchedule = [PolyCoefGF2_8]
type WordKey = PolyCoefGF2_8

-----------------
-- Conversions --
-----------------

inputToState :: Input -> State
inputToState ps = State $ [PCGF28 $ PCC (take 4 ps)] ++ [PCGF28 $ PCC $ take 4 (drop 4 ps)] ++ [PCGF28 $ PCC $ take 4 (drop 8 ps)] ++ [PCGF28 $ PCC $ take 4 (drop 12 ps)]

stateToOutput :: State -> Output
stateToOutput (State ps) = concatMap polyCoefGF28ToArray ps
                    where polyCoefGF28ToArray (PCGF28 (PCC p)) = p

stateToHexa :: State -> [String]
stateToHexa (State ps) = map polyCoefGF28ToHexa ps

hexaToState :: [String] -> State
hexaToState s = State $ map hexaToPolyCoefGF28 s

hexaToInput :: String -> Input
hexaToInput s = hexaToPolyListGF28 s

hexaToKey :: String -> Key
hexaToKey s = hexaToPolyListGF28 s

outputToHexa :: Output-> String
outputToHexa s = polyListGF28ToHexa s

stateToBiArray :: State -> [[GF2_8]]
stateToBiArray (State ps) = map polyCoefGF28ToArray ps
                    where polyCoefGF28ToArray (PCGF28 (PCC p)) = p

biArrayToState :: [[GF2_8]] -> State
biArrayToState ps = State $ [PCGF28 $ PCC (ps!!0)] ++ [PCGF28 $ PCC $ (ps!!1)] ++ [PCGF28 $ PCC $ (ps!!2)] ++ [PCGF28 $ PCC $ (ps!!3)]

----------------------------------
-- Implémentation de addRoundKey--
----------------------------------

addRoundKey :: KeySchedule -> State -> State
addRoundKey key (State st) = State $ zipWith plusPC2_8 key st

-----------------------------------------------
-- Implémentation de SubBytes et invSubBytes --
-----------------------------------------------

subBytes :: State -> State
subBytes st = biArrayToState $ map (map subByte) (stateToBiArray st)

subByte :: GF2_8 -> GF2_8
subByte p = (removeRight0 . (subByteAffineTrans 0) . fillRight0 . inverseGF2_8 . removeRight0) p

-- fonction auxiliaire de subBytes tranformant un octet (GF2^8)
-- reçoit un octet complet (avec zéros inutiles)
subByteAffineTrans ::  Int -> GF2_8 -> GF2_8
subByteAffineTrans i (PCC o) | i == 8 = PCC [Z2Z 0]
                             | otherwise = plusPCC (shiftPoly (PCC [b']) i) (subByteAffineTrans (i+1) (PCC o))
                        where
                          b' = plusMod2 (o!!i) $ plusMod2 (o!!(mod (i+4) 8)) $ plusMod2 (o!!(mod (i+5) 8)) $ plusMod2 (o!!(mod (i+6) 8)) $ plusMod2 (o!!(mod (i+7) 8)) (c!!i)
                          c = [Z2Z 1, Z2Z 1, Z2Z 0, Z2Z 0, Z2Z 0, Z2Z 1, Z2Z 1, Z2Z 0]

invSubBytes :: State -> State
invSubBytes st = biArrayToState $ map (map invSubByte) (stateToBiArray st)

invSubByte :: GF2_8 -> GF2_8
invSubByte p = (inverseGF2_8 . removeRight0 . (invSubByteAffineTrans 0) . fillRight0) p

invSubByteAffineTrans ::  Int -> GF2_8 -> GF2_8
invSubByteAffineTrans i (PCC o) | i == 8 = PCC [Z2Z 0]
                                | otherwise = plusPCC (shiftPoly (PCC [b']) i) (invSubByteAffineTrans (i+1) (PCC o))
                        where
                          b' = plusMod2 (o!!(mod (i+2) 8)) $ plusMod2 (o!!(mod (i+5) 8)) $ plusMod2 (o!!(mod (i+7) 8)) (c!!i)
                          c = [Z2Z 1, Z2Z 0, Z2Z 1, Z2Z 0, Z2Z 0, Z2Z 0, Z2Z 0, Z2Z 0]

-------------------------------------------------
-- Implémentation de ShiftRows et invShiftRows --
-------------------------------------------------

shiftRows :: State -> State
shiftRows st = biArrayToState $ transpose $ map shiftRow (zip [0..] $ transpose stBiArr)
  where
    stBiArr = stateToBiArray st
    shiftRow (r, row) = drop r row ++ take r row

invShiftRows :: State -> State
invShiftRows st = biArrayToState $ transpose $ map shiftRow (zip [0..] $ transpose stBiArr)
  where
    stBiArr = stateToBiArray st
    shiftRow (r, row) = reverse $ drop r (reverse row) ++ take r (reverse row)

---------------------------------------------------
-- Implémentation de MixColumns et invMixColumns --
---------------------------------------------------

mixColumns :: State -> State
mixColumns (State s) = State $ map mixColumn s

mixColumn :: PolyCoefGF2_8 -> PolyCoefGF2_8
mixColumn c = croixPC2_8 poly_A c
          where
            poly_A = PCGF28 $ PCC [PCC [Z2Z 0, Z2Z 1], PCC [Z2Z 1], PCC [Z2Z 1], PCC [Z2Z 1, Z2Z 1]]

invMixColumns :: State -> State
invMixColumns (State s) = State $ map invMixColumn s

invMixColumn :: PolyCoefGF2_8 -> PolyCoefGF2_8
invMixColumn c = croixPC2_8 poly_Amoins1 c
          where
            poly_Amoins1 = PCGF28 $ PCC [PCC [Z2Z 0, Z2Z 1, Z2Z 1, Z2Z 1], PCC [Z2Z 1, Z2Z 0, Z2Z 0, Z2Z 1], PCC [Z2Z 1, Z2Z 0, Z2Z 1, Z2Z 1], PCC [Z2Z 1, Z2Z 1, Z2Z 0, Z2Z 1]]

------------------------------------------------------------
-- Implémentation de rotWord et subWord pour keyExpansion --
------------------------------------------------------------

rotWord :: WordKey -> WordKey
rotWord (PCGF28 (PCC w)) = PCGF28 $ PCC $ tail w ++ [head w]

subWord :: WordKey -> WordKey
subWord (PCGF28 (PCC w)) = PCGF28 $ PCC $ map subByte w

------------------------------------
-- Implémentation de keyExpansion --
------------------------------------

keyToWords :: Key -> [WordKey]
keyToWords [] = []
keyToWords xs = (PCGF28 (PCC (take 4 xs))) : keyToWords (drop 4 xs)

keyExpansion :: Int -> Int -> Int -> Key -> KeySchedule
keyExpansion nk nb nr key = keyTrans nk (nb*(nr+1)) w
      where
        w = keyToWords key
        keyTrans i n ks | i == n = ks
                        | otherwise = keyTrans (i+1) n (ks ++ [plusPC2_8 (ks!!(i-nk)) temp])
              where
                temp | (mod i nk == 0) = plusPC2_8 ((subWord . rotWord) (ks!!(i-1))) rcon
                     | (nk > 6 && mod i nk == 4) = subWord (ks!!(i-1))
                     | otherwise = ks!!(i-1)
                rcon = PCGF28 $ PCC [powGF2_8 ((div i nk)-1) (PCC [Z2Z 0, Z2Z 1])]
                powGF2_8 0 (PCC p) = PCC [Z2Z 1]
                powGF2_8 n (PCC p) = croixGF2_8 (PCC p) (powGF2_8 (n-1) (PCC p))

------------------------------
-- Implémentation de Cipher --
------------------------------

-- Nr = 10 Nk = 4 Nb = 4  /// AES128
-- Nr = 12 Nk = 6 Nb = 4  /// AES192
-- Nr = 14 Nk = 8 Nb = 4  /// AES256

aes128Cipher :: Key -> Input -> Output
aes128Cipher key input = stateToOutput $ aesCipherState 10 keySchedule (addRoundKey keySchedule (inputToState input))
  where keySchedule = keyExpansion 4 4 10 key

aes192Cipher :: Key -> Input -> Output
aes192Cipher key input = stateToOutput $ aesCipherState 12 keySchedule (addRoundKey keySchedule (inputToState input))
  where keySchedule = keyExpansion 6 4 12 key

aes256Cipher :: Key -> Input -> Output
aes256Cipher key input = stateToOutput $ aesCipherState 14 keySchedule (addRoundKey keySchedule (inputToState input))
  where keySchedule = keyExpansion 8 4 14 key

aesCipherState :: Int -> KeySchedule -> State -> State
aesCipherState nr keySchedule st = lastRound (drop (nr*4) keySchedule) $ roundXtimes (nr-1) keySchedule st

aesRound :: KeySchedule -> State -> State
aesRound keySchedule st = ((addRoundKey keySchedule) . mixColumns . shiftRows . subBytes) st

roundXtimes :: Int -> KeySchedule -> State -> State
roundXtimes 0 _ st = st
roundXtimes n keySchedule st = roundXtimes (n-1) (drop 4 keySchedule) (aesRound (drop 4 keySchedule) st)

lastRound :: KeySchedule -> State -> State
lastRound keySchedule st = ((addRoundKey keySchedule) . shiftRows . subBytes) st

---------------------------------
-- Implémentation de invCipher --
---------------------------------

aes128InvCipher :: Key -> Input -> Output
aes128InvCipher key input = stateToOutput $ aesInvCipherState 10 keySchedule (addRoundKey keySchedule (inputToState input))
  where keySchedule = inverseKeySchedule $ keyExpansion 4 4 10 key

aes192InvCipher :: Key -> Input -> Output
aes192InvCipher key input = stateToOutput $ aesInvCipherState 12 keySchedule (addRoundKey keySchedule (inputToState input))
  where keySchedule = inverseKeySchedule $ keyExpansion 6 4 12 key

aes256InvCipher :: Key -> Input -> Output
aes256InvCipher key input = stateToOutput $ aesInvCipherState 14 keySchedule (addRoundKey keySchedule (inputToState input))
  where keySchedule = inverseKeySchedule $ keyExpansion 8 4 14 key

inverseKeySchedule :: KeySchedule -> KeySchedule
inverseKeySchedule keySchedule = concat $ reverse $ splitArrByFour keySchedule
  where
    splitArrByFour [] = []
    splitArrByFour xs | length xs >= 4 = take 4 xs : splitArrByFour (drop 4 xs)
                      | otherwise = [xs]

aesInvCipherState :: Int -> KeySchedule -> State -> State
aesInvCipherState nr keySchedule st = lastInvRound (drop (nr*4) keySchedule) $ invRoundXtimes (nr-1) keySchedule st

aesInvRound :: KeySchedule -> State -> State
aesInvRound keySchedule st = (invMixColumns . (addRoundKey keySchedule) . invSubBytes . invShiftRows) st

invRoundXtimes :: Int -> KeySchedule -> State -> State
invRoundXtimes 0 _ st = st
invRoundXtimes n keySchedule st = invRoundXtimes (n-1) (drop 4 keySchedule) (aesInvRound (drop 4 keySchedule) st)

lastInvRound :: KeySchedule -> State -> State
lastInvRound keySchedule st = ((addRoundKey keySchedule) . invSubBytes . invShiftRows) st
