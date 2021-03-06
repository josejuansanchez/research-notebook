## Conditional Replenishment + Motion Compensation


#### Keywords
JPEG2000, Streaming, Conditional Replenishment, Motion Compensation


#### Conditional Replenishment of JPEG2000 tiles with Motion Compensation

**Notes** 

* Reduces the inter-frame redundancy present in common JPEG2000 sequences (MJP2 sequences).
* Applies a real-time motion compensation technique to the MJP2 sequences before transmission.
* They propose transmitting only the tiles that change in each JPEG2000 frame.
* *Review*: the method proposed for real-time tile change detection.

**References**  

1. [MIJ2K: Enhanced video transmission based on conditional replenishment of JPEG2000 tiles with motion compensation](http://www.sciencedirect.com/science/article/pii/S1047320311000253).  
Alvaro Luis Bustamante, José M. Molina López,  Miguel A. Patricio.  
Univ. Carlos III de Madrid, Madrid, Spain.  


#### Conditional Replenishment of JPEG2000 code-blocks with Motion Compensation

**Notes** 

* Too complex to be applied in real-time environments.
* Clients and servers have to be purposely designed for use with these techniques.


**References**  

1. [A novel paradigm for optimized scalable video transmission based on JPEG2000 with motion.](http://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=4379773)  
A. Naman, D. Taubman.  
IEEE International Conference on Image Processing, 2007. ICIP 2007, vol. 5, 2007.  


2. [Optimized scalable video transmission based on conditional replenishment of JPEG2000 code-blocks with motion compensation](http://delivery.acm.org/10.1145/1300000/1290061/p43-naman.pdf).  A. Naman, D. Taubman.  
Proceedings of the International Workshop on Mobile Video, ACM, New York, NY, USA (2007), pp. 43–48

3. [A flexible video transmission system based on JPEG 2000 conditional replenishment with multiple references](http://www.intopix.com/uploaded/Download%20Publications/intoPIX%20-%20A%20FLEXIBLE%20VIDEO%20TRANSMISSION%20SYSTEM%20BASED%20ON%20JPEG%202000%20CONDITIONAL%20REPLENISHMENTWITH%20MULTIPLE%20REFERENCES_FO_Devaux.pdf).  
F. Devaux, J. Meessen, C. Parisot, J. Delaigle, B. Macq, C. De Vleeschouwer.  
IEEE International Conference on Acoustics, Speech Signal Proces. (ICASSP 07).  


---

**Notes**

* They propose a rate-distortion optimal strategy to select the most profitable packets to transmit. 
* They provide the client with two references, the previous reconstructed frame and an estimation of the current scene background, which improves the transmission system performances.
 
**References**

* [A flexible video transmission system based on JPEG2000 Conditional Replenishment with multiple references](http://www.intopix.com/uploaded/Download%20Publications/intoPIX%20-%20A%20FLEXIBLE%20VIDEO%20TRANSMISSION%20SYSTEM%20BASED%20ON%20JPEG%202000%20CONDITIONAL%20REPLENISHMENTWITH%20MULTIPLE%20REFERENCES_FO_Devaux.pdf)

---

### Thesis

* **Thesis**: [JPEG 2000 and Parity Bit Replenishment for Remote Video Browsing](http://www.intopix.com/uploaded/Download%20Publications/intoPIX_JPEG%202000%20and%20Parity%20Bit%20Replenishment%20for%20Remote%20Video%20Browsing_Thesis_FO_Devaux.pdf)  
  François-Olivier Devaux. September 2008.

* **Thesis** [JPEG2000-Based Scalable Interactive Video (JSIV)](https://www.google.es/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&ved=0CDUQFjAA&url=http%3A%2F%2Funsworks.unsw.edu.au%2Ffapi%2Fdatastream%2Funsworks%3A9778%2FSOURCE02&ei=x0zqUoOfMqv07Abl_4G4Dw&usg=AFQjCNEd2CqPc-IbL2rKOa6Axr_JJw6aog&sig2=z8pLe5Lb2GOWY-1rvEvD0w&bvm=bv.60444564,d.ZGU)  
  Aous Thabit Naman. September 2010.

**Notes**

* JSIV relies on three main concepts: storing the video sequence as independent
JPEG2000 frames to provide for quality and spatial resolution scalability, as well as
temporal and spatial accessibility; prediction and conditional replenishment of precincts
to exploit inter-frame redundancy; and loosely-coupled server and client policies.

* The server optimally selects the number of quality layers for each precinct
it transmits and decides on any side-information that needs to be transmitted while the
client attempts to make most of the received (distorted) frames.

* The client decides which precincts are predicted and which are decoded from received data (or
possibly filled with zeros in the absence of received data). Thus, in JSIV, a predicted
frame typically has some of its precincts predicted from nearby frames while others
are decoded from received intra-coded precincts; JSIV never uses frame differences or
prediction residues.

* The philosophy behind these policies is that neither the server nor the client drives
the video streaming interaction, but rather the server dynamically selects and sends the
pieces that, it thinks, best serve the client needs and, in turn, the client makes most
of the pieces of information it has. The JSIV paradigm postulates that if both the
client and the server policies are intelligent enough and make reasonable decisions, then
the decisions made by the server are likely to have the expected impact on the client’s
decisions.

* Experimental results show that JSIV’s performance is slightly inferior to that of
existing predictive coding standards in conventional streaming applications; however,
JSIV produces significant improvements when its scalability and accessibility features,
such as the region of interest, are employed.

* The **preprocessing stage** is responsible for compressing each frame
independently of the other frames into the JPEG2000 format and preparing side-
information for these frames. The side information can include distortion-length slope
tables, motion information, motion distortions, and any other side information that
might be required during media serving. Side-information can either be generated off-
line for pre-recorded media or in real-time for live media. Many of these operations are
independent of each other and can be easily delegated to one or more machines in a
content delivery network.

---

### Patents

* [Conditional replenishment for motion JPEG2000 &raquo;](http://www.google.com/patents/US8577157)  
  Inventors: [Fabrice Le Leannec](http://www.technicolor.com/en/talent/researcher/le-leannec) and [Xavier Henocq](http://www.informatik.uni-trier.de/~ley/pers/hd/h/Henocq:Xavier.html). / Canon.  
  Date of Patent: Nov. 5, 2013
  
---

* [Rate-constrained Conditional Replenishment Video Coding with Adaptive Change Detection](http://www.stanford.edu/class/ee368b/Projects/chiao/)  
  Xinqiao Liu. December 1, 2000.  

* [A New Video Compression Scheme Combining Conditional Replenishment and Address Event Representation](http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=4387612)  
  IEEE Workshop on Signal Processing Systems, 2007. Date of Conference: 17-19 Oct. 2007.

* [Adaptation of the method of estimation and motion compensation int he transmission of the video sequence in JPEG2000](http://airccse.org/journal/ijdps/papers/3612ijdps14.pdf). International Journal of Distributed and Parallel Systems (IJDPS) Vol.3, No.6, November 2012. Abdou Khadre Diop.
