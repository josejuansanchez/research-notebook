## Quality Comparison Algorithms

Four of the most respected algorithms. 

* **Y-SSIM**  
  Structural Similarity algorithm [1] applied to luma channel only.

* **RGB-SSIM**  
  Average of Structural Similarity algorithm [1] applied to R, G, and B channels.

* **IW-SSIM**  
  Information Content Weighted Structural Similarity algorithm [5] applied to luma channel only.

* **PSNR-HVS-M**  
  Peak Signal to Noise Ratio taking into account Contrast Sensitivity Function (CSF) and between-coefficient contrast masking of DCT basis functions [6].

All of these algorithms compare two images and return a number indicating the degree to which the second image is similar to the first. In all cases, no matter what the scale, higher numbers indicate a higher degree of similarity.

It's unclear which algorithm is best in terms of human visual perception.

An implementation of these algorithms can be found on [github](https://github.com/bdaehlie/web_image_formats).

In October of 2013, Mozilla Corporation published a study entitled ["Lossy Compressed Image Formats Study"](http://people.mozilla.org/~josh/lossy_compressed_image_study_october_2013/) where they tested the aforementioned algorithms.



Image
=====

Video
=====
* [Survey of Objective Video Quality Measurements &raquo;](ftp://ftp.cs.wpi.edu/pub/techreports/pdf/06-02.pdf)
