library ieee;
use ieee.std_logic_1164.all;

entity demux_1to8_16b is
    port(
        A0 : out std_logic_vector (15 downto 0); --saídas
        A1 : out std_logic_vector (15 downto 0); 
        A2 : out std_logic_vector (15 downto 0); 
        A3 : out std_logic_vector (15 downto 0); 
        A4 : out std_logic_vector (15 downto 0); 
        A5 : out std_logic_vector (15 downto 0); 
        A6 : out std_logic_vector (15 downto 0); 
        A7 : out std_logic_vector (15 downto 0); 
        SEL : in std_logic_vector (2 downto 0); --seletor
        Y : in std_logic_vector (15 downto 0) --entrada
    );
    end entity demux_1to8_16b;

architecture comp of demux_1to8_16b is
    begin 
process(Y, SEL)
    begin
if (SEL = "000") then
    A0 <= Y;
elsif (SEL = "001") then 
    A1 <= Y;
elsif (SEL = "010") then
    A2 <= Y;
elsif (SEL = "011") then 
    A3 <= Y;
elsif (SEL = "100") then
    A4 <= Y;
elsif (SEL = "101") then 
    A5 <= Y;
elsif (SEL = "110") then 
    A6 <= Y;
elsif(SEL = "111") then 
    A7 <= Y;

end if;
end process;
end comp;
    
