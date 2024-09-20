--autores: Maria Clara Solek e A. Cardoso Siqueira
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity blackjack is 
    port(
        KEY: in std_logic_vector (3 downto 0); --clk, reset, 
        sw: in std_logic_vector (9 downto 0); -- 0 até 3 são cartas e 8 e 9 hit e stay, respectivamente
        ledR : out std_logic_vector (9 downto 0); -- leds vermelhos
        ledG : out std_logic_vector (7 downto 0); --leds verdes
        HEX0: out std_logic_vector (6 downto 0); --display 4 de 7 seg 
        HEX1: out std_logic_vector (6 downto 0); --display 3 de 7 seg
        HEX2: out std_logic_vector (6 downto 0); --display 2 de 7 seg
        HEX3: out std_logic_vector (6 downto 0) --display 1 de 7 seg
    );
end entity blackjack;

architecture comp of blackjack is

function seteSegmentos (carta: integer) return std_logic_vector is 
begin
    if(carta=0) then
        return "1000000";
    elsif(carta=1) then
        return "1111001";
    elsif(carta=2) then
        return "0100100";
    elsif(carta=3) then
        return "0110000";
    elsif(carta=4) then
        return "0011001";
    elsif(carta=5) then
        return "0010010";
    elsif(carta=6) then
        return "0000010";
    elsif(carta=7) then
        return "1111000";
    elsif(carta=8) then
        return "0000000";
    elsif(carta=9) then
        return "0010000";
    elsif(carta=10) then
        return "0001000";--imprime A
    elsif(carta=11) then
        return "0000011";--imprime B
    elsif(carta=12) then
        return "1000110";--imprime C
    elsif(carta=13) then
        return "0100001";--imprime D
	
    else
        return "1111111";
    end if;
