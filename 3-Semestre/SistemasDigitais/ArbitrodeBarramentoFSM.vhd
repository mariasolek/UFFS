--Autores: Maria Clara Solek e A. Cardoso Siqueira
library ieee;
USE ieee.std_logic_1164.all ;

entity barramento is 
    port(
        KEY: in std_logic_vector (3 downto 0);
        sw : in std_logic_vector (9 downto 0);
        ledR : out std_logic_vector (9 downto 0)
    );
end entity barramento;

architecture comp of barramento is
    TYPE Estado is (I, L0, L1, L2, L3);
    SIGNAL K : Estado;
    begin
        process(KEY(0), KEY(1))
        begin 
        if (KEY(1) = '0') then
            K <= I;
        elsif (KEY(0) 'EVENT AND KEY(0) = '0') then
				case K is
					when I =>
						if (sw(3) = '1') then 
							K <= L3;
						end if;
						if (sw(2) = '1') then 
							K <= L2;
						end if;
						if (sw(1) = '1') then 
							K <= L1;
						end if;
						if (sw(0) = '1') then 
							K <= L0;
						end if;
					when L0 =>
						if (sw(0)= '0') then 
							K <= I;
						end if;
					when L1 =>
						if (sw(1) = '0' or sw(0) = '1') then
							K <= I;
						end if;
					when L2 =>
						if (sw(2) = '0' or sw(1) = '1' or sw(0) = '1') then 
							K <= I;
						end if;
					when L3 =>
						if (sw(3) = '0' or sw(2) = '1' or sw(1) = '1' or sw(0) = '1') then 
							K <= I;
						end if;
				end case;
        end if;
    end process;
	 
   process(K)
	begin 
		case K is 
			when L3 =>
				ledR <= "0000001000";
			when L2 =>
				ledR <= "0000000100";
			when L1 =>
				ledR <= "0000000010";
			when L0 =>
				ledR <= "0000000001";
			when I =>
				ledR <= "0000000000";
		end case;
	end process;
end architecture comp;        