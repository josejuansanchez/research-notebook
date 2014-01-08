### JPEG2000 Packet Structure
-----------------------------

Example:  

```
 FF 91    00 04    04 EC    C0 00 ...
\-----/  \-----/  \-----/  \--------/
 16 bits  16 bits  16 bits   N bits
 
 SOP       Lsop     Nsop     Packet Body
```

**SOP**: Start Of Packet marker.  
**Lsop**: Length of marker segment in bytes (Not including the marker).  
**Nsop**: Packet number (Possible values are between 0 and 65535).  


### Warning!
------------

Be careful when you are going to search the SOP marker in a JPEG2000 code-stream.  
If you only looking for ```0xFF91``` values, you can get an erroneous result.  

Example:  

```
 FF 91    00 04    00 FF    91 40 ...
\-----/  \-----/  \-----/  \--------/
 16 bits  16 bits  16 bits   N bits
 
 SOP       Lsop     Nsop     Packet Body
```

The last byte of **Nsop** and the first byte of **Packet body** form a ```0xff91``` value that could result in an erroneous interpretation.  
