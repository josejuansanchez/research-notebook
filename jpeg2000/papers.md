## Papers
  * [Limited spatial access in JPEG2000 for remote image editing](http://www.informatik.uni-rostock.de/~sanction/publications/Rosenbaum-VIIP04b.pdf) René Rosenbaum.
  * [Flexible, dynamic and compliant region of interest coding in JPEG2000](http://vcg.informatik.uni-rostock.de/~sanction/publications/Rosenbaum-ICIP02.pdf) René Rosenbaum.
  * [Efficient communication of video using metadata](http://ivmp.unsw.edu.au/~aousn/pdf/icip2011.pdf). Aous Thabit Naman, Duncan Edwards, and David Taubman. ICIP 2011.  
  In this paper the sequences have **33** frames with a resolution of **1024x768** and a
  bit depth of **8 bits per sample**. Both sequences are converted to JPEG2000 using
  Kakadu. **Five levels of irreversible DWT** are employed for both sequences with
  a **code-block size of 32x32** and **20 quality layers**.   
  **Motion is estimated at 1/4
  -pixel accuracy**, using **7-tap interpolation kernels formed by windowing cubic
  splines**. Motion is estimated using the color version of these sequences, but
  only the Y-component is used for all the tests reported in the paper.
