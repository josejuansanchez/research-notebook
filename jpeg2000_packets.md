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

Be careful when you are going to search the SOP marker in a J2C file.  

```
 FF 91    00 04    00 FF    91 40 ...
\-----/  \-----/  \-----/  \--------/
 16 bits  16 bits  16 bits   N bits
 
 SOP       Lsop     Nsop     Packet Body
```
