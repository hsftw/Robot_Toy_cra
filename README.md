# Robot_Toy_cra

藍芽遙控小車  

超音波測距HC-SR04  
Tr : 18(D12)  
Ec : 19(D13)  
Vcc   
Gnd   

L298N控制板  
E1 : 5(D3)  
N1 : 11(D5)   
N2 : 12(D6)   
N3 : 15(D9)   
N4 : 16(D10)    
E2 : 17(D11)    

藍芽HC-06   
Rx : 4(D2)  
Tx : 6(D4)  
Vcc   
Gnd   

伺服馬達SG90    
Gnd   
Vcc   
Ser : 14(D8)  

Vin- 18650  
Vin+ 18650  
Vin+ to L298N&LM259 

PCBA腳位  

      Tr    Ec  Vcc  Gnd  E1   N1    N2   N3   N4   E2
     (D12) (D13) +5V     (D3) (D5) (D6) (D9) (D10) (D11)
     __|____|____|____|____|____|____|____|____|____|__
    |__________________________________________________|
       |    |    |    |    |    |    |    |    |    |
     (D2)  (D4) +5V            +5V  (D8)   18650
      Rx  Tx   Vcc  Gnd  Gnd  Vcc  Ser  Vin- Vin+ Vin+

大燈 A0       
倒車 A1       
左方 A2       
右方 A3       
煞車 A4       
     
