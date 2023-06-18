module Structures where

-- Définition de la classe Anneau

class Anneau a where
  unit_a :: a
  unit_m :: a
  oppose :: a -> a 
  plus :: a -> a -> a
  croix :: a -> a -> a

-- Définition de la classe Corps

class (Anneau a) => Corps a where
  inverse :: a -> a