library ieee;
use ieee.std_logic_1164.all;

entity decoder_2to4en is
    port (
    EN : in std_logic; -- Enable
    A : in std_logic_vector (1 downto 0); -- entrada
    Y_L : out std_logic_vector (3 downto 0) -- saída
    );
   end entity decoder_2to4en;

architecture decod of decoder_2to4en is
    begin
    process(EN, A)
    begin
if (EN = '1') then
    y_l(0) <= (EN) and not (a(0)) and not (a(1));
    y_l(1) <= (EN) and not (a(0)) and (a(1));
    y_l(2) <= (EN) and (a(0)) and not (a(1));
    y_l(3) <= (EN) and (a(0)) and (a(1));
end if;
end process;
    end decod;