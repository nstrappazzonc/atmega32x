void LCDInit(void);
void LCDLatch(void);
void LCDCmd(uint8_t cmd);
void LCDClear(void);
void LCDChar(uint8_t data);
void LCDCreateCustomChar(uint8_t x, uint8_t y, uint8_t n, unsigned char *ptr);
void LCDPrint(char *str);
void LCDSetCursor(uint8_t x, uint8_t y);
void LCDClear(void);
