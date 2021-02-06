SPIFFS
-

HTTP requests methods
##### GET: 
Used to get **data** from a specific **ressource**. The query string is sent in the URL of a GET request: 
`/test/demo_form.php?name1=value1&name2=value2`


PROGMEM 
-
- `PGM_P` , `PROGMEM` 
- Tells the compiler to put the information into flash memory instead of SRAM (where variable go to normally).
- Part of the `pgmspace.h` library avaialbe in AVR architecture only. 
- Used to store large data (e.g strings) that don't change. It frees up the SRAM.
  
