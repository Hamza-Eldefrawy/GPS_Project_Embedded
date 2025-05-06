#define SET_BIT(reg,bit)  (reg|=(1<<(bit)))
#define CLR_BIT(reg,bit)  (reg&=~(1<<(bit)))
#define TOGLE_BIT(reg,bit) (reg^=(1<<(bit)))
#define READ_BIT(reg,bit) ((reg&(1<<(bit)))>>(bit))
