#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 

void Write(String tekst){
  u8g.firstPage();
  do{
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr( 0, 22, tekst.c_str());
  }while(u8g.nextPage());
}

