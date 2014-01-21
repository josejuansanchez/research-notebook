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

5. [IW-SSIM: Information Content Weighted Structural Similarity Index for Image Quality Assessment](https://ece.uwaterloo.ca/~z70wang/research/iwssim/).  
  Zhou Wang and Qiang Li, "Information Content Weighting for Perceptual Image Quality Assessment," IEEE Transactions on Image Processing, vol. 20, no. 5, pp. 1185-1198, May 2011.


## Tools

### SSIM (Structural Similarity)

* [SSIM Matlab/Octave implementation](https://github.com/josejuansanchez/ssim).


### DSSIM (Structural Dissimilarity)

* [DSSIM C implementation](https://github.com/pornel/dssim).
  This tool computes (**dis**)similarity between two **PNG** images using algorithms approximating human vision. [More info]( http://pornel.net/dssim).


## Quality Comparison Algorithms

* **Y-SSIM**  
  Structural Similarity algorithm [1] applied to luma channel only.

* **RGB-SSIM**  
  Average of Structural Similarity algorithm [1] applied to R, G, and B channels.

* **IW-SSIM**  
  Information Content Weighted Structural Similarity algorithm [5] applied to luma channel only.

* **PSNR-HVS-M**  
  Peak Signal to Noise Ratio taking into account Contrast Sensitivity Function (CSF) and between-coefficient contrast masking of DCT basis functions [6].

All of these algorithms compare two images and return a number indicating the degree to which the second image is similar to the first. In all cases, no matter what the scale, higher numbers indicate a higher degree of similarity.

It's unclear which algorithm is best in terms of human visual perception, so we tested with four of the most respected algorithms. 


