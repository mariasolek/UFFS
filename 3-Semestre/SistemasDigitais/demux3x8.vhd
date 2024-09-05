library ieee;
use ieee.std_logic_1164.all;

entity decoder_3to8 is
    port (
    A : in std_logic_vector (2 downto 0); 
    Y : out std_logic_vector (7 downto 0)
    );
   end entity decoder_3to8;

architecture decod of decoder_3to8 is
    begin 
y(0) <= not (a(0)) and not (a(1)) and not (a(2));
y(1) <= not (a(0)) and not (a(1)) and (a(2));
y(2) <= not (a(0)) and (a(1)) and not (a(2));
y(3) <= not (a(0)) and (a(1)) and (a(2));
y(4) <= (a(0)) and not (a(1)) and not (a(2));
y(5) <= (a(0)) and not (a(1)) and (a(2));
y(6) <= (a(0)) and (a(1)) and not (a(2));
y(7) <= (a(0)) and(a(1)) and(a(2));
    end decod;