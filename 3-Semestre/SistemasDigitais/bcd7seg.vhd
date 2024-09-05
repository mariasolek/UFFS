library ieee;
use ieee.std_logic_1164.all;

entity bcd7seg is
port (
	EN : in std_logic; -- Enable
	D : in std_logic_vector (3 downto 0); -- entrada
	S : out std_logic_vector (6 downto 0) -- saída
);
end entity bcd7seg;

architecture comp of bcd7seg is 
begin
	process (EN, D)

begin

	if (EN = '1') then 
			case D is  
				when "0000" => S <= "1111110";
				when "0001" => S <= "0110000";
				when "0010" => S <= "1101101";
				when "0011" => S <= "1111001";
				when "0100" => S <= "0110011";
				when "0101" => S <= "1011011";
				when "0110" => S <= "1011111";
				when "0111" => S <= "1110000";
				when "1000" => S <= "1111111";
				when "1001" => S <= "1111011";
				when "1010" => S <= "1110111";
				when "1011" => S <= "0011111";
				when "1100" => S <= "1001110";
				when "1101" => S <= "0111101";
				when "1110" => S <= "1001111";			
				when others => S <= "1000111";
		
			end case;
	end if;
	end process;
end comp;

