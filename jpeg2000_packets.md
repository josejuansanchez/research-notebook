JPEG2000 Packet Structure
-------------------------

Example:

``
 FF 91     00 04    04 EC   C0 00 ...
\-----/   \-----/  \-----/  \--------/
 16 bits  16 bits  16 bits   N bits
 
 SOP       Lsop     Nsop     Packet Body
``

SOP: Start Of Packet.
Lsop: Length of marker segment in bytes (Not including the marker).
Nsop: Packet number. (Values: 0 - 65535).
