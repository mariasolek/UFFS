library ieee;
USE ieee.std_logic_1164.all ;

entity contador_mod5 is
    port(
        CLK, RESET, S: in std_logic;
        X: out std_logic_vector (3 downto 0)
    );
end contador_mod5;

architecture comp of contador_mod5 is 
    TYPE Estado is (Q0, Q1, Q2, Q3, Q4);
    SIGNAL Y: Estado
    begin
        process(CLK, RESET)
        begin 
        if (RESET = '1') then
            Y <= Q0;
        elsif (Clock 'EVENT AND Clock = '1') then
            case Y is 
                when Q0 =>
                    if (S = '0') then
                        Y <= Q1;
                    else 
                        Y <= Q4;
                when Q1 =>
                    if (S = '0') then
                        Y <= Q2;
                    else 
                        Y <= Q0;
                when Q2 =>
                    if (S = '0') then 
                        Y <= Q3;
                    else 
                        Y <= Q1;
                when Q3 => 
                    if (S = '0') then 
                        Y <= Q4;
                    else 
                        Y <= Q2;
                when Q4 => 
                    if (S = '0') then 
                        Y <= Q0;
                    else 
                        Y <= Q3;
        end if;
    end process;
    
    process(Y)
    begin 
    case X is 
        when Q0 =>
            X <= "000";
        when Q1 =>
            X <= "001";
        when Q2 =>
            X <= "010";
        when Q3 =>
            X <= "011";
        when Q4 =>
            X <= "100";
    end case;
    end process;
end comp;
