Structural SIMilarity (SSIM)
============================

1. [The SSIM Index for Image Quality Assessment](http://www.cns.nyu.edu/~lcv/ssim/).  
  [Zhou Wang](http://www.ece.uwaterloo.ca/~z70wang/), [Alan C. Bovik](http://live.ece.utexas.edu/people/bovik/), [Hamid R. Sheikh](http://live.ece.utexas.edu/People/people_detail.php?id=92) and [Eero P. Simoncelli](http://www.cns.nyu.edu/~eero/).

2. [Image Quality Assessment: From Error Visibility to Structural Similarity](http://www.cns.nyu.edu/pub/eero/wang03-reprint.pdf).  
  IEEE Transactions on Image Processing, vol. 13, no. 4, Apr. 2004.

3. [Mean squared error: love it or leave it? - A new look at signal fidelity measures](https://ece.uwaterloo.ca/~z70wang/publications/SPM09.pdf).  
  IEEE Signal Processing Magazine, vol. 26, no. 1, pp. 98-117, Jan. 2009.

4. [Image Quality Assessment Techniques on Spatial Domain](http://www.ijcst.com/vol23/1/sasivarnan.pdf).  
  IJCSt Vol. 2, ISSue 3, September 2011.  
  Note: "SSIM is widely used method for measurement of image quality. It works accurately can measure better across distortion types as compared to MSE and PSNR, but **fails in case of highly blurred image**."


## Tools

### SSIM (Structural Similarity)

* [SSIM Matlab/Octave implementation](https://github.com/josejuansanchez/ssim).

* [PYSSIM Python implementation](https://github.com/jterrace/pyssim). A Python module for computing the Structural Similarity Image Metric (SSIM). Original code written by Antoine Vacavant from http://isit.u-clermont1.fr/~anvacava/code.html, with modifications by Christopher Godfrey and Jeff Terrace.

* [SSIM implementation for OpenCV2.x (c++)](http://nma.web.nitech.ac.jp/fukushima/opencv/ssim/ssim-e.html).


### DSSIM (Structural Dissimilarity)

* [DSSIM C implementation](https://github.com/pornel/dssim).
  This tool computes (**dis**)similarity between two **PNG** images using algorithms approximating human vision. [More info]( http://pornel.net/dssim).

* [DSSIM C++ implementation](http://pholia.tdi.informatik.uni-frankfurt.de/~philipp/software/dssim.shtml).


## Quality Comparison Algorithms

* **Y-SSIM**  
  Structural Similarity algorithm [4] applied to luma channel only.

* **RGB-SSIM**  
  Average of Structural Similarity algorithm [4] applied to R, G, and B channels.

* **IW-SSIM**  
  Information Content Weighted Structural Similarity algorithm [5] applied to luma channel only.

* **PSNR-HVS-M**  
  Peak Signal to Noise Ratio taking into account Contrast Sensitivity Function (CSF) and between-coefficient contrast masking of DCT basis functions [6].

All of these algorithms compare two images and return a number indicating the degree to which the second image is similar to the first. In all cases, no matter what the scale, higher numbers indicate a higher degree of similarity.

It's unclear which algorithm is best in terms of human visual perception, so we tested with four of the most respected algorithms. 


