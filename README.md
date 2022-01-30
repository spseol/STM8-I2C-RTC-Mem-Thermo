STM8 a software I2C
====================

* RTC DS3231
* teploměr LM75A ![](https://github.com/hpaluch/i2c-cjmcu-75/blob/master/ch341-i2c-lm75a/assets/sigrok-ch341-i2c-read-temp.png?raw=true)
* seriová paměť AT24C32





Startovací strom zdrojových kódů pro výuku mikroprocesorové techniky s kitem
[NUCLEO-8S208RB](https://www.st.com/en/evaluation-tools/nucleo-8s208rb.html).

Strom je určen pro překladač [SDCC](http://sdcc.sourceforge.net/). Standardní
knihovnu pro práci s periferiemi 
[SPL](https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm8-embedded-software/stsw-stm8069.html)
je třeba (z licenčních důvodů) stáhnou zvlášť ze stránek výrobce a použít
[patch](https://github.com/gicking/STM8-SPL_SDCC_patch).

* template: [STM8 start toolchain](https://github.com/spseol/STM8-start-toolchain)
* toolchain návod: [Vývoj STM8 s OpenSource nástroji](https://chytrosti.marrek.cz/vyvoj-stm8-s-opensource-nastroji.html)