end seteSegmentos;  

    TYPE Estado is (START, ESPERA, C1, C2, C3, C4, PLAYER, DEALER, ACUMULAP, ACUMULAD, COMPARA, GANHA, PERDE, EMPATE);
    SIGNAL K : Estado;
    SIGNAL somaP, somaD : integer range 0 to 32 := 0; 
    SIGNAL ultCarta : integer range 0 to 20;
    --lógica de mudança de estados
    begin
        process(KEY(0), KEY(1))
        variable flagP : boolean := false;
        variable flagD : boolean := false;
		variable cartavdd: integer range 0 to 20 := 0;
		variable carta : integer range 0 to 20 := 0;
        variable cartar : std_logic_vector(3 downto 0) := "0000";
        begin 
        if (KEY(1) = '0') then --aperta reset
            K <= START;
        elsif (KEY(0) 'EVENT AND KEY(0) = '0') then --aperta clk
		case K is
                    when START =>
			carta := 0;
			cartavdd := 0;
			ultCarta <= 0;
			somaD <= 0;
			somaP <= 0;
			K <= ESPERA;
							  
		when ESPERA =>
			cartar(0) := sw(0);
			cartar(1) := sw(1);
			cartar(2) := sw(2);
			cartar(3) := sw(3);
			carta := to_integer(unsigned(cartar));
			cartavdd := to_integer(unsigned(cartar));
			if (carta >= 10) then 
                            carta := 10;
                        elsif (carta = 1) then 
                            carta := 11;
                            flagP := true;
                        end if;
			ultCarta <= cartavdd;
			K <= C1;
							  
                when C1 => --1 player
			cartar(0) := sw(0);
			cartar(1) := sw(1);
			cartar(2) := sw(2);
			cartar(3) := sw(3);
			carta := to_integer(unsigned(cartar));
			cartavdd := to_integer(unsigned(cartar));
                        if (carta >= 10) then 
                            carta := 10;
                        elsif (carta = 1) then 
                            carta := 11;
                            flagP := true;
                        end if;
                        somaP <= carta;
			ultCarta <= cartavdd;
                        K <= C2;
								
                 when C2 => --1 dealer
			cartar(0) := sw(0);
			artar(1) := sw(1);
			cartar(2) := sw(2);
			cartar(3) := sw(3);
			carta := to_integer(unsigned(cartar));
			cartavdd := to_integer(unsigned(cartar));
                        if (carta >= 10) then 
                           carta := 10;
                        elsif (carta = 1) then 
                            carta := 11;
                            flagD := true;
                        end if;
                        somaD <= carta;
			ultCarta <= cartavdd;
                        K <= C3;
								
                 when C3 => -- 2 player
			cartar(0) := sw(0);
			cartar(1) := sw(1);
			cartar(2) := sw(2);
			cartar(3) := sw(3);
			carta := to_integer(unsigned(cartar));
			cartavdd := to_integer(unsigned(cartar));
                        if (carta >= 10) then 
                            carta := 10;
                        elsif (carta = 1) then 
                            carta := 11;
                            flagP := true; 
                        end if;
                        if (somaP + carta > 21) then --soma só pode ser 21 se a pessoa recebe 2 ais nesse caso
                            carta := carta - 10;
                        end if; 
                        somaP <= somaP + carta;
			ultCarta <= cartavdd;
                        K <= C4;
								
                  when C4 => --2 dealer
			cartar(0) := sw(0);
			cartar(1) := sw(1);
			cartar(2) := sw(2);
			cartar(3) := sw(3);
			carta := to_integer(unsigned(cartar));
			cartavdd := to_integer(unsigned(cartar));
                        if (carta >= 10) then 
                            carta := 10;
                        elsif (carta = 1) then --verifica ais
                            carta := 11;
                            flagD := true; --tem ais ! 
                        end if;
                        if (somaD + carta > 21) then --soma só pode ser 21 se a pessoa recebe 2 ais nesse caso
                            carta := carta - 10;
                        end if;
                        somaD <= somaD + carta;
			ultCarta <= cartavdd;
                        K <= PLAYER;
								
                    when PLAYER => 
			if (somaP > 21) then 
                            K <= PERDE;
			end if;
                        if (sw(8) = '1') then --HIT
                            K <= ACUMULAP;
                        elsif (sw(9) = '1') then --STAY
                            K <= DEALER;
                        end if;
			ultCarta <= cartavdd;

                    when ACUMULAP =>
                        cartar(0) := sw(0);
                        cartar(1) := sw(1);
                        cartar(2) := sw(2);
                        cartar(3) := sw(3);
                        carta := to_integer(unsigned(cartar));
			cartavdd := to_integer(unsigned(cartar));
                        if (carta >= 10) then 
                            carta := 10;
                        end if;
                        if (carta = 1 and flagP) then --se recebo um ais e ja tenho outro
                            carta := 1;
                        elsif (carta = 1 and not (flagP) and somaP + 11 < 21) then 
                            carta := 11;
                        end if;
                        somaP <= somaP + carta; 
                        if (somaP > 21) then 
                            K <= PERDE;
                        else
                            K <= PLAYER;
                        end if;
			ultcarta <= cartavdd;
								
                    when DEALER =>  
			if (somaD >= 17) then 
                            K <= COMPARA;
			else
			    K <= ACUMULAD;
			end if;
								
                    when ACUMULAD =>
                        if (somaD >= 17) then 
                            K <= COMPARA;
                        else 
                            K <= DEALER;
                        end if;
			cartar(0) := sw(0);
			cartar(1) := sw(1);
			cartar(2) := sw(2);
			cartar(3) := sw(3);
			carta := to_integer(unsigned(cartar));
			cartavdd := to_integer(unsigned(cartar)); --signal, que recebe a variável cartar, usado mais tarde para mostrar no display o número da carta
                        if (carta >= 10) then 
                            carta := 10;
                        end if;
                        if (carta = 1 and flagD) then 
                            carta := 1;
                        elsif (carta = 1 and not (flagD) and somaP + 11 > 21) then 
                            carta := 11;
                        end if;
                        somaD <= somaD + carta;
			ultcarta <= cartavdd;

                    when COMPARA =>
			if (somaD > 21) then 
			    K <= GANHA;
                        elsif (somaP = somaD) then 
                            K <= EMPATE;
                        elsif (somaD < somaP) then 
                            K <= GANHA;
                        elsif (somaD > somaP) then
                            K <= PERDE;
                        end if;
                    when EMPATE =>
                        K <= START;
                    when GANHA =>
                        K <= START;
                    when PERDE =>
                        K <= START;
                    end case;
                end if;
        end process;
    --lógica de saída
    process(K)
begin
    case K is 
        when START =>
            HEX0 <= "1111111";
            HEX1 <= "1111111";
            HEX2 <= "1111111";
            HEX3 <= "0010010";
	    ledG <= "00000000";
	    ledR <= "0000000001";
	 when ESPERA =>
	    HEX0 <= "1111111";
            HEX1 <= "1111111";
            HEX2 <= "1111111";
            HEX3 <= "0000110";
	    ledG <= "00000000";
	    ledR <= "1000000001";
        when C1 =>
            HEX0 <= seteSegmentos(ultcarta);
            HEX1 <= "1111111";
            HEX2 <= "1111001";
            HEX3 <= "1000110";
            ledG <= "00000000";
	    ledR <= "0000000010";
        when C2 =>
            HEX0 <= seteSegmentos(ultcarta);
            HEX1 <= "1111111";
            HEX2 <= "0100100";
            HEX3 <= "1000110";
	    ledG <= "00000000";
	    ledR <= "0000000100";
        when C3 =>
            HEX0 <= seteSegmentos(ultcarta);
            HEX1 <= "1111111";
            HEX2 <= "0110000";
            HEX3 <= "1000110";
            ledG <= "00000000";
	    ledR <= "0000001000";
        when C4 =>
            HEX0 <= seteSegmentos(ultcarta);
            HEX1 <= "1111111";
            HEX2 <= "0011001";
            HEX3 <= "1000110";
	    ledG <= "00000000";
	    ledR <= "0000010000";
        when PLAYER =>
            HEX0 <= seteSegmentos(somaP mod 10);
            HEX1 <= seteSegmentos(somaP / 10);
            HEX2 <= "1111111";
            HEX3 <= "0001100";
	    ledG <= "00000000";
	    ledR <= "0000100000";
        when DEALER =>
            HEX0 <= seteSegmentos(somaD mod 10);
            HEX1 <= seteSegmentos(somaD / 10);
            HEX2 <= "1111111";
            HEX3 <= "0100001";
	    ledG <= "00000000";
	    ledR <= "0001000000";
        when ACUMULAP => --dizer somas
            HEX0 <= seteSegmentos(ultcarta);
            HEX1 <= seteSegmentos(somaP mod 10);
            HEX2 <= seteSegmentos(somaP / 10);
            HEX3 <= "0001100";
	    ledG <= "00000000";
	    ledR <= "0010000000";
        when ACUMULAD =>
            HEX0 <= seteSegmentos(ultcarta);
            HEX1 <= seteSegmentos(somaD mod 10);
            HEX2 <= seteSegmentos(somaD / 10);
            HEX3 <= "0100001";
            ledG <= "00000000";
	    ledR <= "0100000000";
        when COMPARA =>
            HEX0 <= seteSegmentos(somaD mod 10);
            HEX1 <= seteSegmentos(somaD / 10);
            HEX2 <= seteSegmentos(somaP mod 10);
            HEX3 <= seteSegmentos(somaP / 10);
	    ledG <= "00000000";
	    ledR <= "1000000000";
        when GANHA => 
	    HEX0 <= "0001000";
            HEX1 <= "0001000";
            HEX2 <= "0000011";
            HEX3 <= "0000110";
            ledG <= "11111111";
	    ledR <= "0000000000";
        when PERDE =>
	    HEX0 <= "0000110";
            HEX1 <= "0010010";
            HEX2 <= "1000000";
            HEX3 <= "1000111";
            ledR <= "1111111111";
        when EMPATE =>
	    HEX0 <= "0111111";
            HEX1 <= "0111111";
            HEX2 <= "0111111";
            HEX3 <= "0111111";
            ledG <= "11111111";
            ledR <= "1111111111";
        end case;
     end process;
end architecture comp;
